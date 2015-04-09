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

Read about [how to coordinate physics simulation and periodic
drawing](http://gafferongames.com/game-physics/fix-your-timestep/ "Fix
Your Timestep!").
