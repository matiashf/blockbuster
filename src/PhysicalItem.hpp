#ifndef HAS_BODY_HPP
#define HAS_BODY_HPP

#include "GameScene.hpp"

#include <QGraphicsItem>

// More on what frames of reference are used in QGraphicsScene and Box2D:
// * http://stackoverflow.com/a/1151955/2719221
// * http://gamedev.stackexchange.com/a/3760

/** A QGraphicsItem with a body in the simulated physical world.

    When an instance is added to a scene, the createBody() method is
    called, and likewise with destroyBody(). Subclasses must implement
    createShape(), defineBody() and defineFixture(), which are called
    by createBody().

    The shape is owned by the fixture, the fixture is owned by the
    body, the body is owned by the world, and the world is owned by
    the scene. No further memory management is required in this
    class. */
class PhysicalItem : public QGraphicsItem {
public:
  /// Places the graphic item at the given scene coordinates
  PhysicalItem(qreal x, qreal y);
  virtual ~PhysicalItem();

  inline b2Body* body() { return body_; };

  inline GameScene* gameScene() {return dynamic_cast<GameScene*>(scene());}

  /// Sets scene position and orientation from its body in the world
  void advance(int phase) override;
  /// Creates or destroys a body when added to or removed from a scene
  QVariant itemChange(GraphicsItemChange change, const QVariant & value);
protected:
  /// Defines additional body properties like initial velocity and damping
  virtual void defineBody(b2BodyDef&) = 0;
  /// Defines additional fixture properties like friction, restitution, density
  virtual void defineFixture(b2FixtureDef&) = 0;
  /// Creates a new shape *on the heap*. Ownership is passed to the caller.
  virtual b2Shape* createShape() = 0;

  /// Removes the body from the world and deletes it.
  void destroyBody();
private:
  b2Body* body_;

  /// Creates a body using defineBody(), defineFixture() and createShape().
  void createBody();
};

#endif
