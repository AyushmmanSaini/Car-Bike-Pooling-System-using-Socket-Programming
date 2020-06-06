//Example code: A simple server side code, which echos back the received message. 
//Handle multiple socket connections with select and fd_set on Linux  
#include <stdio.h>  
#include <string.h>   //strlen  
#include <stdlib.h>  
#include <errno.h>  
#include <unistd.h>   //close  
#include <arpa/inet.h>    //close  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros  
     
#define TRUE   1  
#define FALSE  0  
#define PORT 8888  
     
	struct driver
{
    struct driver *prev;
    char d_name[20], type[10];
	int d_id,dstartpt,dendpt,capacity;
	int d_socket;
    struct driver *next;
}*h,*temp,*temp1,*temp2,*temp3,*temp4;
 
 struct passenger
{
    struct passenger *prev;
    char p_name[20];
	int p_id,pstartpt,pendpt;
	int p_socket;
    struct passenger *next;
}*p,*p_temp,*p_temp1,*p_temp2,*p_temp3,*p_temp4;
 
 int d_count = 0;
 int p_count = 0;
 
 /* TO d_create an empty driver */
void d_create(char name[20], char type[10], int id, int startpt, int endpt, int capacity,int s)
{
    temp =(struct driver *)malloc(1*sizeof(struct driver));
    temp->prev = NULL;
    temp->next = NULL;
    strcpy(temp->d_name,name);
	temp->d_id=id;
	strcpy(temp->type,type);
	temp->dstartpt=startpt;
	temp->dendpt=endpt;
	temp->capacity=capacity;
    temp->d_socket=s;
	d_count++;
}

/* TO p_create an empty passenger */
void p_create(char name[20],int id,int startpt, int endpt, int  s)
{
    p_temp =(struct passenger *)malloc(1*sizeof(struct passenger));
    p_temp->prev = NULL;
    p_temp->next = NULL;
    strcpy(p_temp->p_name,name);
	p_temp->p_id=id;
	p_temp->pstartpt=startpt;
	p_temp->pendpt=endpt;
    p_temp->p_socket=s;
	p_count++;
}

/*  TO insert at end (Driver) */
void d_insert(char name[20], char type[10], int id, int startpt, int endpt, int capacity,int s)
{
    if (h == NULL)
    {
        d_create(name,type,id,startpt,endpt,capacity,s);
        h= temp;
        temp1 = h;
    }
    else
    {
        d_create(name,type,id,startpt,endpt,capacity,s);
        temp1->next = temp;
        temp->prev = temp1;
        temp1 = temp;
    }
}
 
 /*  TO insert at end (Passenger)*/
void p_insert(char name[20],int id,int startpt, int endpt, int  s)
{
    if (p == NULL)
    {
        p_create(name,id,startpt,endpt,s);
        p = p_temp;
        p_temp1 = p;
    }
    else
    {
        p_create(name,id,startpt,endpt,s);
        p_temp1->next = p_temp;
        p_temp->prev = p_temp1;
        p_temp1 = p_temp;
    }
}
 
//For printing driver's list
void d_print()
{
    temp2 = h;
 
    if (temp2 == NULL)
    {
        printf("List empty to display \n");
        return;
    }
    printf("\n Linked list elements from begining : ");
 
    while (temp2->next != NULL)
    {
        printf("\nName of driver: %s ", temp2->d_name);
		printf("\nID of driver: %d ", temp2->d_id);
		printf("\nType of vehicle: %s ", temp2->type);
		printf("\nStarting point: %d ", temp2->dstartpt);
		printf("\nEnd point: %d ", temp2->dendpt);
		printf("\nCapacity: %d ", temp2->capacity);
        printf("\n......................");
		temp2 = temp2->next;
    }
    printf("\nName of driver: %s ", temp2->d_name);
		printf("\nID of driver: %d ", temp2->d_id);
		printf("\nType of vehicle: %s ", temp2->type);
		printf("\nStarting point: %d ", temp2->dstartpt);
		printf("\nEnd point: %d ", temp2->dendpt);
        printf("\n......................");
}

