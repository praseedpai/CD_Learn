// Server.cpp : Defines the entry point for the console application.
// under POSIX
// g++ -o Mserver.exe Mserver.cpp -lpthread
// ./Mserver.exe <port>
// under Windows
// cl /DWINDOWS_OS MServer.cpp ws2_32.lib
// Mserver <port>
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
////////////////////////////////

bool StartSocket(); //--- Initialize Socket Engine ..No code inside the Posix

#ifdef WINDOWS_OS
typedef struct{
 	SOCKET Sh; // Socket Handle which represents a Client
}CLIENT_DATA; 
//---------------- Socket Descriptor for Windows 
//---------------- Listener Socket => Accepts Connection
//---------------- Incoming Socket is Socket Per Client
SOCKET ListnerSocket;
SOCKET InComingSocket;
//----------------- Thread Entry Points for Listener and Thread Per Client
DWORD WINAPI ListenThreadProc( LPVOID lpParameter);
DWORD WINAPI ClientThreadProc( LPVOID lpParam   );
//--------------- Call WSACleanUP for resource de-allocation
void Cleanup() {
      WSACleanup();
} 
//------------ Initialize WinSock Library
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
//-----------------Get Last Socket Error
int SocketGetLastError(){ return  WSAGetLastError();}
//----------------- Close Socket
int CloseSocket( SOCKET s ) { closesocket(s); return 0;}

/* This is the critical section object (statically allocated). */
CRITICAL_SECTION m_CriticalSection;

void InitializeLock() {
	InitializeCriticalSection(&m_CriticalSection);
}
	
void AcquireLock( ) {
                 EnterCriticalSection(&m_CriticalSection);
}
 void ReleaseLock() {
    	LeaveCriticalSection( &m_CriticalSection );
}
#else // POSIX
typedef struct{
 int Sh; // Socket Handle which represents a Client
}CLIENT_DATA;
//-------------- Socket Descriptor is integer in POSIX
int ListnerSocket;
int InComingSocket;
//----------------------- House Keeping Routines for GNU Linux
void Cleanup() {} 
bool StartSocket(){return true;}
int SocketGetLastError(){return  0xFFFF;}
#define SOCKET_ERROR (-1) 
//------------------- Close Sockets
int CloseSocket( int s ) {shutdown (s, 2); return 0;}
/* This is the critical section object (statically allocated). */
static pthread_mutex_t cs_mutex =  PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
void InitializeLock() {}
void AcquireLock( ) { pthread_mutex_lock( &cs_mutex );}
void ReleaseLock() {pthread_mutex_unlock( &cs_mutex );}
#define INVALID_SOCKET (-1)
#define DWORD unsigned long
//--------------- Thread Routines
void * ClientThreadProc(void * lpParam);
void * ListenThreadProc(void * lpParameter);

#endif
/////////////////////////////
//
//
//
int ProtocolPort = 3500; 
struct sockaddr_in LocalAddress;
struct sockaddr_in RemoteAddress;
char   Buffer[1024];


///////////////////////////////////////
//
//




int main(int argc, char* argv[])
{


	if ( argc != 2 ){
      		fprintf(stdout,"Usage: Server <portid> \n");  
     		 return 1;
	}
	if ( !StartSocket() )
	{
     		 fprintf(stdout,"Failed To Initialize Socket Library\n");
	  	return 1;
	}

    	ProtocolPort = atoi(argv[1]); 
    	LocalAddress.sin_family = AF_INET;
	LocalAddress.sin_addr.s_addr = INADDR_ANY;
	LocalAddress.sin_port = htons(ProtocolPort);
                  printf("%s\n", "Created Socket ................ ");
	if ( ( ListnerSocket = socket(AF_INET, SOCK_STREAM,0)) ==
		 INVALID_SOCKET ) 
	{
    		fprintf(stdout,"call to socket failed with error %d\n",
			SocketGetLastError());
		Cleanup();
		return -1;
	}
                  printf("%s\n", "About to Bind.. ................ ");
	if (bind(ListnerSocket,(struct sockaddr*)&LocalAddress,
		sizeof(LocalAddress) ) 
		== SOCKET_ERROR) {
		fprintf(stderr,"Socket Error %d\n",SocketGetLastError());
		Cleanup();
		return -1;
	}

                 printf("%s\n", "Listen. ................ ");
	if (listen(ListnerSocket,5) == SOCKET_ERROR) 
	{
	 fprintf(stderr,"Socket Error %d\n",SocketGetLastError());
	 Cleanup();
	 return -1;
	}

	#ifdef WINDOWS_OS
    	DWORD  Thid;
                  printf("%s\n", "Creating a  Windows Thread....... for Listener\n");
	CreateThread(NULL,0,ListenThreadProc,NULL,
		0,&Thid);
                 #else
                    
                     pthread_t thread1;
 	    int  iret1;
                      //-----
                      printf("%s\n", "Creating a  POSIX Thread....... for Listener\n");
                      iret1 = pthread_create( &thread1, NULL, ListenThreadProc, (void*) 0);
  
                 #endif 

	while(1)
		;


	
   	Cleanup();
	return 0;
}


/////////////////////////////////
//
// Initialise Winsock Libraries 
// 
//
//



/////////////////////////////////
//
//
//
//

#ifdef WINDOWS_OS 
DWORD WINAPI ListenThreadProc(
  LPVOID lpParameter   
)

#else
   void * ListenThreadProc(
  void * lpParameter   
)
#endif 

{
 printf("Entered the Listener Thread....\n");

while (1)
{
	unsigned int Len = sizeof( RemoteAddress );
             #ifdef WINDOWS_OS
	InComingSocket = accept(ListnerSocket,
	(struct sockaddr*)&RemoteAddress, (int *)&Len);
            #else
                 InComingSocket = accept(ListnerSocket,
	(struct sockaddr*)&RemoteAddress,(socklen_t *) &Len);

            #endif
                  printf("....................After the Accept........");
	if (InComingSocket == INVALID_SOCKET) 
	{
		fprintf(stderr,"accept error %d\n",SocketGetLastError());
		Cleanup();
		return 0;
	}
                 printf("\n....................Accepted a new Connection........\n");
	CLIENT_DATA ClientData;
               #ifdef WINDOWS_OS
	DWORD ThreadId;
	ClientData.Sh = InComingSocket;
	::CreateThread(NULL,0,ClientThreadProc,(LPVOID)&ClientData,
		0,&ThreadId);
              #else 
                   pthread_t thread2;
                  ClientData.Sh = InComingSocket;
                  pthread_create( &thread2, NULL, ClientThreadProc, (void*) &ClientData);
              #endif
}

 return 0;
}

/////////////////////////////////////
//
//
//
//
//
//
#ifdef WINDOWS_OS
DWORD WINAPI ClientThreadProc(
  LPVOID lpParam   
)
#else
void * ClientThreadProc(
 void * lpParam   
)
#endif

{

 InitializeLock();
 printf("Acquired the Lock....\n");
 CLIENT_DATA CData;
 memcpy(&CData,lpParam,sizeof(CLIENT_DATA));
 char bfr[255];

 while (1)
 {
	 memset(bfr,0,255);
	 int RetVal
		 = recv(CData.Sh ,bfr,sizeof(bfr),0);
                   printf("The Read ...value is %d\n", RetVal);
	 if ( RetVal == 0 || RetVal == -1) 
		 return 0; 

	AcquireLock();
	 printf("==========================\n");
	 printf("%s\n",bfr);
                  printf("\n==========================\n");
	ReleaseLock();

}
  return 0;
}