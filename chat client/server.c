/* 
 * NOTE: client and server chat program, this is the SERVER side.
 *        (You must set up the server side first)
 *       TO RUN FROM TERMINAL USE THESE COMMANDS:
 *
 *           gcc server.c -o server
 *           ./server
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>

#define SIZE 100

int main (){

    //get port number from user
    int PORT;
    printf("Please enter PORT number: ");
      char buf[SIZE];
    if (fgets(buf, sizeof(buf), stdin) != NULL){
        PORT = atoi(buf);
      }

      //fpurge(stdin); //this only works on Mac when using scanf
                        //clears the stdin budder
                        //if not done, then the next input will
                         //be skipped
                        //old unix uses fflush

     char flag[]="yes";
     char argv[]="no"; //change tp yes if you want to debug

	int 	 sd, sd_current, cc, fromlen, tolen;
	int 	 addrlen;
	struct   sockaddr_in sin;
	struct   sockaddr_in pin;
    char  buffer[BUFSIZ];

	/* get an internet domain socket */
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	/* complete the socket structure */
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(PORT);

	/* bind the socket to the port number */
	if (bind(sd, (struct sockaddr *) &sin, sizeof(sin)) == -1) {
		perror("bind");
		exit(1);
	}

	printf("Listening for client\n");

	/* show that we are willing to listen */
    //printf("testing listen: %d \n", listen(sd, 1));

	if (listen(sd, 1) == -1) {
		perror("listen");
		exit(1);
	}
    //printf("After listen.\n");
    if(!strcmp(flag,argv))
    {printf("After listen.\n");}


	/* wait for a client to talk to us */
	if ((sd_current = accept(sd, (struct sockaddr *)  &pin, &addrlen)) == -1) {
		perror("accept");
		exit(1);
	}
    if(!strcmp(flag,argv))
    {printf("After accept.\n");}


	/* get a message from the client */

/////////////////////////////////////////////////////
/************_____CHAT_____**********************/
//////////////////////////////////////////////////////

 char message[SIZE];
 char done[]="BYE\n";
    while(1){

            //////RECEIVE MESSAGE
            if (recv(sd_current, message, SIZE , 0) == -1) {
               perror("recv");
               exit(1);
            }

            /////print message from client
            printf("CLIENT SAYS: %s \n" ,message);

            /////If message == "BYE" close connection
            if(!strcmp(done,message)){
                printf("Connection terminated\n");
                close(sd_current);
                close(sd);
                break;
            }


            bzero(message, SIZE);

            if(!strcmp(flag,argv)){
                printf  ("Sending Total: %s\n", message);
            }

                    /*Sending Total*/
            printf("SEND::> ");
            fgets(message, SIZE, stdin);

            ////////SEND MESSAGE
            if(send(sd_current, message, SIZE, 0) == -1) {
                perror("send");
                exit(1);
            }

            if(!strcmp(flag,argv)){
                printf("SEND: %s \n", message);
            }

            bzero(message, SIZE);
    }

        /* give client a chance to properly shutdown */
        sleep(1);
}

