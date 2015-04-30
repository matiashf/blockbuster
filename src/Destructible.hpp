#ifndef DESTRUCTIBLE_HPP
#define DESTRUCTIBLE_HPP

/* A destructible object has a health counter and can be damaged and destroyed.

   This class requires all bodies in the world to have their UserData
   field either set to nullptr or point to a Destructible object,
   otherwise a segmentation fault will occur.
*/
class Destructible {
public:
  typedef float Health;

  static const Health kDefaultHealth;
  Destructible(Health health=kDefaultHealth);

  void damage(Health);
  inline Health health() { return health_; }
private:
  Health health_;
protected:
  virtual void destroy() = 0;
};

#endif
