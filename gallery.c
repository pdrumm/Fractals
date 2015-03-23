#include <stdio.h>
#include "gfx3.h"
#include <math.h>
void Snow(int,int,double,double,int);

int main()
{
	printf("Hit the space bar to display the gallery. Press 'q' to exit the window.\n");
	int stillgoing=1, 			// truth value for while loop
		xSize=1100, ySize=600;		// dimensions of window
	gfx_open(xSize,ySize,"Snow!");
	while(stillgoing){
		switch(gfx_wait()){
			case ' ':
				gfx_clear();
				int replay=1,				// gallery will display new snowflakes if space bar is hit in the middle of a display
					i,j,				// loop counters
					xPos[16]={0},yPos[16]={0},	// position of each snow flake
					r[16]={0},b[16]={0},g[16]={0},	// color values of each snowflake
					rad[16],			// size of each snowflake
					speed[16],			// vertical speed of each snowflake
					arms[16];			// number of arms of each snowflake
				double theta[16]={0}, dTheta[16];	// dTheta controls rotation speed of each snowflake
				char user;				// variable input while the snowflakes are falling
				while(replay){
					replay=0;
					for(i=0;i<=15;i++){
						while(xPos[i]<50 || xPos[i]>(xSize-50)) xPos[i]=rand()%xSize;
						yPos[i]=rand()%(ySize/2);
						while(r[i]+g[i]+b[i]<150){
							r[i]=rand()%255;
							g[i]=rand()%255;
							b[i]=rand()%255;;
						}
						rad[i]=(rand()%15)+8;
						dTheta[i]=pow(0.1,(rand()%4+1));
						speed[i]=rand()%20;
						arms[i]=rand()%4+3;
					}
					for(j=0;j<=400;j++){
						gfx_clear();
						for(i=0;i<=15;i++){	// draws 16 snowflakes
							gfx_color(r[i],g[i],b[i]);
							Snow(xPos[i],yPos[i]+(1+speed[i]/10.)*j,rad[i],theta[i]+=dTheta[i],arms[i] );
						}
						gfx_flush();
						usleep(20000);
						if(gfx_event_waiting()){
							user=gfx_wait();
							if(user=='q'){
								stillgoing=0;
								break;
							}else if(user==' '){	// if user hits space bar, new snowflakes will fall
								replay=1;
								break;
							}
						}
					}
				}
				break;
			case 'q':	// Quit
				stillgoing=0;
				break;
			default:
				break;
		}
	}
}

void Snow( int x1, int y1, double len, double phi, int arms )
{
	// Base case.
	if( len < 1 ) return;

	int i;
	// Draw the lines
	for(i=1;i<=arms;i++){
		gfx_line(x1,y1,x1+len*cos(i*6.28/arms+phi),y1+len*sin(i*6.28/arms+phi));
	}

	// Recursive calls
	for(i=1;i<=arms;i++){
		Snow( x1+len*cos(i*6.28/arms+phi), y1+len*sin(i*6.28/arms+phi), 0.36*len, phi, arms );
	}
}
