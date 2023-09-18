/* Anirudh Kondapaneni */

void constraints(struct Ball *ball);
void left_paddle(struct Ball *ball);
void move(double dt, struct Ball *ball);
bool on_table(struct Ball *ball);
void polar2cart(struct Ball *ball);
void update_ball(struct Ball *ball);
