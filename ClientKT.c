#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char *argv[]){
    int clientSocket, portNum, nBytes;
    char receivedBuffer[1024],fileBuffer[1024], reversedOutput[1024];
    char buffer[1024],outputBuffer[1024],temp,hostName[20];
    struct sockaddr_in serverAddr;
    struct hostent *server;
    socklen_t addr_size;
    FILE *fp,*fp2;
    int i=0;int j=0, check;

    if(argc < 3){
        printf("\nEnter port number and server address");
        return 0;
    }
    
    portNum = atoi(argv[1]);
    
    //printf("Server address %s",argv[2]);
    fp = fopen("userinput.txt", "w+");
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(portNum);
    serverAddr.sin_addr.s_addr = inet_addr("130.191.166.3"); //change with argv[2]
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    addr_size = sizeof serverAddr;
    check = connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
printf("%i\n",check);

    while(1){
        buffer[0]='\0';
        fileBuffer[0]='\0';
        receivedBuffer[0]='\0';
        temp = '\0';
        printf("Type a sentence to send to server:\n");
        scanf(" %[^\t\n]s",buffer);
        printf("You typed: %s\n",buffer);
        fp = fopen("userinput.txt", "w+");
        if(fp != NULL) //if file does not exist, create it
        {
		//printf("%s\n",buffer);
            fwrite(&buffer, sizeof(char), sizeof(buffer), fp);
            fseek(fp, 0, SEEK_SET);
            fread(&fileBuffer, strlen(buffer)+1, 1024, fp);
		//printf("%s\n",fileBuffer);

            temp = '\0';
            nBytes = strlen(fileBuffer)+1;
            printf("nBytes:%d\n",nBytes);
            send(clientSocket,fileBuffer,nBytes,0);
 		printf("after send\n");
	    memset(fileBuffer,0,strlen(fileBuffer));

            recv(clientSocket,receivedBuffer , 1024, 0);
 		printf("after receive\n");
		
            printf("Received from server: %s\n", receivedBuffer);
	    memset(receivedBuffer,0,strlen(receivedBuffer));

            fclose(fp);
            //fclose(fp2);
        }

    }

    return 0;
}
