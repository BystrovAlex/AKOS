#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
	freopen ("tmp.txt", "w", stdout);
    struct sockaddr_in adr;
    int soc, lis;
    char buf[1000];
    int bytes;
    lis=socket(AF_INET, SOCK_STREAM, 0);
    if (lis < 0)
    {
        perror("socket error");
        exit(1);
    }
    adr.sin_family = AF_INET;
    adr.sin_port = htons(5000);
    adr.sin_addr.s_addr = htonl(INADDR_ANY);
	pid_t child;
	int ret;
    if(bind(lis, (struct sockaddr *)&adr, sizeof(adr)) < 0)
    {
        perror("bind error");
        exit(2);
    }
    listen(lis, 1);
    while (1) {
	soc=accept(lis, NULL, NULL);
	if (soc < 0)
	{
	    perror("accept error");
	    exit(3);
	}
	child=fork();
	if (child == -1) {
		perror ("fork error");
		exit(4);
	}
	if (child == 0) {	
		bytes=recv(soc, buf, 1000, 0);
		printf ("%s\n", buf);
		exit(ret);	
	} else wait();
	//close (soc);
    }
    return 0;
}
