#ifndef GAMEHEADERS_INCLUDE
#define GAMEHEADERS_INCLUDE

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <bits/stdc++.h>
using namespace std;


struct RGB
{
	float r,g,b;
};

int grid[3][3]=
{
	{7,4,1},
	{8,5,2}, 
	{0,6,3}
};

/*
DISPLAYED IN THE FORM : 

(0,2) (1,2) (2,2) ^
(0,1) (1,1) (2,1) ^
(0,0) (1,0) (2,0) ^
   i > > >		  j
*/

int hole[2] = { 2, 0 }; 
// hole[0] = row
// hole[1] = column




map <int,RGB> colormap = 
{
	{0, {0.9, 0.9, 0.9} }, 
	{1, {0.0, 0.0, 1.0} }, 
	{7, {0.9, 0.3, 0.0} }, 
	{3, {0.0, 1.0, 0.0} }, 
	{4, {1.0, 0.0, 1.0} }, 
	{5, {0.0, 1.0, 1.0} }, 
	{6, {1.0, 1.0, 0.0} }, 
	{2, {0.6, 0.5, 1.0} },
	{8, {1.0, 0.7, 0.2} } 
} ;

#endif