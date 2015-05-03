## 2015-04-07 First project day

Played around with ideas, decided on a game backed by the Bullet
physics engine. A realtime 2D multiplayer game where you shoot down
the opponents castle with your cannnon.

Downloaded and built bullet with examples. Glanced at its
architecture. Drew some game sketches.

## 2015-04-08 First day of programming. 

Decided on evaluating project feasability by writing a prototype over
the next three days.

Familiarized myself with Qt and QGraphicsView, set up a basic
environment with build tools. Tried to use GNU Make but switched to
qmake which generates a Makefile.

Implemented a running program with window, OpenGL-backed drawing
canvas using QGraphicsView and some size and scaling constraints.

The game currently draws a black ball at a fixed position.

## 2015-04-09 Periodic rendering and physics simulation

Read article on [how to coordinate physics simulation and periodic
drawing](http://gafferongames.com/game-physics/fix-your-timestep/ "Fix
Your Timestep!"). Implemented periodic rendering at 60 FPS (with frame
dropping).

Did basic integration with bullet. Created a physics world and applied
gravity constraints. No objects in the world.

The game currently shows a box in a fixed position and moves a black
ball with constant speed.

## 2015-04-10 End of prototype phase, ditching Bullet

Attempted to integrate bullet, but ran into several problems:
* Bullet is a 3D engine. Applying 2D-constraints is possible, but non-trivial.
* The source code contains a mix of both working and unfinished
  code. Googling, I found a post by one of the authors mentioning that
  "that class is unfinished, and should not be used."
* The documentation is severely lacking, and the examples are hard to
  read.

In conclusion, I've decided to avoid using bullet. If I had a 3D
background I might find the concepts easier to grasp. But I don't, so
I won't.

Instead, I will use box2d. It seems to be the most promising OSS
candidate for 2D physics simulation.
