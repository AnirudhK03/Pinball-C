/* Anirudh Kondapaneni */

void BonusCodeNotPresent();
int CheckFilePtr(FILE *fileptr,char *nameOfFile);
void InsufficentArgs(int argc);
void allocateMessage(int numBalls);
void draw_ball(struct Ball *ball);
void failAllocation();
void failInsertion(struct Ball *ball, char *listName);
void final_graphics(struct Sim *table);
void final_output(struct Ball *ball);
void freeMessage(int numFree);
void launch_message(struct Ball *ball);
void left_message(struct Ball *ball);
void left_paddle_message(struct Ball *ball);
void load_message(struct Ball *ball);
void master_graphics(struct Sim *table);
void master_text(struct Ball *ball);
void off_message(struct Ball *ball);
void print_ball(struct Ball *ball);
void print_header(struct Sim *table);
void print_score(struct Ball *ball);
void right_message(struct Ball *ball);
void right_paddle_message(struct Ball *ball);
void top_message(struct Ball *ball);
void x_message( char *string, struct Ball *ball);
