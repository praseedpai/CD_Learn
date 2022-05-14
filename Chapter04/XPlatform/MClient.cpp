/////////////////////////////////////////////// 
//
// Socket Client Application
//
#ifdef WINDOWS_OS
	#include <windows.h>
#else
                #include <sys/socket.h>
                #include <netinet/in.h>
                #include <arpa/inet.h>
                #include <netdb.h>
                #include <pthread.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
/////////////////////////////
//
// Helper Function To Start Socket
// 
bool StartSocket();

///////////////////////////
//
//  
//
//
char ServerName[255];   
unsigned short PortNumber;        
struct sockaddr_in Server; 
struct hostent     *HostPointer; 
unsigned int addr; 

  
#ifdef WINDOWS_OS
SOCKET ConnectSock; 
void Cleanup() {WSACleanup();} 

bool StartSocket()
{
  WORD Ver;
  WSADATA wsd;
  Ver = MAKEWORD( 2, 2 );
  if (WSAStartup(Ver,&wsd) == SOCKET_ERROR) 
  {
	WSACleanup();
	return false;
  }

  return true;
}
int SocketGetLastError()
{
       return  WSAGetLastError();
}

int CloseSocket( SOCKET s ) {
           closesocket(s);
           return 0;
}
#else
 int ConnectSock;
void Cleanup() {} 
bool StartSocket(){return true;}
int SocketGetLastError(){return  0xFFFF;}
#define SOCKET_ERROR (-1) 
int CloseSocket( int s ) {shutdown (s, 2); return 0;}
#endif
char Buffer[128];
char bfr[255];
/////////////////////////////////////
//
//
//
//

int main(int argc, char* argv[])
{

	if ( argc != 4 )
	{
      		fprintf(stdout,"Usage: Client <ServerName ><portid> <message> \n");  
      		return 1;
	}

	if ( !StartSocket() )
	{
      		fprintf(stdout,"Failed To Initialize Socket Library\n");
	  	return 1;
	}

	strcpy(ServerName,argv[1] );
	PortNumber = atoi(argv[2]);


   
	if (isalpha(ServerName[0])) {   
		HostPointer= gethostbyname(ServerName);
	}
	else  { /* Convert nnn.nnn address to a usable one */
		addr = inet_addr(ServerName);
		HostPointer = gethostbyaddr((char *)&addr,4,AF_INET);
	}
	if (HostPointer == NULL ) {
		fprintf(stderr,"Client: Cannot resolve address [%s]: Error %d\n",
			ServerName,SocketGetLastError());
		
		exit(1);
	}
                
	printf("*");
    	printf(" **");
    	memset(&Server,0,sizeof(Server));
	printf(" ***\n");
    	memcpy(&(Server.sin_addr),HostPointer->h_addr,HostPointer->h_length);
	Server.sin_family = HostPointer->h_addrtype;
	Server.sin_port = htons(PortNumber);
	printf("***");   
                  printf("\n");
                  fflush(stdout);

	
	ConnectSock = socket(AF_INET,SOCK_STREAM,0); 
	if (ConnectSock <0 ) {
		fprintf(stderr,"Client: Error Opening socket: Error %d\n",
			SocketGetLastError());
		Cleanup();
		return -1;
	}


	if (connect(ConnectSock,
		(struct sockaddr*)&Server,
		sizeof(Server))
		== SOCKET_ERROR) {
		fprintf(stderr,"connect() failed: %d\n",SocketGetLastError());
		Cleanup();
		return -1;
	}
    
    
   
    while (1) {
            
                             printf("Helllo......\n");
                            #ifdef WINDOWS_OS
		gets_s(Buffer);
                            #else
                                   fgets(Buffer,200,stdin);
                            #endif
                            if (strncmp(Buffer,"END",3) == 0 ){break;}
                            int RetVal = send(ConnectSock,Buffer,strlen(Buffer),0);
                            if (RetVal == SOCKET_ERROR) {
	 	fprintf(stderr,"send() failed: error %d\n",SocketGetLastError());
		Cleanup();
		return -1;
	         }
                           continue; 
                   }
                   CloseSocket(ConnectSock);
	 Cleanup();
                   return 0;
}
//--- EOF MClient.cpp



