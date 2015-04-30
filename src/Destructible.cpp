#include "Destructible.hpp"

#include <QTimer>

const Destructible::Health Destructible::kDefaultHealth = 200.0f; // FIXME: Adjust

Destructible::Destructible(Destructible::Health health) :
  health_{health}
{
}

// Decrements health. Calls destroy() if health goes below zero.
void Destructible::damage(Destructible::Health damage) {
  health_ -= damage;
  if (health_ <= 0 and health_ + damage > 0)
    destroy();
}
