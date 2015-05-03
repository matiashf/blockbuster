#ifndef CONTACT_LISTENER_HPP
#define CONTACT_LISTENER_HPP

#include "Destructible.hpp" // Destructible::Damage

#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <functional> // std::function
#include <QObject>

/** Calculates and deals damage to Destructible objects. The
    ContactListener is called by the physics world during collisions.

    Damage is calculated from impulse divided by a constant root of
    mass. In other words: objects take damage proportional to how much
    they speed up when colliding, and inversely proportional to their
    mass. Small collisions are ignored.

    The callback code runs while the physics world is resolving
    collisions, so adding or removing objects from the callbacks is
    not allowed. To avoid this problem we delay the call to
    Destructible until after the physics engine is done working.

    All user data pointers on b2Body objects MUST be a
    reinterpret_cast from QGraphicsItem* to void*. This holds true in
    our game (they are set in HasBody only), but it somehow feels
    brittle. Maybe the Box2D developers could have provided us with
    something more type safe than void pointers?
*/
class ContactListener : public QObject, public b2ContactListener {
  Q_OBJECT
public:
  ContactListener();
  ~ContactListener();

  /// Called by Box2D when two objects have collided
  void PostSolve(b2Contact*, const b2ContactImpulse*);
  /// Impulses less than the given value are discarded
  static const float32 kImpulseThreshold;
  /// The exponent when calculating damage = impulse / mass**exponent
  static const float32 kDamageReductionFromMass;
private:
  // Deals damage to a fixture based the impulse to received in the collision
  void damage(b2Fixture*, float32 impulse_magnitude);
  // Asynchronously run the given functor after the collision phase is completed
  void delay(std::function<void(void)>);
};
#endif
