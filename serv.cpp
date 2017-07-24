#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>

using namespace std;

#define PORT 5555
#define BACKLOG 3

int main(){

  int fd,fd2;
  struct sockaddr_in server,client;

  int bytes;

  char buf[50];
  for(int i=0;i<50;i++)
    buf[i]=' ';

  fd=socket(AF_INET,SOCK_STREAM,0);
  if(fd<0){
    cout<<"Error creating socket\n";
    return 0;
  }

  cout<<"Socket successfully created\n\n";
  server.sin_family=AF_INET;
  server.sin_port=htons(PORT);
  server.sin_addr.s_addr=INADDR_ANY; 

  int bnd;

  bnd=bind(fd,(struct sockaddr*)&server,sizeof(server));
  if(bnd<0){
    cout<<"Error binding socket\n";
    return 0;
  }
  cout<<"Binding successful\n\n";

  if(listen(fd,BACKLOG)<0){
    cout<<"Error listening\n";
    return 0;
  }

  cout<<"Server is listeninig\n";
  
  socklen_t len=sizeof(client);
  fd2=accept(fd,(struct sockaddr*)&client,&len);
  if(fd2<0){
    cout<<"Error accepting\n";
    return 0;
  }
  
  cout<<"Accept successful\n";
  
  bytes=recv(fd2,buf,sizeof(buf),0);
  if(bytes<0){
    cout<<"Error receiving\n";
    return 0;
  }
  cout<<"\nClient message : ";
  cout<<buf<<endl;

  close(fd2);
  close(fd);
  shutdown(fd,0);
  cout<<"\nSocket closed\n";
  return 0;
}
