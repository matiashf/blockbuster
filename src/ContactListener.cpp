#include "ContactListener.hpp"
#include "Destructible.hpp"

#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <cmath> // std::isnan
#include <QTimer>

// TODO: Increase the threshold below to a reasonable value
const float32 ContactListener::kSpecificImpulseThreshold = 0.1f; // Unit: m/s

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
  return; // FIXME: The cast below segfaults
  Destructible* destructible = static_cast<Destructible*>(body->GetUserData());
  if (destructible == nullptr)
    return;  // the body did not point to a Destructible (e.g. points to a Ball)
  impulse_magnitude /= body->GetMass(); // Convert from impulse to specific impulse
  // FIXME: Assuming that the impulse is positive. Is that always true?
  if (impulse_magnitude >= kSpecificImpulseThreshold)
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
