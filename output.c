
/* Copyright 2023, Neil Kirby.  Not for disclosure without permission */

//Edits made by Anirudh Kondapaneni
/* Almost all functions were edited by Ani to support structs */

/* system includes go first */
#include <stdio.h>
#include <stdbool.h>
#include "link.h"

#include "libpb.h"
#include "n2.h"

/* includes ball struct */ /*Added by Anirudh Kondapaneni */
#include "struct.h"

/* includes for constants and tyupes are next */
#include "debug.h"
#include "constants.h"

/* includes for functions go last */
#include "callbackFuncs.h"
#include "bits.h"
#include "output.h"

/* functions internal to this file go here at the top */

/* Edit by Ani...Got rid of all the static keyword in-front of the functions because it was causing a error when I tried to call the functions in a different file*/


//Prints headers for tabular output.
void print_header(struct Sim *table)
{
	/* VY can hit -100, so it needs more room */
	if(TEXT)printf("%7s %2s   %9s %9s  %9s %10s    ET=%9.6lf   Score=%d\n",
	"Color","ST", "___X_____", "___Y_____", "___VX____", "____VY____", table->time, table->score);

}

//prints the ball value. Edited by Ani to support structs.
void print_ball(struct Ball *ball)
{
	char *colorString = getColorString(ball->color);	
	/* VY can hit -100, so it needs more room */
	if(TEXT)printf("%7s %02X   %9.5lf %9.5lf  %9.5lf %10.5lf\n",
	   colorString,ball->bits, ball->x, ball->y, ball->vx, ball->vy);

}

//draws ball for graphical output. Edited by Ani to support structs.
void draw_ball(struct Ball *ball)
{
	
	pb_ball(ball->color, ball->x, ball->y);
}

//print headers and ball. Edited by Ani to support structs.
void master_text(struct Ball *ball)
{
	print_header(ball->simulation);
	print_ball(ball);
	printf("\n");
}

//output for graphics, such as drawing and refreshing. Edited by Ani to support structs.
void master_graphics(struct Sim *table)
{
	double et = table->time;
	int score = table->score;
	pb_clear();
	iterate(table->in_play, action_draw_ball);
	pb_left();
	pb_right();
	pb_score(score);
	pb_time( (int) et * 1000);
	pb_refresh();

	microsleep( (unsigned int)(DELTA_T * 1000000.0));
}

//final graphics waits a little bit before outputting. Edited by Ani to refresh so it keeps score and flippers on screen.   
void final_graphics(struct Sim *table)
{
	int score = table->score;
	double et = table->time;
        double wait = 0.0;

        while(wait < 4.0)
        {
            pb_clear();
            pb_time( (int) et * 1000);
	    pb_score(score);
	    pb_left();
	    pb_right();
            pb_refresh();

            microsleep( (unsigned int)(DELTA_T * 1000000.0));
            wait += DELTA_T;
        }
}


/* public functions below here **********************************/

//Final message when ball is off table. Edited by Ani to reflect changes made in other functions.
void final_output(struct Ball *ball)
{
	off_message(ball);
	//if(GRAPHICS)final_graphics(ball);

}

//load message for ball. Edited by Ani to support structs.
void load_message(struct Ball *ball)
{
	char *colorString = getColorString(ball->color);
	if(GRAPHICS)pb_status("Loaded");
	if(TEXT)printf("Loaded %7s %02X %d ball at %9.5lf, %9.5lf %9.5lf deg %9.5lf ips\n",
    		colorString,ball->bits, ball->color, ball->x, ball->y, ball->theta, ball->force);

}

//launch message for ball. Edited by Ani to support structs.
void launch_message(struct Ball *ball)
{

	char *colorString = getColorString(ball->color);
	if(GRAPHICS)pb_status("Launch");
	if(TEXT)printf("Launched %7s %02X %d ball at %9.5lf, %9.5lf at %9.5lf, %9.5lf\n",
    		colorString,ball->bits, ball->color, ball->x, ball->y, ball->vx, ball->vy);

}


/* not technically public but it goes right next to the funcitons that call
 * it */

//Higher level output function that prints hit wall messages.
void x_message( char *string, struct Ball *ball)
{
	char *colorString = getColorString(ball->color);
    if(TEXT) printf("%s: %7s %02X    %9.5lf %9.5lf    %9.5lf %10.5lf\n",
	    string,colorString,ball->bits, ball->x, ball->y, ball->vx, ball->vy );

	if(GRAPHICS)pb_status(string);
}

//prints output for left flipper.
void left_paddle_message(struct Ball *ball)
{
	x_message("Left_ flipper", ball);
}

//prints output for right flipper.
void right_paddle_message(struct Ball *ball)
{
	x_message("Right flipper", ball);
}

//prints if ball hit left wall. Edited by Ani.
void left_message(struct Ball *ball)
{
    x_message("Left_ wall", ball);
}

//prints if ball hit right wall. Edited by Ani
void right_message(struct Ball *ball)
{
    x_message("Right wall", ball);
}

//prints if ball hit top wall. Edited by Ani.
void top_message(struct Ball *ball)
{
    x_message("Upper wall", ball);
}

//prints off message output. Edited by Ani.
void off_message(struct Ball *ball)
{
    x_message("Off table", ball);
}


/* DIAGNOSTIC MESSAGES FOR dynamicM.c */

//Written by Ani.
//print message for diagnostic
void allocateMessage(int numBalls)
{

	if(TEXT)printf("DIAGNOSTIC: %d balls allocated.\n", numBalls);

}

//Written by Ani
//print message for freeing ball
void freeMessage(int numFree)
{

	if(TEXT)printf("DIAGNOSTIC: %d balls freed.\n", numFree);

}

//written by Ani
//prints the bit and the score of the ball.
void print_score(struct Ball *ball)
{
	char *colorString = getColorString(ball->color);
	if(TEXT)printf("%7s %hhX     %d points\n",colorString,ball->bits, -(int)ball->vy);
}


//prints an error if the args passed on the command line are not the required amount
void InsufficentArgs(int argc)
{
	printf("ERROR: Insufficent arguments (argc is %d).\n",argc);
}

//prints since the bonus code is not present.
void BonusCodeNotPresent()
{
	printf("ERROR: Bonus Code is not present.\n");
}

//checks wether the file ptr is valid or not
int CheckFilePtr(FILE *fileptr,char *nameOfFile)
{

	if (fileptr == NULL)
	{
		printf("ERROR: Unable to open this %s for reading.\n",nameOfFile);
		return 0;
	} else 
	{
		if(TEXT)printf("Successfully opened %s for reading\n",nameOfFile);
		return 1;
	}
}

//output for when the ball fails to allocate
void failAllocation()
{
	printf("ERROR: failed to allocate ball\n");
}


//output for when insert to linked list fails
void failInsertion(struct Ball *ball, char *listName)
{
	printf("ERROR: Unable to insert into %s list, freeing %hhX\n",listName, ball->bits);

}







