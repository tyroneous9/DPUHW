/*-------------------------------------------------------------------------*
 *---									---*
 *---		wordServer.c						---*
 *---									---*
 *---	    This file defines a C program that gets file-sys commands	---*
 *---	from client via a socket, executes those commands in their own	---*
 *---	threads, and returns the corresponding output back to the	---*
 *---	client.								---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a					Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

//	Compile with:
//	$ gcc wordServer.c -o wordServer -lpthread

//---		Header file inclusion					---//

#include	"wordClientServer.h"
#include	<pthread.h>	// For pthread_create()


//---		Definition of constants:				---//

#define		STD_OKAY_MSG		"Okay"

#define		STD_ERROR_MSG		"Error doing operation"

#define		STD_BYE_MSG		"Good bye!"

#define		THIS_PROGRAM_NAME	"wordServer"

#define		OUTPUT_FILENAME		"out.txt"

#define		ERROR_FILENAME		"err.txt"

const int	ERROR_FD		= -1;

//---   Declaration of functions:       ---//
void*   handleClient                  (void* dataPtr);
int     listFiles                     (char* buffer);
int     writeToFile                   (char* buffer,
                                      char* fileName);
int     spellCheckFile                (char* buffer,
                                      char* fileName);
int     deleteFile                    (char* fileName);
void    doServer	                    (int listenFd);
int	    getPortNum	                  (int	argc,
				                              char*	argv[]);
int		  getServerFileDescriptor       (int port);


//---		Definition of functions:				---//
void* handleClient(void* dataPtr) 
{ 
  int* data = (int*)dataPtr;
  int socketfd = data[0];
  int threadCount = data[1];
  free(data);

  printf("THREAD %d\n________", threadCount);
  char	buffer[BUFFER_LEN];
  char	command;
  int	  fileNum;
  char	text[BUFFER_LEN];
  int 	shouldContinue	= 1;
  int   exitStatus;
  while  (shouldContinue)
  {
    text[0]	= '\0';
    read(socketfd,buffer,BUFFER_LEN);
    printf("Thread %d received: %s\n",threadCount,buffer);
    sscanf(buffer,"%c %d \"%[^\"]\"",&command,&fileNum,text);
    // // YOUR CODE HERE
    char fileName[BUFFER_LEN];
    snprintf(fileName, BUFFER_LEN, "%d%s", fileNum, FILENAME_EXTENSION);
    switch(command) {
      case DIR_CMD_CHAR:
        exitStatus = listFiles(buffer);
        break;

      case WRITE_CMD_CHAR:
        exitStatus = writeToFile(buffer, fileName);   
        break;    

      case SPELL_CMD_CHAR:
        exitStatus = spellCheckFile(buffer, fileName);
        break;

      case DELETE_CMD_CHAR:
        exitStatus = deleteFile(fileName);
        break;
        
      case QUIT_CMD_CHAR:
        fprintf(stdout, "%s\n", STD_BYE_MSG);
        shouldContinue = 0;
        break;
    }
    (exitStatus == 0) ? snprintf(buffer, BUFFER_LEN, "%s\n", STD_OKAY_MSG) : snprintf(buffer, BUFFER_LEN, "%s\n", STD_ERROR_MSG);
    write(socketfd, buffer, BUFFER_LEN);
  }
  printf("Thread %d quitting.\n",threadCount);
  return(NULL);
}

int listFiles(char* buffer) 
{
  DIR* dirPtr = opendir(".");
  struct dirent* entry;
  memset(buffer, '\0', BUFFER_LEN);
  if(dirPtr == NULL)
    return -1;
  for(int i=0; entry != NULL; entry = readdir(dirPtr)) {
    i += snprintf(buffer+i, BUFFER_LEN, "%s\n", entry->d_name);
  }
  closedir(dirPtr);
  printf("%s", buffer);
  return 0;
}

int writeToFile(char* buffer,
                char* fileName) 
{
  int fd = open(fileName, O_CREAT, O_WRONLY, 0777);
  if(fd == -1 || write(fd, buffer, BUFFER_LEN) == -1) {
    perror("Error");
    return -1;
  }
    
  close(fd);
  return 0;
}

int spellCheckFile(char* buffer,
                    char* fileName)
{
  int fd = open(fileName, O_RDWR, 0666);
  if(fd == -1)
    return -1;

  long length;
  int	status;
  int spellerToFile[2];

  pipe(spellerToFile);
  pid_t childId;
  if((childId = fork()) == 0) {
    length  = lseek(fd,0,SEEK_SET);
    status	= write(fd,ENDING_TEXT,sizeof(ENDING_TEXT)-1);
    dup2(fd,STDIN_FILENO);
    dup2(spellerToFile[1],STDOUT_FILENO);
    if(execl(SPELLER_PROGNAME, SPELLER_PROGNAME, SPELLER_PROG_OPTION, '\0') == -1) {
      snprintf(buffer, BUFFER_LEN, "%s, ENDING TEXT: %s", STD_ERROR_MSG, ENDING_TEXT);
      write(spellerToFile[1], buffer, BUFFER_LEN);
      exit(EXIT_FAILURE);
    }
  }
  else {
    for(int i=0; strstr(buffer+i, ENDING_TEXT)!=NULL;) {
      i += read(spellerToFile[0], buffer+i, BUFFER_LEN);
    }
    waitpid(childId, NULL, 0);
    ftruncate(fd,length);
    close(fd);
    close(spellerToFile[0]);
    close(spellerToFile[1]);
  }
  return 0;
}

int deleteFile(char* fileName)
{
  if(unlink(fileName) == -1)
    return -1;
  return 0;
}

//  PURPOSE:  To run the server by 'accept()'-ing client requests from
//	'listenFd' and doing them.
//  PURPOSE:  To run the server by 'accept()'-ing client requests from
//	'listenFd' and doing them.
void		doServer	(int		listenFd)
{
  //  I.  Application validity check:

  //  II.  Server clients:
  pthread_t		threadId;
  pthread_attr_t	threadAttr;
  int			threadCount	= 0;
  // YOUR CODE HERE
  pthread_attr_init(&threadAttr);
  pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED);
  while(1)  {
    int* sendMe       = calloc(2,sizeof(int));
    sendMe[0]         = accept(listenFd, NULL, NULL);
    sendMe[1]         = threadCount++;
    pthread_create(&threadId, &threadAttr, handleClient, (void*)sendMe);
  }
    //  III.  Finished:
  pthread_attr_destroy(&threadAttr);
}



//  PURPOSE:  To decide a port number, either from the command line arguments
//	'argc' and 'argv[]', or by asking the user.  Returns port number.
int		getPortNum	(int	argc,
				 char*	argv[]
				)
{
  //  I.  Application validity check:

  //  II.  Get listening socket:
  int	portNum;
  if  (argc >= 2)
    portNum	= strtol(argv[1],NULL,0);
  else
  {
    char	buffer[BUFFER_LEN];

    printf("Port number to monopolize? ");
    fgets(buffer,BUFFER_LEN,stdin);
    portNum	= strtol(buffer,NULL,0);
  }

  //  III.  Finished:  
  return(portNum);
}


//  PURPOSE:  To attempt to create and return a file-descriptor for listening
//	to the OS telling this server when a client process has connect()-ed
//	to 'port'.  Returns that file-descriptor, or 'ERROR_FD' on failure.
int		getServerFileDescriptor
				(int		port
				)
{
  //  I.  Application validity check:

  //  II.  Attempt to get socket file descriptor and bind it to 'port':
  //  II.A.  Create a socket
  int socketDescriptor = socket(AF_INET, // AF_INET domain
			        SOCK_STREAM, // Reliable TCP
			        0);
  int iSetOption = 1;
  setsockopt(socketDescriptor, SOL_SOCKET, SO_REUSEADDR, (char*)&iSetOption, sizeof(iSetOption));

  if  (socketDescriptor < 0)
  {
    perror(THIS_PROGRAM_NAME);
    return(ERROR_FD);
  }

  //  II.B.  Attempt to bind 'socketDescriptor' to 'port':
  //  II.B.1.  We'll fill in this datastruct
  struct sockaddr_in socketInfo;

  //  II.B.2.  Fill socketInfo with 0's
  memset(&socketInfo,'\0',sizeof(socketInfo));

  //  II.B.3.  Use TCP/IP:
  socketInfo.sin_family = AF_INET;

  //  II.B.4.  Tell port in network endian with htons()
  socketInfo.sin_port = htons(port);

  //  II.B.5.  Allow machine to connect to this service
  socketInfo.sin_addr.s_addr = INADDR_ANY;

  //  II.B.6.  Try to bind socket with port and other specifications
  int status = bind(socketDescriptor, // from socket()
		    (struct sockaddr*)&socketInfo,
		    sizeof(socketInfo)
		   );

  if  (status < 0)
  {
    perror(THIS_PROGRAM_NAME);
    return(ERROR_FD);
  }

  //  II.B.6.  Set OS queue length:
  listen(socketDescriptor,5);

  //  III.  Finished:
  return(socketDescriptor);
}


int		main		(int	argc,
				 char*	argv[]
				)
{
  //  I.  Application validity check:

  //  II.  Do server:
  int 	    port	= getPortNum(argc,argv);
  int	      listenFd	= getServerFileDescriptor(port);
  int	      status	= EXIT_FAILURE;

  if  (listenFd >= 0)
  {
    doServer(listenFd);
    close(listenFd);
    status	= EXIT_SUCCESS;
  }

  //  III.  Finished:
  return(status);
}