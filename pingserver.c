#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int sockfd, n;
    int arr[10]; //x packets transmitted, y received
    int x=0, y=0, MIN=0, AVG=0, MAX=0, tm;   // Z% packet loss
    double z;
    long int time1;
    struct sockaddr_in servaddr,cliaddr;
    char sendline[1000],seq[100],timeSt[100];
    char mesg[1000],tmp1[20],tmp2[20], tmp3[20];
    char recvline[1000]
    struct timeval tv, start, end;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    
    if (argc != 3)
    {
        exit(1);
    }
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=inet_addr(argv[1]);
    servaddr.sin_port=htons(atoi(argv[2]));
    
    
    if(setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) <0){
        perror("Error");
    };
    
    
    for(int i=0; i<10; i++)
    {
    TAG:
        strcpy(sendline, "PING ");
        sprintf(seq, "%d", i);
        strcat(sendline, seq);
        
        gettimeofday(&start, NULL);
        sendto(sockfd,sendline,strlen(sendline),0,
               (struct sockaddr *)&servaddr,sizeof(servaddr));
        
        n = recvfrom(sockfd,recvline,10000,0,NULL,NULL);
        gettimeofday(&end, NULL);
        x++;y++;
        if (strlen(recvline)== 0)
        {
            y--;
            goto TAG;
        }
        sprintf(timeSt, "%ld", ((end.tv_sec * 1000000 + end.tv_usec)
                                - (start.tv_sec * 1000000 + start.tv_usec))/1000);
        tm = ((end.tv_sec * 1000000 + end.tv_usec)
              - (start.tv_sec * 1000000 + start.tv_usec))/1000;
        arr[i]=tm;
        strcat(sendline, timeSt);
        memset(&sendline[0], 0, sizeof(sendline));

        strcpy(mesg,"PING received from ");
        strcat(mesg, argv[2]);
        strcpy(tmp1,": seq#=");
        strcat(mesg, tmp1);
        strcat(mesg, seq);
        strcpy(tmp2, " time=");
        strcat(mesg, tmp2);
        strcat(mesg, timeSt);
        strcpy(tmp3, " ms");
        strcat(mesg, tmp3);
        
        // printf("%s -------- %s -------\n", recvline, mesg);
        // --- ping statistics --- X packets transmitted, Y received, Z% packet loss rtt min/avg/max = MIN AVG MAX ms
        printf("%s\n", mesg);
        
        memset(&recvline[0], 0, sizeof(recvline));
        sleep(1);
    }
    close(sockfd);
    
    // for (int i = 0; i < 10; ++i)
    // {
    // 	printf("%d\n", arr[i]);
    // }
    int sum=0;
    MAX = arr[0];
    MIN = arr[0];
    for (int i = 0; i < 10; ++i)
    {
        if (arr[i]>MAX)
        {
            MAX = arr[i];
        }
        if (arr[i]<MIN)
        {
            MIN = arr[i];
        }
        sum+=arr[i];
    }
    
    printf("--- ping statistics --- %d packets transmitted, %d received, %f%% packet loss rtt min/avg/max = %d %d %d ms\n", x, y, (double)(100-((double)y*100/(double)x)), MIN, sum/10, MAX);
    return 0;
}
