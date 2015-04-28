# Design decisions

This document describes some of the design decisions I've made during
development of the game.

## Colors

There are some visual challenges that must be solved in the game:
1. Associating items on the scene with players.
2. Distinguishing between boxes, so that two boxes next to each other
   do not appear to be one single box.
3. Indicating that a box has taken damage.

To solve these problems we use the convenient [HSL color
model](http://en.wikipedia.org/wiki/HSL_and_HSV), which describes a
cylindrical color space using three axes; Hue, Saturation and
Lightness. This corresponds nicely with the three visual distinctions
we need to make in the came.

Each player gets a distinct hue (a base color like red, green, etc.)
equally spaced out in the hue color axis (from 0° to 359°). Boxes
belonging to a player use the same hue but a different, random
saturation level withing a reasonable interval (to avoid white boxes)
and full lightness. When boxes take damage, they darken (i.e. get
lower lightness) down to some minimum (to avoid black boxes).
