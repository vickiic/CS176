#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<poll.h>
#include<sys/time.h>
#include<stdio.h>
long getmilli_sec()
{
    struct timeval tpp;
    gettimeofday(&tpp, NULL);
    long mss = tpp.tv_sec * 1000 + tpp.tv_usec / 1000;
    return mss;
    
}
void append(char *str1,char *str2)
{
    int len1=strlen(str1);
    int len2=strlen(str2);
    for(int i=len1,j=0;j<len2;i++,j++)
        str1[i]=str2[j];
}
char int_to_char (int a)
{
    if (a==0)
        return '0';
    else if (a==1)
        return '1';
    else if (a==2)
        return '2';
    else if (a==3)
        return '3';
    else if (a==4)
        return '4';
    else if (a==5)
        return '5';
    else if (a==6)
        return '6';
    else if (a==7)
        return '7';
    else if (a==8)
        return '8';
    else if (a==9)
        return '9';
}
int getlength(long a)
{
    int i=0;
    for(;(a/10)>0;i++)
    {
        a=a/10;
    }
    return i+1;
}
void convertToCharArray(char *arr,long a)
{
    int len=getlength(a);
    for(int i=len-1;i>=0;i--)
    {
        arr[i]= int_to_char(a%10);
        a=a/10;
    }
}

void print_stats(long *rtts,int nrcvd)
{
    printf("---Ping Stats---\n");
    double p_age=(nrcvd/10.0)*100;
    printf("Percentage of packet loss:\t%f\n",p_age);
    long min=rtts[0];
    long max=rtts[0];
    long sum=0;
    for(int i=1;i<10;i++)
    {
        if (rtts[i] <min)
            min=rtts[i];
        if (rtts[i] >max)
            max=rtts[i];
        sum+=rtts[i];
    }
    printf("Min RTT:\t%d\n",min);
    printf("Max RTT:\t%d\n",max);
    printf("Avg RTT:\t%d\n",sum/nrcvd);
    
}
int main()
{
    int port=1236;
    int sockfd;
    long rtts[10];
    
    char data[100];
    char p[20];
    int nrcvd=0;
    
    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in serv;
    
    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    
    for(int i=0;i<10;i++)
    {
        memset(&data[0], 0, sizeof(data));
        append(data,"PING");
        long mss=getmilli_sec();
        
        memset(&p[0], 0, sizeof(p));
        convertToCharArray(&p[0],mss);
        
        append(data," ");
        
        char temp[2];
        memset(&temp[0], 0, sizeof(temp));
        
        if (i<9)
        {
            temp[0]= int_to_char(i+1);
            append(data,temp);
        }
        else
            append(data,"10");
        append(data," ");
        
        append(data,p);
        socklen_t m = sizeof(serv);
        sendto(sockfd,data,strlen(data),0,(struct sockaddr *)&serv,m);
        
        memset(&data[0], 0, sizeof(data));
        
        struct pollfd fd;
        int ret;
        
        fd.fd = sockfd; // your socket handler 
        fd.events = POLLIN;
        ret = poll(&fd, 1, 1000); // 1 second for timeout
        switch (ret) 
        {
            case -1:
                break;
            case 0:
                rtts[i]=getmilli_sec()-mss;
                // Timeout 
                break;
            default:
                recv(sockfd,data,sizeof(data), 0); // get your data
                printf("Reply Recieved from server:");
                printf("\t%s\n",data);
                nrcvd++;
                rtts[i]=getmilli_sec()-mss;
                break;
        }		
    }
    print_stats(rtts,nrcvd);	
}

