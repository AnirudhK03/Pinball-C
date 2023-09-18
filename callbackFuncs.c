/* Anirudh Kondapaneni */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libpb.h"
#include "debug.h"

//#include "linkedlist.h"
#include "link.h"

//I just decided include almost all .h because sometimes compliler would complain.
#include "struct.h"
#include "dynamicM.h"
#include "output.h"
#include "physics.h"
#include "callbackFuncs.h"

/* Comparison Functions */

//used for insert so that it places balls in decreasing y order.
bool y_order (void *moreY, void *lessY)
{

	struct Ball *moreYball = moreY;
	struct Ball *lessYball = lessY;
	
	return moreYball->y >= lessYball->y;

}

//comparison function used for sorting by vy
bool vy_order (void *moreVY, void *lessVY)
{

	struct Ball *moreVYball = moreVY;
	struct Ball *lessVYball = lessVY;

	return moreVYball->vy >= lessVYball->vy;
}

//returns true for comparison
bool true_func(void *data)
{
	return 1;

}

/*Criteria Function */

//returns true if ball is off table
bool off_table(void *yolo)
{

	struct Ball *ball = yolo;
	return !(on_table(ball));

}


/* Action Functions */

//action function that draws the ball
void action_draw_ball (void *data)
{
	struct Ball *ball = data;
	draw_ball(ball);
}

//action function that updates the ball from polar to rectangular coords.
void action_polar2cart (void *data)
{

	struct Ball *ball = data;
	polar2cart(ball);
}

//action function that moves/updates the ball.
void action_update_ball(void *data)
{

	struct Ball *ball = data;
	update_ball(ball);

}

//action function to put ball into off_table list
void action_move_to_off_play(void *data)
{

	struct Ball *ball = data;
	off_message(ball);
	struct Sim *table = ball->simulation;
	if(insert(&(table->off_play), ball, vy_order, TEXT))
	{
		if(TEXT)printf("%d points\n", -((int) ball->vy));
		table->score += -((int) ball->vy);
	} else
	{
		freeBallFailInsert(ball, "off-play");
	}
}



//action function that frees the ball if ball is lower than table.
void action_free_ball(void *data)
{
	struct Ball *ball = data;
	freeBall(ball);
	
}

//action function that prints balls using tabular output.
void action_print_ball(void *data)
{
	struct Ball *ball = data;
	if(TEXT)print_ball(ball);

}

//prints all the balls and there respective score
void action_score_print(void *data)
{

	struct Ball *ball = data;
	if(TEXT)print_score(ball);

}

//free balls for the in play list
void free_ball(void *data)
{
	struct Ball *ball = data;
	free(ball);

}







