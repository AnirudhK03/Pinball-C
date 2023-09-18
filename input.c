
/* Anirudh Kondapaneni */

/* system includes go first */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "libpb.h"

#include "link.h"

#include "n2.h"
/* includes ball struct */ /*Added by Anirudh Kondapaneni */
#include "struct.h"

/* includes for constants and tyupes are next */
#include "debug.h"
#include "constants.h"

/* includes for functions go last */
#include "input.h"
#include "dynamicM.h"
#include "callbackFuncs.h"
#include "bits.h"
#include "output.h"
#include "physics.h"

//reads in balls as long as it can.
void readBall (struct Sim *table)
{

	unsigned char bits;
	int color, tokens;
	double x,y,vx,vy,theta,force;
	struct Ball ball;
	//this while-loop is from Neil Kirby code
	while ( 5 == (tokens = fscanf(table->fileptr,"%hhx %lf %lf %lf %lf", &ball.bits, &ball.x, &ball.y, &ball.theta, &ball.force)))
	{
	    
	    get_color(&ball);
	    //load message using temp ball struct.
	    load_message(&ball);
	    set_in_play(&ball);
	    //our diagnostic and launch will be taken care of inside addBalltoList func.
	    addBalltoList(ball,table);
	}

	if(TEXT)printf("Final scanf call returned %d\n\n", tokens);
}

//allocates memery for ball and adds it to list.
void addBalltoList(struct Ball ballCopy, struct Sim *table) 
{

	//allocate the ball memory
	
	struct Ball *ball = allocateBall();
	
	if (ball != NULL)
	{
	
	    *ball = ballCopy;
	    ball->simulation = table;
	    polar2cart(ball);

	    if (insert(&(table->in_play), ball, y_order, TEXT))
	    {
	        launch_message(ball);
	    } else 
	    {
	        freeBallFailInsert(ball, "in-play");
	    }

	} else 
	{
	    freeBallandMessage(ball);
	}
}



//moves/updates/physic-ify's the balls that are inside the list.
//I just chose random name cuz I didnt know what I wanted it to be. Technically this is 'kinda' like sim function but putting it in lab3.c felt weird so I kept it here.
void classicTateW (struct Sim *table)
{

	
	while(table->in_play != NULL) 
	{
	    if(TEXT)print_header(table);

	    if(TEXT)iterate(table->in_play,action_print_ball);
	    if(TEXT)printf("\n");

	    if(GRAPHICS)master_graphics(table);

	    table->time += DELTA_T;
	    iterate(table->in_play, action_update_ball);
	    deleteSome(&(table->in_play), off_table, action_move_to_off_play, TEXT);
	    sort(table->in_play,y_order);
	
	}

	miniTateW(table);

}

//final output including total score, each balls points, freeing balls, and the last 4 second wait time for graphics only.
void miniTateW (struct Sim *table)
{
	if(GRAPHICS)final_graphics(table);

	if(TEXT)printf("\nThe final score was %d points:\n", table->score);
	iterate(table->off_play, action_score_print);
	if(TEXT)printf("\n");
	int deleted_in_play = deleteSome(&(table->in_play), true_func, free_ball, TEXT);

	if(TEXT)printf("Deleted %d balls from in play list.\n", deleted_in_play);
	
	int deleted_off_play = deleteSome(&(table->off_play), off_table, action_free_ball,TEXT);
	if(TEXT)printf("Deleted %d balls from off table list.\n", deleted_off_play);

}

















