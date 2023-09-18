/* Anirudh Kondapaneni */

#include <stdio.h>

struct Sim {
	double time;
	int score;
	void *in_play;
	void *off_play;
	FILE *fileptr;

};

struct Ball {
	unsigned char bits;
	int color;
	double x;
	double y;
	double vx;
	double vy;
	double theta;
	double force;
	struct Sim *simulation;
};
