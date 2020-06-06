#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8888


void send_request(char name[40], int id, int ch, char type[10], int capacity, int startpt, int endpt , int clientSocket)
{
	printf("\nSending Request");
		if(send(clientSocket, name,20,0)<0)
			printf("[-]Error in sending data.\n");
		send(clientSocket, &id, sizeof(int),0);
		send(clientSocket, &ch, sizeof(int),0);
			send(clientSocket, type,10,0);
			send(clientSocket,  &capacity, sizeof(int),0);
		send(clientSocket, &startpt, sizeof(int),0);
		send(clientSocket, &endpt, sizeof(int),0);
		printf("\nRequest Sent");
}
void send_request1(char name[40], int id, int ch, int startpt, int endpt , int clientSocket)
{
	printf("\nSending Request");
		if(send(clientSocket, name,20,0)<0)
			printf("[-]Error in sending data.\n");
		send(clientSocket, &id, sizeof(int),0);
		send(clientSocket, &ch, sizeof(int),0);
		send(clientSocket, &startpt, sizeof(int),0);
		send(clientSocket, &endpt, sizeof(int),0);
		printf("\nRequest Sent");
}

int main(){
	
	int clientSocket, ret;
	struct sockaddr_in serverAddr;
	char buffer[100];
	int ch,id,startpt,endpt;
	int capacity=0;
	char name[20];
	char type[10]="nill"; 
	
	char t_name[20];
	int t_id;
	printf("   Welcome to Carpooling System");
	printf("\n[1]-Driver  [2]-Passenger");
	printf("\nEnter your choice: ");
	scanf("%d",&ch);
	printf("\n Enter your name : ");
	scanf("%s", &name[0]);
	printf("\n Enter ID: ");
    scanf("%d", &id);
	if(ch==1){
		printf("\nEnter Type of vehicle: ");
		scanf("%s",&type[0]);
		printf("\nEnter vehicle capacity: ");
		scanf("%d",&capacity);
	
		printf("\n[1]-Ballupur  [2]-FRI  [3]-IMA  [4]-Prem Nagar  [5]-Nanda Ki Chowki  [6]-Pondha  [7]-Kandoli  [8]-Bhidoli");

		printf("\n Enter Sarting point : ");
		scanf("%d", &startpt);
		printf("\n Enter End point : ");
		scanf("%d", &endpt);
		
		printf("\nRequest is processing");
		
		clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");
		
		send_request(name,id,ch,type,capacity,startpt,endpt, clientSocket);
			
		while(1)
		{
		
			bzero(buffer,100);
			recv(clientSocket, buffer, 100,0);
			printf("\n%s",buffer);
		
			
			 if(strcmp(buffer," There are no passengers yet !!") == 0){
				printf("\n Start your ride without passenger. Will check for passenger on next point");
				while (startpt!=endpt){
				sleep(10);
				startpt= startpt+1;
				send_request(name,id,ch,type,capacity,startpt,endpt,clientSocket);
				bzero(buffer,100);
				recv(clientSocket, buffer, 100,0);
				 if(strcmp(buffer,"Match found !!") == 0)
					 recv(clientSocket, t_name, 20,0);
			recv(clientSocket, &t_id, sizeof(int),0);
			if(ch==1)
				printf("\nDriver's name and id are %s and %d",t_name,t_id);
			else if(ch==2)
				printf("\nPassenger's name and id are %s and %d",t_name,t_id);
			close(clientSocket);
			printf("[-]Disconnected from server.\n");
			exit(1);
				}
				
					printf("\nNot found any passengers in ride. \nRide Complete\n");
					close(clientSocket);
					printf("[-]Disconnected from server.\n");
					exit(1);
			 }
				else if(strcmp(buffer,"Match found !!") == 0){
					recv(clientSocket, t_name, 20,0);
			recv(clientSocket, &t_id, sizeof(int),0);
			if(ch==1)
				printf("\nDriver's name and id are %s and %d",t_name,t_id);
			else if(ch==2)
				printf("\nPassenger's name and id are %s and %d",t_name,t_id);
			close(clientSocket);
			printf("[-]Disconnected from server.\n");
			exit(1);
			
		}
		
			
		}
		
	}
		else if(ch==2)
		{
			printf("\n[1]-Ballupur  [2]-FRI  [3]-IMA  [4]-Prem Nagar  [5]-Nanda Ki Chowki  [6]-Pondha  [7]-Kandoli  [8]-Bhidoli");

		printf("\n Enter Sarting point : ");
		scanf("%d", &startpt);
		printf("\n Enter End point : ");
		scanf("%d", &endpt);
		
		printf("\nRequest is processing");
		
		clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");
		
		send_request1(name,id,ch,startpt,endpt, clientSocket);
			
			bzero(buffer,100);
			recv(clientSocket, buffer, 100,0);
			printf("\n%s",buffer);
			
		if(strcmp(buffer," There are no drivers yet !!") == 0){
					bzero(buffer,100);
					recv(clientSocket, buffer, 100,0);
					
			}
		if(strcmp(buffer,"Match found !!") == 0){
			recv(clientSocket, t_name, 20,0);
			recv(clientSocket, &t_id, sizeof(int),0);
			if(ch==1)
				printf("\nDriver's name and id are %s and %d",t_name,t_id);
			else if(ch==2)
				printf("\nPassenger's name and id are %s and %d",t_name,t_id);
			close(clientSocket);
			printf("[-]Disconnected from server.\n");
			exit(1);
		}
	}
		
	close(clientSocket);
	return 0;
}