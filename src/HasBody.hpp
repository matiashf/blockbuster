#ifndef HAS_BODY_HPP
#define HAS_BODY_HPP

#include "GameScene.hpp"

#include <QGraphicsItem>

// More on what frames of reference are used in QGraphicsScene and Box2D:
// * http://stackoverflow.com/a/1151955/2719221
// * http://gamedev.stackexchange.com/a/3760

// The shape is owned by the fixture, the fixture is owned by the
// body, the body is owned by the world, and the world is owned by the
// scene. No further memory management is required in this class.

class HasBody : public QGraphicsItem {
public:
  HasBody(qreal x, qreal y);
  virtual ~HasBody();

  inline b2Body* body() { return body_; };

  inline GameScene* gameScene() {return dynamic_cast<GameScene*>(scene());}

  // Callbacks used for rendering
  void advance(int phase) override;
  QVariant itemChange(GraphicsItemChange change, const QVariant & value);
protected:
  virtual void defineBody(b2BodyDef&) = 0;
  virtual void defineFixture(b2FixtureDef&) = 0;
  virtual b2Shape* createShape() = 0;

  void destroyBody();
private:
  b2Body* body_;

  void createBody();
};

#endif
