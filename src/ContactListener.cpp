#include "ContactListener.hpp"
#include "Destructible.hpp"

#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <cmath> // std::isnan
#include <QTimer>
#include <QGraphicsItem>

const float32 ContactListener::kImpulseThreshold = 5.0f; // Unit N*s
const float32 ContactListener::kDamageReductionFromMass = 0.2f;

ContactListener::ContactListener() {}
ContactListener::~ContactListener() {}

// Called by box2d after a collision between two objects
void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){
  damage(contact->GetFixtureA(), impulse->normalImpulses[0]);
  damage(contact->GetFixtureB(), impulse->normalImpulses[1]);
}

/* Helper method for PostSolve.

   Finds Destructible instance from fixture (using the bodys
   UserData() pointer) and deals damage to it. */
void ContactListener::damage(b2Fixture* fixture, float32 impulse_magnitude) {
  b2Body* body = fixture->GetBody();
  QGraphicsItem* item = reinterpret_cast<QGraphicsItem*>(body->GetUserData());
  Destructible* destructible = dynamic_cast<Destructible*>(item);
  if (destructible == nullptr)
    return;  // the item is not a Destructible (e.g. is Ball not a Box)
  if (impulse_magnitude < 0)
    impulse_magnitude *= -1.0f;
  if (impulse_magnitude < kImpulseThreshold)
    return;  // The impact was not powerful enough

  // Apply mass damage reduction
  impulse_magnitude *= pow(body->GetMass(), -kDamageReductionFromMass);

  delay([destructible, impulse_magnitude] {
      destructible->damage(impulse_magnitude);
    });
}

/* Add the functor to the back of Qts event queue by using a single
   shot timer with a timeout of zero milliseconds. Destructible is not
   a QObject (since QGraphicsItem is not), so we use a c++-11 functor
   to make the call instead of a Qt slot. */
void ContactListener::delay(std::function<void(void)> functor) {
  QTimer* timer = new QTimer(this);
  timer->setSingleShot(true);
  timer->setInterval(0); // When all other events have finished processing
  connect(timer, &QTimer::timeout, functor);
  connect(timer, &QTimer::timeout, timer, &QObject::deleteLater);
  timer->start();
}
