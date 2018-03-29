# Puzzle-8
An implementation of the game Puzzle 8 and building an AI to solve it

The AI of the program is going to be built using the A* algorithm which used Priority Queues and Heaps to implement. Uses OpenGL and GLUT framework. Make sure you have both the libraries installed before running.

**To compile :**

macOS :
~~~~ 
g++ main.cpp -o main.out -std=c++11 -framework GLUT -framework OpenGL -Wno-deprecated-declarations
~~~~
Linux :
~~~~ 
g++ main.cpp -o main.out -std=c++11 -lGL -lGLU -lglut -Wno-deprecated-declarations
~~~~

**To run :**
~~~~
./main.out
~~~~
