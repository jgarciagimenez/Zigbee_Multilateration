/*
 * comm.c
 *
 *  Created on: 11 ene. 2017
 *      Author: xismy
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include "Multilateracion.h"


#define PORT 6590
#define MAX_CONN 2


pthread_t* conns;

struct connection{
	int id;
	int socket;
};

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

#define print(...)\
	printf(__VA_ARGS__);\
	fflush(stdout)

void parseData(int id, const char* line, float** data, int* len){
	int mod;
	char lineCpy[16];
	char* token;
	const char limit[2] = " ";

	strcpy(lineCpy, line);
	token = strtok(lineCpy, limit);


	if(!strcmp(token, "dist")){
		token = strtok(NULL, limit);
		mod = atoi(token);
		if(*len <= mod){
			(*len)++;
			(*data) = realloc(*data, sizeof(float*)*(*len));
		}
		(*data)[mod] = atof(strtok(NULL, limit));
		print("dist: %f\n", (*data)[mod]);
	}
	else if(!strcmp(token, "loc")){
		int i;
		print("Dev: %d\n", id);
		for(i=0;i<(*len);i++){
			print("Mod %d: %f\n", i, (*data)[i]);
		}

		multilat(*data);
	}
}

void* newConnection(void* arg){
	int id = ((struct connection*)arg)->id;
	int socket = ((struct connection*)arg)->socket;
	char buff[16];
	int connected = 1;
	int len = 3;
	float* x = malloc(len*sizeof(float*));

	bzero(buff, 16);
	connected = read(socket, buff, 16);
	while(connected){
		print(buff);
		parseData(id, buff, &x, &len);
		connected = read(socket, buff, 16);
	}
	close(socket);
	*(conns+id) = 0;
	pthread_exit(0);
}

int addConnection(int socket){
	int n;
	struct connection conn;
	for(n=0; n<MAX_CONN && conns[n]!=0; n++)
		;
	conn.id = n;
	conn.socket =  socket;
	if(n!=MAX_CONN){
		pthread_create(conns+n, 0, newConnection, &conn);
	}
	else{
		perror("No se admiten más conexiones.");
		close(socket);
	}
	return 0;
}

int createServer()
{
     int socketServer, socketConn;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;

     socketServer = socket(AF_INET, SOCK_STREAM, 0);
     if (socketServer < 0)
        error("Error al crear socket.");

     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(PORT);

     if (bind(socketServer, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
              error("Error al enlazar el socket.");

     listen(socketServer,5);

     clilen = sizeof(cli_addr);

     conns = malloc(MAX_CONN*sizeof(pthread_t));
     memset(conns, 0, MAX_CONN*sizeof(pthread_t));

     while(1){
		 socketConn = accept(socketServer,(struct sockaddr *) &cli_addr, &clilen);
		 if (socketConn < 0)
			  error("Error al aceptar.");
		 addConnection(socketConn);
     }

     close(socketServer);
     return 0;
}

int main(int argc, char *argv[]){
	float* x = malloc(sizeof(int)*argc/2);
	float* y = malloc(sizeof(int)*argc/2);
	int i;

	for(i=0;i<(argc-1)/2;i++){
		x[i] = atoi(argv[i*2+1]);
		y[i] = atoi(argv[(i+1)*2]);
	}
	multilat_init((argc-1)/2, x, y);

	createServer();
	return 0;
}
