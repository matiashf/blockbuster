#ifndef DESTRUCTIBLE_HPP
#define DESTRUCTIBLE_HPP

/** A virtual class with a health counter, that can be damaged and destroyed. */
class Destructible {
public:
  /// We use a type to improve code readability
  typedef float Health;

  /// Sets the health counter to the given value
  Destructible(Health);

  /// Reduces the health counter by the given value
  virtual void damage(Health);
  /// Returns the health counter
  inline Health health() { return health_; }
private:
  Health health_;
protected:
  /// Called when the health counter goes to or below zero. Only called once.
  virtual void destroy() = 0;
};

#endif
