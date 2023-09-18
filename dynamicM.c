/* Anirudh Kondapaneni */
#include <stdio.h>
#include <stdlib.h>
#include "altmem.h"

#include "struct.h"
#include "output.h"
#include "dynamicM.h"

//allocates dynamic memory for the ball that is read in and prints diagnostic message if needed.
struct Ball *allocateBall()
{
	static int numBalls = 0;
	struct Ball *ballPtr =  alternative_malloc(sizeof(struct Ball));
	if (ballPtr != NULL)
	{
	    numBalls += 1;
	    allocateMessage(numBalls);
	
	}

	return ballPtr;
}

//frees ball memory for ball and prints diagnostic message.
void freeBall( struct Ball *tbfBall)
{

	static int numFree = 1;

	alternative_free(tbfBall);

	freeMessage(numFree);
	numFree+=1;

}

//frees ball memory with assocaited print
void freeBallandMessage(struct Ball *tbfBall)
{

	failAllocation();
	alternative_free(tbfBall);
}

//frees ball when failed to insert with associated print
void freeBallFailInsert(struct Ball *ball, char *listName)
{
	failInsertion(ball,listName);
	freeBall(ball);

}
