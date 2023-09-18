
/* Copyright 2023 Neil Kirby, not for disclosure */
//Edits made by Anirudh Kondapaneni
//all methods edited by Ani to support structs.
//
/* All physics goes here */

#define GRAVITY	(-47.052534795)	/* inches per second per second */
#define LEFT_LIMIT	(-12.0)
#define RIGHT_LIMIT	(12.0)
#define UPPER_LIMIT	(48.0)
#define LOWER_LIMIT	(0.0)
#define INELASTIC	(0.95)

//#defiines included by Ani
#define LFLside (-5.0)
#define LFRside (-2.0)
#define RFLside 2.0
#define RFRside 5.0
#define TOPFLIPPER 1.0
#define BOTTOMFLIPPER 0.0
#define VYFLIP 75.0
#define YFLIP 1.0
#define VXFLIP 6.4

#include <stdbool.h>
#include <math.h>

/* includes ball struct */ /*Added by Anirudh Kondapaneni */
#include "struct.h"

#include "constants.h"

#include "output.h"

/* validate my own header file */
#include "physics.h"


//checks if ball is below lower limit.
bool on_table(struct Ball *ball)
{
	//updated function so it uses struct. Edit made by Ani.
	return( ball->y >= LOWER_LIMIT);
}

//checks if ball has hit the right paddle
static void right_paddle(struct Ball *ball)
{

	if (RFLside <= ball->x && ball->x <= RFRside && BOTTOMFLIPPER <= ball->y && ball->y <= TOPFLIPPER)
	{
	    right_paddle_message(ball);
	    ball->vy += VYFLIP;
	    ball->y += YFLIP;
	    ball->vx += -(VXFLIP);
	}

}

//checks if ball has left paddle
//I had to make this not static because I used for prototype.
void left_paddle(struct Ball *ball)
{

	if (LFLside <= ball->x && ball->x <= LFRside && BOTTOMFLIPPER <= ball->y && ball->y <= TOPFLIPPER)
	{
	    left_paddle_message(ball);
	    ball->vy += VYFLIP;
	    ball->y += YFLIP;
	    ball->vx += VXFLIP;
	
	}

}

//checks if ball is past left wall and changes values accordingly.
static void left_wall(struct Ball *ball)
{
	if(ball->x < LEFT_LIMIT)
	{
	    //changed the function so it uses struct. Edit made by Ani.
	    left_message(ball);
	    ball->x = 2.0 * LEFT_LIMIT - (ball->x);
	    ball->vx = -(ball->vx);
	    ball->vx *= INELASTIC;
	    ball->vy *= INELASTIC;
	}
}

//checks if ball is past left wall and chnages values accordingly.
static void right_wall(struct Ball *ball)
{
	//update the function so it uses struct. Edit made by Ani.
	if(ball->x > RIGHT_LIMIT)
	{
	    right_message(ball);
	    ball->x = 2.0 * RIGHT_LIMIT - (ball->x);
	    ball->vx = -(ball->vx);
	    ball->vx *= INELASTIC;
	    ball->vy *= INELASTIC;
	}
}

//checks of ball is past top wall and changes values accordingly.
static void top_wall(struct Ball *ball)
{
	//updated function so it uses struct. Edit made by Ani.
	if(ball->y > UPPER_LIMIT)
	{
	    top_message(ball);
	    ball->y = 2.0 * UPPER_LIMIT - (ball->y);
	    ball->vy = -(ball->vy);
	    ball->vx *= INELASTIC;
	    ball->vy *= INELASTIC;
	}
}

//checks constraints. Edited by Ani.
void constraints(struct Ball *ball)
{
	//Updated funtions. Edit by Ani.
	left_paddle(ball);
	right_paddle(ball);
	left_wall(ball);
	right_wall(ball);
	top_wall(ball);
}

//updates the ball by moving ball and checking constraints. Edited by Ani, so it uses struct.
void update_ball(struct Ball *ball)
{
	move(DELTA_T, ball);
	constraints(ball);
}

//moves the ball as time moves.
void move(double dt, struct Ball *ball)
{
	//changed function so it uses struct. Edit made by Ani.
	/* position first, then velocity */
	ball->x += (ball->vx) * dt;
	ball->y += (ball->vy) * dt + 0.5 * GRAVITY * dt * dt;
	/* no change in VX */
	ball->vy += GRAVITY * dt;
}

//changes the polar coords to rectangular coords.
void polar2cart(struct Ball *ball)
{
	//updated function so it uses struct. Edit by Ani. The magic number of 180.0 was kept since it was Prof. Kirby code.
	double computedVX = (ball->force) * cos( (ball->theta) * M_PI / 180.0 );
	double computedVY = (ball->force) * sin( (ball->theta) * M_PI / 180.0 );

	ball->vx = computedVX;
	ball->vy = computedVY;
}
