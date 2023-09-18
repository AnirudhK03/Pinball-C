
/* Copyright 2023 Neil Kirby, not for disclosure */

#include "struct.h"
#include "bits.h"

#define COLOR_SHIFT 3
#define COLOR_MASK 7

#define STATUS_SHIFT 6
#define STATUS_MASK 7

#define STATUS_IN_PLAY 2

//sets bits of ball to be in play. Edited by Ani to support structs.
void set_in_play(struct Ball *ball)
{
	unsigned char bits = ball->bits;
	/* don't take this as mgic, work out how it works */
	bits = bits &  ( ~( (unsigned char)STATUS_MASK << STATUS_SHIFT));
	bits = bits | ( (unsigned char)STATUS_IN_PLAY <<STATUS_SHIFT);
	ball->bits = bits;
}

//Gets color from bits of ball. Edited by Ani to support structs.
void get_color(struct Ball *ball)
{
	int color = (ball->bits >> COLOR_SHIFT) & COLOR_MASK;

	ball->color=color;
}

//Made by Ani
//Method returns the color of the ball in String form.
char *getColorString(int index)
{

	static char *arrayOfColors[] = {
	    "Black", 
	    "Red", 
	    "Green",
	    "Yellow",
	    "Blue",
	    "Magenta",
	    "Cyan",
	    "White"
	    };

	return arrayOfColors[index];

}
