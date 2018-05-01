/* This file contains the game skeleton including the logic to implement game moves */

#define GRIDSTARTX 10
#define GRIDSTARTY 13
#define SQUAREWIDTH 20


void printString(float x, float y, const char* s, RGB color)
{
	glColor3f(color.r, color.g, color.b);
	glRasterPos2f(x, y);

	for(int i=0;i<strlen(s);++i)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
}

void printBigString(int x, int y, string s, RGB color, int z=0)
{
	glColor3f(color.r,color.g,color.b);
	glPushMatrix();
	glTranslatef(x, y+8,z);
	glScalef(0.09f,0.08f,z);

	for(int i=0;i<s.length();++i)
		glutStrokeCharacter(GLUT_STROKE_ROMAN , s[i]);
	glPopMatrix();
}

void drawSquare(int x, int y, int num)
{
	glLineWidth(4.0);
	glColor3f(1.0,0.0,0.0);
	
	glBegin(GL_LINE_LOOP);
		glVertex2f(x,y);
		glVertex2f(x+SQUAREWIDTH,y);
		glVertex2f(x+SQUAREWIDTH,y+SQUAREWIDTH);
		glVertex2f(x,y+SQUAREWIDTH);
	glEnd();


	float r1 = colormap[num].r;
	float g1 = colormap[num].g;
	float b1 = colormap[num].b;
	glColor3f(r1,g1,b1);
	glRectd(x+0.5,y+0.5,x+SQUAREWIDTH-0.5,y+SQUAREWIDTH-0.5);
	
	if(num)
		printBigString(x+7,y-2,to_string(num),{0,0,0});
}

void drawGrid(int g[3][3])
{
	int x = GRIDSTARTX , y = GRIDSTARTY;

	for(int i=0;i<3;++i)
	{
		y = GRIDSTARTY;
		for(int j=0;j<3;++j)
		{
			drawSquare(x,y,g[i][j]);
			y+=SQUAREWIDTH;
		}
		x+=SQUAREWIDTH;
	}
}

void moveUp()
{
	if(hole[1] != 0)
	{
		swap(grid[ hole[0] ][ hole[1] ] , grid[ hole[0] ][ hole[1] - 1 ]) ;
		hole[1]--;
	}
}
void moveDown()
{
	if(hole[1] != 2)
	{
		swap(grid[ hole[0] ][ hole[1] ] , grid[ hole[0] ][ hole[1] + 1 ]) ;
		hole[1]++;
	}
}
void moveLeft()
{
	if(hole[0] != 2)
	{
		swap(grid[ hole[0] ][ hole[1] ] , grid[ hole[0] + 1][ hole[1] ]) ;
		hole[0]++;
	}
}
void moveRight()
{
	if(hole[0] != 0)
	{
		swap(grid[ hole[0] ][ hole[1] ] , grid[ hole[0] - 1][ hole[1] ]) ;
		hole[0]--;
	}
}

bool isSolvable(int seed[])
{
	int inversions = 0;
	for(int i=0;i<9-1;++i)
		for(int j=i+1;j<9;++j)
			if(seed[i] && seed[j] && seed[i] > seed[j])
				inversions++;

	// return true if inversion count is even.
	return (inversions%2 == 0);
}

void reset()
{
	int i,j,k,l,m;
	int sseed[]={1,2,3,4,5,6,7,8,0}, seed[3][3];

	// Randomly swap positions
	for(i=0;i<9;++i)
		swap(sseed[i],sseed[rand()%9]);

	for(k=0,i=0;i<3;++i)
	{
		for(j=0;j<3;++j,++k)
		{
			seed[i][j] = sseed[k];
		}
	}

	if(isSolvable(sseed))
	{
		k = 0;
		for(i=0;i<3;++i)
		{
			for(j=0;j<3;++j)
			{
				if(seed[i][j] == 0)
				{
					hole[0] = i;
					hole[1] = j;
				}

				grid[i][j] = seed[i][j];
				k++;
			}
		}
	}
	else
		reset();
}

void printGrid()
{
	int i, j;
	seed* curr = finalsequence.top();
	for(i=0;i<3;++i)
		for(j=0;j<3;++j)
			grid[i][j] = curr->mat[i][j];
}

void pushGrids(seed* node)
{
	finalsequence.push(node);

	if(node->parent)
		pushGrids(node->parent);
	else
		printGrid();
	return ;
}


