#ifndef DESTRUCTIBLE_HPP
#define DESTRUCTIBLE_HPP

/* A destructible object has a health counter and can be damaged and destroyed. */
class Destructible {
public:
  typedef float Health;

  Destructible(Health);

  virtual void damage(Health);
  inline Health health() { return health_; }
private:
  Health health_;
protected:
  virtual void destroy() = 0;
};

#endif
