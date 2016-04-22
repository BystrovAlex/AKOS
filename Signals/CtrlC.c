#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main()
{
	signal (SIGINT, SIG_IGN);
	printf ("qwerty");
	fflush(stdout);
	while(0==0){}
	printf ("123456");
	fflush(stdout);
	return 0;
}
