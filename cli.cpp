#include<iostream>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdio.h>
using namespace std;
#define PORT 5555
#define MAXSIZE 10000

int main(int argc,char * argv[])
{
  int fd;
  struct sockaddr_in server,client;
  struct hostent *hp;
  char buf[MAXSIZE];
  
  server.sin_family=AF_INET;
  server.sin_addr.s_addr=INADDR_ANY;
  server.sin_port=htons(PORT);
  
  fd=socket(AF_INET,SOCK_STREAM,0);
  if(fd<0){
    cout<<"Error creating socket\n";
    return 0;
  }
    cout<<"Socket Created\n";
    
    hp=gethostbyname(argv[1]);
    bcopy((char*)hp->h_addr,(char*)&server.sin_addr.s_addr,hp->h_length);
  
    int con;
    con=connect(fd,(struct sockaddr*)&server,sizeof(struct sockaddr));
    
    if(con<0){
      cout<<"Error connecting\n";
    return 0;
    }
    
    cout<<"\nConnection has been made\n\n";
    
    /*
    while(rec=recv(fd,buf,1000,0)){
      if(rec<0){
	cout<<"Error receiving\n";
	return 0;
      }
      cout<<buf;
    }
    */
    
    cout<<"Enter message to send\n";
    for(int i=0;i<50;i++){
      buf[i]=' ';
      cin>>buf[i];
    }
    
  send(fd,buf,sizeof(buf),0);
  close(fd);
  //cout<<"Socket closed\n";
  return 0;
}
