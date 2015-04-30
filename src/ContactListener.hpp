#ifndef CONTACT_LISTENER_HPP
#define CONTACT_LISTENER_HPP

#include "Destructible.hpp" // Destructible::Damage

#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <functional> // std::function
#include <QObject>

/* The ContactListener is called by the physics engine during
   collisions. It deals damage to Destructible objects.

   The unit of damage is specific impulse, i.e. N*s/kg = m/s. In other
   words: objects take damage proportional to how much they speed up
   when colliding. Heavy objects take less damage than light
   objects. Small collisions are ignored.

   The callback code runs while the physics world is resolving
   collisions, so adding or removing objects from the callbacks is not
   allowed. To avoid this problem we delay the call to Destructible
   until after the physics engine is done working.
*/
class ContactListener : public QObject, public b2ContactListener {
  Q_OBJECT
public:
  ContactListener();
  ~ContactListener();

  // Called by Box2D when two objects have collided
  void PostSolve(b2Contact*, const b2ContactImpulse*);
private:
  // Deals damage to a fixture based the impulse to received in the collision
  void damage(b2Fixture*, float32 impulse_magnitude);
  // Asynchronously run the given functor after the collision phase is completed
  void delay(std::function<void(void)>);
  static const float32 kSpecificImpulseThreshold;
};
#endif
