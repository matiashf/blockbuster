#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include <QtWidgets/QGraphicsScene>
#include <QTimer>
#include <QTime>
#include <QString>

#include <Box2D.h>

#include "ContactListener.hpp"

class Ball;

/** The graphic scene which owns and paints QGraphicItem instances.

    The scene keeps track of game time and can be started, stopped and
    stepped forward. Rendering is managed by the superclass, but
    changes to items are made by a timer periodically calling
    advance().

    When constructed, the scene creates a Box2D world to simulate
    physics. The world gets physical boundries that correspond with
    the scene edges. Physical objects are added to the world in
    the PhysicalItem class.

    Note that the reference system used by the scene has x pointing
    right and y pointing *down*. The physical world has the same
    orientation and origin as the scene, but measures distance in
    meters instead of pixels. The mapToWorld and mapFromWorld
    functions are used to translate from one reference system to the other.
*/
class GameScene: public QGraphicsScene {
  Q_OBJECT
private:
  Ball* ball_;

  QTimer* timer; // Periodic event dispatcher
  QTime worldTime; // Clock for synchronizing the physics world with real time

  /* Use a constraint-based physics engine, like this:
     http://allenchou.net/2013/12/game-physics-constraints-sequential-impulse */
  b2Vec2 gravity;
  b2World world_;
  const qreal worldScale; // in world meters per scene pixel

  ContactListener contact_listener; // Called by world when objects collide

  /* The constants below are given as arguments to the box2d world step
     function, and set the maximum number of iterations allowed during
     numerical approximations for velocity and position. Essentially,
     the higher the number the more accurate simulation of
     collitions. Setting the value too high, however, will cause the
     simulation to slow down *in some corner cases*.

     See http://www.iforce2d.net/b2dtut/worlds for a more detailed
     description.*/
  static const int kMaxVelocityIterations;
  static const int kMaxPositionIterations;

  // For calculating worldScale, we set the number of seconds it takes
  // an object to free fall from the top to the bottom of the screen.
  static const float kScaleFactor;

  // The number of times per seconds advance() should be called
  static const qreal kFrameRate;

  // The dimensions of the scene in pixels
  static const int kSceneWidth, kSceneHeight;

  // Helper method used to construct the ground, walls and ceiling of the scene
  void addEdgeLine(QPointF, QPointF);
public:
  GameScene(QObject* parent=0);

  inline b2World* world() { return &world_; }
  inline Ball* ball() { return ball_; }

  // Convenience functions for mapping between world and scene coordinates
  inline float32 mapToWorld(qreal scalar) { return scalar * worldScale; }
  inline qreal mapFromWorld(float32 scalar) { return scalar / worldScale; }
  inline b2Vec2 mapToWorld(const QPointF & vector) {
    return b2Vec2{mapToWorld(vector.x()), mapToWorld(vector.y())};
  }
  inline QPointF mapFromWorld(const b2Vec2 & vector) {
    return QPointF{mapFromWorld(vector.x), mapFromWorld(vector.y)};
  }
  inline b2Vec2 mapToWorld(qreal x, qreal y) {
    return b2Vec2{mapToWorld(x), mapToWorld(y)};
  }

  /// Loads the given map using a GameLoader. Does not clear the scene.
  void load(QString map_url);

public slots:
  void start();
  void stop();
  /// Stop if running and vice versa
  void toggle();
  /// Increases game time by the given number of milliseconds and update game state
  void advance(qreal milliseconds);
  /// Updates game state
  void advance();
protected:
  /// Delegates events to players
  bool eventFilter(QObject * watched, QEvent * event);
};

#endif
