# Puzzle-8
An implementation of the game Puzzle 8 and building an AI to solve it

The AI of the program is built using the A* algorithm which used Priority Queues and Heaps to implement. Uses OpenGL and GLUT framework. Make sure you have both the libraries installed before running.

Some states may take few seconds(maybe even upto 1-2 minutes) so be patient. The algorithm is theorhetically exponential in time complexity asymptotics but works well for 3x3 grid in under 2 minutes.

Use arrow keys to play the game, R to randomize the grid and S to solve it from that instance.

**To compile :**

macOS :
~~~~ 
g++ main.cpp -o main.out -std=c++11 -framework GLUT -framework OpenGL -Wno-deprecated-declarations
~~~~
Linux :
~~~~ 
g++ main.cpp -o main.out -std=c++11 -lGL -lGLU -lglut -Wno-deprecated-declarations
~~~~
Windows :
~~~~ 
g++ main.cpp -o main.out -std=c++11 -lglut32 -lglu32 -lopengl32 -Wno-deprecated-declarations
~~~~

**To run :**
~~~~
./main.out
~~~~
