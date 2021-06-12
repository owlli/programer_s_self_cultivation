#include <stdio.h>
#include <unistd.h>

static int a;
static int *ptra = &a;

void foobar(int i)
{
	printf("Printing from Lib.so %d\n", i);
	sleep(-1);
}
