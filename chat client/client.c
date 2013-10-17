/* 
 * NOTE: client and server chat program, this is the CLIENT side.
 *        (You must set up the server side first)
 *
 *       TO RUN FROM TERMINAL USE THESE COMMANDS:
 *
 *           gcc client.c -o client
 *           ./client
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>

#define SIZE 100

int main (){

    //get host name
    char HOST[SIZE];
    //if want to avoid using the required host,
    //you can use the "localhost" but please change the required
    // string to "localhost" in the while loop
    while(strcmp("bayou.cs.uh.edu",HOST)){
    printf("Please enter HOST name: ");
    fgets(HOST, SIZE, stdin);
    strtok(HOST, "\n"); //gets rid of the '\n'
    //printf("HOST:|||%s||||||",HOST);
    }

    //get port number from user
    int PORT;
    printf("Please enter PORT number: ");
    //scanf("%d", &PORT);  //use with fpurge line: 52

    char buf[SIZE];
    if (fgets(buf, sizeof(buf), stdin) != NULL){
        PORT = atoi(buf);
    }

   // printf("PORT: %i \n",PORT); //portno

    //fpurge(stdin); //this only works on Mac when using scanf
                     //clears the stdin budder
                     //if not done, then the next input will
                     //be skipped
                      //old unix uses fflush

    char flag[] = "yes";
    char argv[] = "no"; //change to yes if you want to debug

	  int	sd, sd_current;
    int    addrlen;
	  struct sockaddr_in sin;
	  struct sockaddr_in pin;
    struct hostent *hp;
    struct hostent *server;

	/* go find out about the desired host machine */
	  if ((hp = gethostbyname(HOST)) == 0) {
	   perror("gethostbyname");
     exit(1);
	  }

    if(!strcmp(flag,argv)){
    printf("After gethostbyname.\n");
    }

	/* fill in the socket structure with host information */
  	memset(&pin, 0, sizeof(pin));
	  pin.sin_family = AF_INET;
  	pin.sin_addr.s_addr = ((struct in_addr *)(hp->h_addr))->s_addr;
	  pin.sin_port = htons(PORT);

    if(!strcmp(flag,argv)){
      printf("After fill in the socket struct.\n");
    }

	/* grab an Internet domain socket */
  	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
	  	perror("socket");
		  exit(1);
	  }

   if(!strcmp(flag,argv)){
    printf("After socket.\n");
    }

	/* connect to PORT on HOST */
	 if (connect(sd,(struct sockaddr *)  &pin, sizeof(pin)) == -1) {
		perror("connect ");
		exit(1);
	 }

    if(!strcmp(flag,argv)){
      printf("After connect.\n");
    }


/////////////////////////////////////////////////////
/************_____CHAT_____**********************/
//////////////////////////////////////////////////////

char message[SIZE];
char done[]="BYE\n";
     while(1){
            printf("SEND::> ");
            fgets(message, SIZE, stdin);

            ////////SEND MESSAGE
            if(send(sd, message, SIZE, 0) == -1) {
    					perror("send");
    					exit(1);
            }

            if(!strcmp(flag,argv)){
              printf("SEND: %s \n", message);
            }
              /////If message == "BYE" close connection
            if(!strcmp(message,done)){
              printf("Connection terminated\n");
              close(sd);
              if(!strcmp(flag,argv)){
                  printf("After close.\n");
                }
                break;
            }

             //////RECEIVE MESSAGE
            bzero(message,SIZE);
            if (recv(sd, message, SIZE , 0) == -1) {
                    perror("recv");
                    exit(1);
            }
              /////print message from server
             printf("SERVER SAYS: %s \n", message);

             bzero(message,SIZE);
    }

    /* give client a chance to properly shutdown */
    sleep(1);
 }


