# MazeGenerator
A simple maze generator and solver!

> <b>Warning</b>, this is an old and not optimized project!

<img src="img/preview.gif?raw=true" alt="Girl in a jacket" width="500" height="500"> 



`Maze Generator` works better on Linux.

You can compile it with;

```sh
$   gcc maze.c -o maze
```

Settings must be choosen before compiling, by modifying these lines:

```

//config parameters
#define SIZE 121
#define WALL 'O'
#define WALK '.'
#define SPEED 10000

```
* `SIZE` is the side length. It must be an odd number
* `WALL` is the char used to represent walls
* `WALK` is the char used to represent the maze solution
* `SPEED` is the delay (in ms) between screen refresh, so a lower value means a faster animation

