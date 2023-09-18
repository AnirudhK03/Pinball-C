
/* Copyright 2023, Neil Kirby.  Not for disclosure without permission */
/* Function linkedlist_sim() written by Ani */

/* system includes go first */
#include <stdio.h>
#include <stdbool.h>
#include "libpb.h"

/* includes ball struct */ /*Added by Anirudh Kondapaneni */
#include "struct.h"


/* includes for constants and tyupes are next */
#include "debug.h"
#include "constants.h"

/* includes for functions go last */
#include "dynamicM.h"
#include "callbackFuncs.h"
#include "n2.h"
#include "output.h"
#include "physics.h"
#include "bits.h"
#include "input.h"
#include "lab4.h"


//simulation for the ball using structs and linked lists.
void linkedlist_sim(FILE *fileptr)
{

	struct Sim world = {0.0, 0, NULL, NULL,fileptr};
	struct Sim *table = &world;

	readBall(table);
	classicTateW(table);

}

//initalizes the graphics based on debug.h.
bool init()
{
	return(TEXT || ( GRAPHICS && pb_initialize()));

}

//teardowns the grpahics/turns it "off".
void teardown()
{
	if(GRAPHICS)pb_teardown();
}

//starts the intilization and calls the sim
void startSim(FILE *fileptr)
{
	if(init())
	{
		linkedlist_sim(fileptr);
		teardown();	
	}

}

//closes the file and prints the diagnostic.
void closeFilePtr(FILE *fileptr)
{
	int check = fclose(fileptr);
	if (check == 0)
	{
		if(TEXT)printf("DIAGNOSTIC: Input file closed.\n");
	} else 
	{
		if(TEXT)printf("ERROR: File not closed properly\n");
	}

}

//main function that keeps track of overall running time and runs the sim.
int main(int argc, char *argv[])
{

	double start, runtime;
	start= now();

	if (argc < 2)
	{
		InsufficentArgs(argc);
	
	} else if(argc >= 3)
	{
		BonusCodeNotPresent();
	} else if (argc == 2)
	{
		FILE *fileptr = fopen(argv[1] ,"r");

		if(CheckFilePtr(fileptr, argv[1]))
		{
			startSim(fileptr);
			closeFilePtr(fileptr);
		}

	}

	runtime = now() - start;
	printf("Total runtime is %.9lf seconds\n", runtime);
	return 0;
}

