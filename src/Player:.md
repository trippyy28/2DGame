Player:
- The player is reperesented by a shape which is defined in the config file
- The player must spawn in the center of the screen at the beginning of the 
game, and after it dies (collides with enemy)
- The player moves by a speed read from the config file in these directions:
Up: W key, Left: A key, Down: S key, Right: D key
- The player is confined to move only within the bounds of the window
- The player will shoot a bullet toward the mouse pointer when the left mouse
is clicked. The speed , the size and lifespan of the bullets are read from the config file.


Special abilty

- You are free to come up with your own "special move" which is fired by
the player when the right mouse button is clicked.
the special abilty must:
  - Multiple entites ( bullets etc ) spawnd by a special weapon
  - Entites have some unique graphic assoiciate with them
  - A unique game mechanic is introduced via a new component 
  - A 'cooldown timer' must be implemented for the special weapon
the properties of the special move are not in the config file. 

Enemy 
- Enemies will spawn in a random location on the screen every X frames,
  where X is defined in the configuartion file.
- Enemies must not overlap the sides of the screen at the time of the spawn.
- Enemies shapes have random number of vertices, between a given number a given minimum and maximun number,
  which is specified in the config file.
- Enemy shape radius will be specified in the config file.
- When an enemy reaches the edge of the window, it should bounce off 
  in the oppsite direction at the same speed.
- When (large) enemies collide with a bullet or player, they are destoryed,
  and N small enemies spawn in its place, where N is the number of the vertics of the original enemy.
  Each small enemy must have the same number of vertices and color of the original enemy. These small 
  entites travel outward at angles at a fixed intervals equal to (360 / vertices).
  For example, if the original enemy had 6 sides, the 6 smaller enemies will
  travel outward in intrevals of (360/6) = 60 degrres.

  Score

  -Each time an enemy spawns, it is given  a score of component of N * 100, where N 
  is the number of vertices it has. Small enenmies get double this value.
  - If a player bullet kills an enemy, the game score is increased by the score
  component of the enemy killed.
  - The score should be displayed with the font specifed by the config file in 
    the top-left corner of the screen. 


Drawing 

- In the render system, all entities should be given a slow rotation,
  which make the game look a little nicer.

- Any special effects which do not alter game play can be added for up to
  5% bonus marks on the assignment, Note that assignments cannot go above
  100% total marks, but the 5% bonus can overwrite any marks lost in other
  areas of the assignment. 
 - Any Entity with a lifespan is currently alive, it should have its
  Color alpha channel set to a ratio depnding on how long its has left to live.
  For example, if an Entity has a 100 frame life span, and it has been alive for