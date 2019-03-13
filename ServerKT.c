#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    //Initialize all variables
    int intiSocket, newSocket, portNum, clientLen, nBytes,check,len;
    char buffer[1024],receivedBuffer[1024];
    char * output;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    char str[1000],text[1000];
    int i=0,j=0;
    char temp;
    intiSocket = socket(PF_INET, SOCK_STREAM, 0);

    if(argc<2){
        printf("\nPlease enter the port number :");
        return 0;
    }
    
    portNum = atoi(argv[1]);
    printf("Port number = %d",portNum);
    serverAddr.sin_family = AF_INET; //Address family
    serverAddr.sin_port = htons(portNum);
    serverAddr.sin_addr.s_addr = inet_addr("130.191.166.3"); //IP Address earlier 127.0.0.1
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    receivedBuffer[0]='\0';
    temp = '\0';
    
    check = bind(intiSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)); // bind: Associating the parent socket with a port
    printf("Bind check %i\n,",check);

    if(listen(intiSocket,5)==0) // if bind successful, returns 0 else -1
        printf("Listening\n");
    else
        printf("Error\n");

    addr_size = sizeof serverStorage;

    while(1){
        if(!fork()){
		newSocket = accept(intiSocket, (struct sockaddr*)&serverStorage, &addr_size); //New Socket created
		nBytes = 1;
		printf("new client \n");
        while(nBytes!=0)
		{
                	buffer[0]='\0';
                	text[0]='\0';
            
	        		strcpy(receivedBuffer, buffer);
            	    nBytes = recv(newSocket,buffer,1024,0); //No.of bytes recieved from the client
			    	printf("nbytes = %i\n",nBytes);
			
                 	for (i=0;i<nBytes-1;i++)
                    {
                        buffer[i] = toupper(buffer[i]); // Added additional function toupper to convert lowercase letters to uppercase
                  	}

                i = 0;
                len=strlen(buffer);
           		j=len-1;
            		for(i=0;i<len;i++) // Reversing the string letter by letter
            		{
                    		str[i]=buffer[j];            
                    		j--;
            		}

			printf("%s\n",buffer);
		    send(newSocket,str,strlen(str),0); //Send the reversed string back to the client
			memset(buffer,0,strlen(buffer));
			memset(str,0,strlen(str));
    	}
        }
        else{
            newSocket = accept(intiSocket, (struct sockaddr*)&serverStorage, &addr_size); //New Socket created
            nBytes = 1;
            printf("new client \n");
            while(nBytes!=0)
            {
                buffer[0]='\0';
                text[0]='\0';
                
                strcpy(receivedBuffer, buffer);
                nBytes = recv(newSocket,buffer,1024,0); //No.of bytes recieved from the client
                printf("nbytes = %i\n",nBytes);
                
                for (i=0;i<nBytes-1;i++)
                {
                    buffer[i] = toupper(buffer[i]); // Added additional function toupper to convert lowercase letters to uppercase
                }
                
                i = 0;
                len=strlen(buffer);
                j=len-1;
                for(i=0;i<len;i++) // Reversing the string letter by letter
                {
                    str[i]=buffer[j];
                    j--;
                }
                
                printf("%s\n",buffer);
                send(newSocket,str,strlen(str),0); //Send the reversed string back to the client
                memset(buffer,0,strlen(buffer));
                memset(str,0,strlen(str));
            }
        }
            close(newSocket);
        }
    
    return 0;
}
