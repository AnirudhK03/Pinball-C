
#include <stdio.h>

void s_test()
{
	static int count = 0;

	count++;
	printf("s_test has been called %d times\n", count);
}

int main()
{
	s_test();
	s_test();
	s_test();
}
