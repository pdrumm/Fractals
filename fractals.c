// open a large window and wait for user input

#include <stdio.h>
#include "gfx3.h"
#include <math.h>
void SierTri(int,int,int,int,int,int);
void ShrinkSq(int,int,int);
void SpiralSq(int,int,double,double,double);
void CircLace(int, int, int);
void Snow(int,int,double);
void Tree(int,int,double,double);
void Fern(int,int,double,double);

int main()
{
	int userCase, stillgoing=1;
	int xSize=700, ySize=xSize, margin=50;
	gfx_open(xSize,ySize,"Fractals!");
	while(stillgoing){
		switch(gfx_wait()){
			case '1':
				gfx_clear();
				SierTri(margin,margin,xSize-margin,margin,xSize/2,ySize-margin);
				break;
			case '2':
				gfx_clear();
				ShrinkSq(xSize/4, ySize/4, xSize/2);
				break;
			case '3':
				gfx_clear();
				SpiralSq(xSize/2,ySize/2,1,3,0);
				break;
			case '4':
				gfx_clear();
				CircLace(xSize/2, ySize/2, xSize/3);
				break;
			case '5':
				gfx_clear();
				Snow(xSize/2, ySize/2, xSize/4);
				break;
			case '6':
				gfx_clear();
				Tree(xSize/2,ySize-10,2*xSize/5,0);
				break;
			case '7':
				gfx_clear();
				Fern(xSize/2,ySize-70,xSize/2,0);
				break;
			case 'q':
				stillgoing=0;
				break;
			default:
				break;
		}
	}
}

void SierTri( int x1, int y1, int x2, int y2, int x3, int y3 )
{
	// Base case. 
	if( abs(x2-x1) < 2 ) return;

	// Draw the triangle
	gfx_triangle(x1,y1,x2,y2,x3,y3);

	// Recursive calls
	SierTri( x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2 );
	SierTri( (x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2 );
	SierTri( (x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3 );
}

void ShrinkSq( int x1, int y1, int width )
{
	// Base case. 
	if( abs(width) < 5 ) return;

	// Draw the square
	gfx_rectangle(x1,y1,width,width);

	int newWidth=6*width/25;
	// Recursive calls
	ShrinkSq( x1-newWidth, y1-newWidth, 2*newWidth );
	ShrinkSq( x1+width-newWidth, y1-newWidth, 2*newWidth );
	ShrinkSq( x1+width-newWidth, y1+width-newWidth, 2*newWidth );
	ShrinkSq( x1-newWidth, y1+width-newWidth, 2*newWidth );
}

void SpiralSq( int x1, int y1, double width, double radius, double theta )
{
	// Base case.
	if( radius > 350 ) return;

	// Draw the square
	gfx_rectangle(x1,y1,width,width);

	// Recursive calls
	SpiralSq( x1+radius*cos(theta), y1+radius*sin(theta), 1.1*width, 1.09*radius, theta+.5 );
}

void CircLace( int x1, int y1, int radius )
{
	// Base case.
	if( radius < 2 ) return;

	// Draw the circle
	gfx_circle(x1,y1,radius);

	int i, newRadius = 0.34*radius;
	// Recursive calls
	for(i=1;i<=6;i++){
		CircLace( x1+radius*cos(i*3.14/3), y1+radius*sin(i*3.14/3), newRadius );
	}
}

void Snow( int x1, int y1, double len )
{
	// Base case.
	if( len < 1 ) return;

	int i;
	// Draw the lines
	for(i=1;i<=5;i++){
		gfx_line(x1,y1,x1+len*cos(i*3.14/2.5),y1+len*sin(i*3.14/2.5));
	}

	// Recursive calls
	for(i=1;i<=5;i++){
		Snow( x1+len*cos(i*3.14/2.5), y1+len*sin(i*3.14/2.5), 0.36*len );
	}
}

void Tree( int x1, int y1, double len, double theta )
{
	// Base case.
	if( len < 1 ) return;

	// Draw the line
	gfx_line(x1,y1,x1-len*sin(theta),y1-len*cos(theta));

	double newTheta=0.7;
	// Recursive calls
	Tree( x1-len*sin(theta), y1-len*cos(theta), 0.62*len, theta+newTheta );
	Tree( x1-len*sin(theta), y1-len*cos(theta), 0.62*len, theta-newTheta );
}

void Fern( int x1, int y1, double len, double theta )
{
	// Base case.
	if( len < 5 ) return;

	// Draw the line
	gfx_line(x1,y1,x1-len*sin(theta),y1-len*cos(theta));

	int i;
	double newTheta=0.6;
	// Recursive calls
	for(i=1;i<=4;i++){
		Fern( x1-(i/4.)*len*sin(theta), y1-(i/4.)*len*cos(theta), 0.35*len, theta+newTheta );
		Fern( x1-(i/4.)*len*sin(theta), y1-(i/4.)*len*cos(theta), 0.35*len, theta-newTheta );
	}
}