// for printing passenger's list
void p_print()
{
    p_temp2 = p;
 
    if (p_temp2 == NULL)
    {
        printf("\nList empty to display \n");
        return;
    }
    printf("\n Linked list elements from begining : ");
 
    while (p_temp2->next != NULL)
    {
        printf("\nName of Passenger: %s ", p_temp2->p_name);
		printf("\nID of Passenger: %d ", p_temp2->p_id);
		printf("\nStarting point: %d ", p_temp2->pstartpt);
		printf("\nEnd point: %d ", p_temp2->pendpt);
        printf("\n......................");
		p_temp2 = p_temp2->next;
    }
    printf("\nName of Passenger: %s ", p_temp2->p_name);
		printf("\nID of Passenger: %d ", p_temp2->p_id);
		printf("\nStarting point: %d ", p_temp2->pstartpt);
		printf("\nEnd point: %d ", p_temp2->pendpt);
        printf("\n......................");
}
void d_delete()
{
	
	 if (temp1 == NULL)
    {
        printf("\nList empty to delete \n");
        
    }
	
	else{
		temp3=temp1;
		temp1=temp1->prev;
		temp1->next=NULL;
		free(temp3);
	}
}

void p_delete()
{
	
	 if (p_temp1 == NULL)
    {
        printf("\nList empty to delete \n");
        
    }
	
	else{
		p_temp3=p_temp1;
		p_temp1=p_temp1->prev;
		p_temp1->next=NULL;
		free(p_temp3);
	}
}

// For matching/ scheduling driver and passenger
int schedule( int dp_arr[],int ch )
{
	printf("Inside schedule func\n");
	temp4=h;
	p_temp4=p;
	printf("drivers list\n");
	d_print();
	printf("passengers list\n");
	p_print();
	if (ch==2){
		if (temp4 == NULL)
		{
			return -2;
		}
	}
	else if(ch==1){
		if (p_temp4 == NULL)
		{
			return -1;
		}
	}
	
		while(1){
			
			if((temp4->dstartpt<=p_temp4->pstartpt) && (temp4->dendpt>=p_temp4->pendpt))
			{
				dp_arr[0]=temp4->d_socket;
				printf("\nDriver socket %d ",dp_arr[0]);
				dp_arr[1]=p_temp4->p_socket;
				printf("\nPassenger socket %d ",dp_arr[1]);
				return 0;
			}
			
			p_temp4 = p_temp4->next;
		
			temp4 = temp4->next;
			if((temp4->next==NULL)||(p_temp4->next==NULL)){
					
				if (ch==2){
					return -2;
				}
				else if(ch==1){
					return  -1;
				}
					
	
	
			}
		}
}
	 
