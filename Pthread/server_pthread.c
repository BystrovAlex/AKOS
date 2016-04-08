#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>



void *func(void *arg)
{	
	int soc=*(int*)arg;
	struct sockaddr_in adr;
	adr.sin_family=AF_INET;
	adr.sin_port=htons(5000);
	adr.sin_addr.s_addr=htonl(INADDR_ANY);	
	int bytes;
	char buf[1000];	
	freopen("tmp.txt", "a", stdout);	
	bytes=recv(soc, buf, 1000, 0);
	if (bytes==-1) {
		perror("bytes");
		exit(5);
	}
	else printf ("%s\n", buf);	
}

int main()
{
	freopen ("tmp.txt", "w", stdout);
    
    int soc, lis;
    //char buf[1000];
    //int bytes;
    lis=socket(AF_INET, SOCK_STREAM, 0);
    if (lis<0)
    {
        perror("socket error");
        exit (1);
    }
    struct sockaddr_in adr;
	adr.sin_family=AF_INET;
	adr.sin_port=htons(5000);
	adr.sin_addr.s_addr=htonl(INADDR_ANY);
	pthread_t thread;
	int ret;
    if(bind(lis, (struct sockaddr *)&adr, sizeof(adr)) < 0)
    {
        perror("bind error");
        exit(2);
    }
    listen(lis, 1);
    while (1) {
	soc=accept(lis, NULL, NULL);
	if (soc<0)
	{
	    perror("accept error");
	    exit(3);
	}
	pthread_create(&thread, NULL, func, &soc);	
	
	//bytes=recv(soc, buf, 1000, 0);
	//printf ("%s\n", buf);	
	pthread_join(thread, NULL);
	//close (soc);
    }
    return 0;
}
