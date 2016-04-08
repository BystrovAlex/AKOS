#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

char msg[1000];
char buf[1000];
int main()
{
	scanf ("%s", msg);
    struct sockaddr_in adr;
    int soc = socket(AF_INET, SOCK_STREAM, 0);
    if (soc<0) {
        perror("socket error");
        exit(1);
    }
    adr.sin_family = AF_INET;
    adr.sin_port = htons(5000);
    adr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(connect(soc, (struct sockaddr *)&adr, sizeof(adr)) < 0)
    {
        perror("connect error");
        exit(2);
    }
    send(soc, msg, 1000, 0);
    //close(soc);
    return 0;
}