int main()   
{   
printf("*********Server***********\n");
	
	char name[20], type[10];
	int ch,id,startpt,endpt,capacity;
	
	int dp_arr[2];
	int x;
	
    int opt = TRUE;   
    int master_socket , addrlen , new_socket , client_socket[30] , max_clients = 30 , activity, i , valread , sd;   
    int max_sd;   
    struct sockaddr_in address;   
         
    char buffer[100]; 
         
    //set of socket descriptors  
    fd_set readfds;   
         
    //a message  
    char *message = "ECHO Daemon v1.0 \r\n";   
     
    //initialise all client_socket[] to 0 so not checked  
    for (i = 0; i < max_clients; i++)   
    {   
        client_socket[i] = 0;   
    }   
         
    //create a master socket  
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)   
    {   
        perror("socket failed");   
        exit(EXIT_FAILURE);   
    }   
     
    //set master socket to allow multiple connections ,  
    //this is just a good habit, it will work without this  
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,  sizeof(opt)) < 0 )   
    {   
        perror("setsockopt");   
        exit(EXIT_FAILURE);   
    }   
     
    //type of socket created  
    address.sin_family = AF_INET;   
    address.sin_addr.s_addr = INADDR_ANY;   
    address.sin_port = htons( PORT );   
         
    //bind the socket to localhost port 8888  
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)   
    {   
        perror("bind failed");   
        exit(EXIT_FAILURE);   
    }   
    printf("Listener on port %d \n", PORT);   
         
    //try to specify maximum of 3 pending connections for the master socket  
    if (listen(master_socket, 3) < 0)   
    {   
        perror("listen");   
        exit(EXIT_FAILURE);   
    }   
         
    //accept the incoming connection  
    addrlen = sizeof(address);   
    puts("Waiting for connections ...");   
         
    while(TRUE)   
    {   
        //clear the socket set  
        FD_ZERO(&readfds);   
     
        //add master socket to set  
        FD_SET(master_socket, &readfds);   
        max_sd = master_socket;   
             
        //add child sockets to set  
        for ( i = 0 ; i < max_clients ; i++)   
        {   
            //socket descriptor  
            sd = client_socket[i];   
                 
            //if valid socket descriptor then add to read list  
            if(sd > 0)   
                FD_SET( sd , &readfds);   
                 
            //highest file descriptor number, need it for the select function  
            if(sd > max_sd)   
                max_sd = sd;   
        }   
     
        //wait for an activity on one of the sockets , timeout is NULL ,  
        //so wait indefinitely  
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);   
       
        if ((activity < 0) && (errno!=EINTR))   
        {   
            printf("select error");   
        }   
             
        //If something happened on the master socket ,  
        //then its an incoming connection  
        if (FD_ISSET(master_socket, &readfds))   
        {   
            if ((new_socket = accept(master_socket,  
                    (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)   
            {   
                perror("accept");   
                exit(EXIT_FAILURE);   
            }   
             
            //inform user of socket number - used in send and receive commands  
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(address.sin_addr) , ntohs (address.sin_port));   
           
		
				printf("\nReceiving Request");
				if(recv(new_socket, name, 20,0)<0)
					printf("[-]Error in receiving data.\n");
				//printf("\n%s",name);
				recv(new_socket, &id, sizeof(int),0);
				recv(new_socket, &ch, sizeof(int),0);
				if(ch==1){
					//printf("\n Driver");
					recv(new_socket, type, 10,0);
					recv(new_socket, &capacity, sizeof(int),0);
					}
					//printf("\n Driver1");
				recv(new_socket, &startpt, sizeof(int),0);
				recv(new_socket, &endpt, sizeof(int),0);
				if(ch==1){
					d_insert(name,type,id,startpt,endpt,capacity,new_socket);
					d_print();
				}
				else if(ch==2){
					p_insert(name,id,startpt,endpt,new_socket);
					p_print();
				}
				printf("\nConnection Accepted from Client %d",id);
		   
				x=schedule(dp_arr,ch);
				if (x==-1){
					bzero(buffer,100);
					strcpy(buffer," There are no passengers yet !!");
					send(new_socket, buffer, 100,0);
					d_delete();
				}
				else if(x==-2){
					bzero(buffer,100);
					strcpy(buffer," There are no drivers yet !!");
					send(new_socket, buffer, 100,0);
					p_delete();
				}
				else if(x==0){
					bzero(buffer,100);
					strcpy(buffer,"Match found !!");
					send(dp_arr[0], buffer, 100,0);
					bzero(buffer,100);
					strcpy(buffer,"Match found !!");
					send(dp_arr[1], buffer, 100,0);
					temp2=h;
					p_temp2=p;
					while (temp2->next != NULL){
						if(dp_arr[0]==temp2->d_socket){
							send(dp_arr[0], temp2->d_name, 20,0);
							send(dp_arr[0], &temp2->d_id,sizeof(int),0);
						}
						temp2 = temp2->next;
					}
					while(p_temp2->next!=NULL){
						if(dp_arr[1]==p_temp2->p_socket)
								{
									send(dp_arr[1], p_temp2->p_name, 20,0);
									send(dp_arr[1], &p_temp2->p_id,sizeof(int),0);
								}
							p_temp2 = p_temp2->next;
						}
					d_delete();
					p_delete();
					
				}
		
				//add new socket to array of sockets  
				for (i = 0; i < max_clients; i++)   
				{   
					//if position is empty  
					if( client_socket[i] == 0 )   
					{   
						client_socket[i] = new_socket;   
						printf("Adding to list of sockets as %d\n" , i);   
							 
						break;   
					}   
				}




		}
			close(new_socket);
           
             
        //else its some IO operation on some other socket 
        for (i = 0; i < max_clients; i++)   
        {   
            sd = client_socket[i];   
                 
            if (FD_ISSET( sd , &readfds))   
            {   
                //Check if it was for closing , and also read the  
                //incoming message  
                if ((valread = read( sd , buffer, 100)) == 0)   
                {   
                    //Somebody disconnected , get his details and print  
                    getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);   
                    printf("Host disconnected , ip %s , port %d \n" ,  inet_ntoa(address.sin_addr) , ntohs(address.sin_port));   
                         
                    //Close the socket and mark as 0 in list for reuse  
                    close( sd );   
                    client_socket[i] = 0;   
                }   
                     
                //Echo back the message that came in  
                /*else 
                {   
                    //set the string terminating NULL byte on the end  
                    //of the data read  
                    buffer[valread] = '\0';   
                    send(sd , buffer , strlen(buffer) , 0 );   
                }   */
            }   
        }   
	}
         
    return 0;   
}