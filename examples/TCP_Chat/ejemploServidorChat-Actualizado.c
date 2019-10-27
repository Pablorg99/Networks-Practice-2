#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>


#define MSG_SIZE 250
#define MAX_CLIENTS 50


/*
 * El servidor ofrece el servicio de un chat
 */

void manejador(int signum);
void salirCliente(int socket, fd_set * readfds, int * numClientes, int arrayClientes[]);



int main ( )
{
  
	/*---------------------------------------------------- 
		Descriptor del socket y buffer de datos                
	-----------------------------------------------------*/
	int serverSocketDescriptor, connectionSocketDescriptor;
	struct sockaddr_in sockname, from;
	char buffer[MSG_SIZE];
	socklen_t from_len;
    fd_set readfds, auxfds;
    int salida;
    int arrayClientes[MAX_CLIENTS];
    int numClientes = 0;
    //contadores
    int socketID, clientID,k;
	int recibidos;
    char identificador[MSG_SIZE];
    
    int on, ret;

    
    
	/* --------------------------------------------------
		Se abre el socket 
	---------------------------------------------------*/
  	serverSocketDescriptor = socket (AF_INET, SOCK_STREAM, 0);
	if (serverSocketDescriptor == -1)
	{
		perror("No se puede abrir el socket del servidor\n");
    		exit (1);	
	}
    
    // Activaremos una propiedad del socket que permitir· que otros
    // sockets puedan reutilizar cualquier puerto al que nos enlacemos.
    // Esto permitir· en protocolos como el TCP, poder ejecutar un
    // mismo programa varias veces seguidas y enlazarlo siempre al
    // mismo puerto. De lo contrario habrÌa que esperar a que el puerto
    // quedase disponible (TIME_WAIT en el caso de TCP)
    on=1;
    ret = setsockopt( serverSocketDescriptor, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));



	sockname.sin_family = AF_INET;
	sockname.sin_port = htons(2000);
	sockname.sin_addr.s_addr =  INADDR_ANY;

	if (bind (serverSocketDescriptor, (struct sockaddr *) &sockname, sizeof (sockname)) == -1)
	{
		perror("Error en la operación bind");
		exit(1);
	}
	

   	/*---------------------------------------------------------------------
		Del las peticiones que vamos a aceptar sólo necesitamos el 
		tamaño de su estructura, el resto de información (familia, puerto, 
		ip), nos la proporcionará el método que recibe las peticiones.
   	----------------------------------------------------------------------*/
		from_len = sizeof (from);


		if(listen(serverSocketDescriptor,1) == -1){
			perror("Error en la operación de listen");
			exit(1);
		}
    
    //Inicializar los conjuntos fd_set
    FD_ZERO(&readfds);
    FD_ZERO(&auxfds);
    FD_SET(serverSocketDescriptor,&readfds);
    FD_SET(0,&readfds);
    
   	
    //Capturamos la señal SIGINT (Ctrl+c)
    signal(SIGINT,manejador);
    
	/*-----------------------------------------------------------------------
		El servidor acepta una petición
	------------------------------------------------------------------------ */
		while(1){
            
            //Esperamos recibir mensajes de los clientes (nuevas conexiones o mensajes de los clientes ya conectados)
            
            auxfds = readfds;
            
            salida = select(FD_SETSIZE,&auxfds,NULL,NULL,NULL);
            
            if(salida > 0){
                
                
                for(socketID=0; socketID<FD_SETSIZE; socketID++){
                    
                    //Buscamos el socket por el que se ha establecido la comunicación
                    if(FD_ISSET(socketID, &auxfds)) {
                        
                        if( socketID == serverSocketDescriptor){
                            
                            if((connectionSocketDescriptor = accept(serverSocketDescriptor, (struct sockaddr *)&from, &from_len)) == -1){
                                perror("Error aceptando peticiones");
                            }
                            else
                            {
                                if(numClientes < MAX_CLIENTS){
                                    arrayClientes[numClientes] = connectionSocketDescriptor;
                                    numClientes++;
                                    FD_SET(connectionSocketDescriptor,&readfds);
                                
                                    strcpy(buffer, "Bienvenido al chat\n");
                                
                                    send(connectionSocketDescriptor,buffer,strlen(buffer),0);
                                
                                    for(clientID=0; clientID<(numClientes-1);clientID++){
                                    
                                        clearBuffer(buffer,sizeof(buffer));
                                        sprintf(buffer, "Nuevo Cliente conectado: %d\n",connectionSocketDescriptor);
                                        send(arrayClientes[clientID],buffer,strlen(buffer),0);
                                    }
                                }
                                else
                                {
                                    clearBuffer(buffer,sizeof(buffer));
                                    strcpy(buffer,"Demasiados clientes conectados\n");
                                    sprintf(connectionSocketDescriptor,buffer,strlen(buffer),0);
                                    close(connectionSocketDescriptor);
                                }
                                
                            }
                            
                            
                        }
                        else if (socketID == 0){
                            //Se ha introducido información de teclado
                            clearBuffer(buffer, sizeof(buffer));
                            fgets(buffer, sizeof(buffer),stdin);
                            
                            //Controlar si se ha introducido "SALIR", cerrando todos los sockets y finalmente saliendo del servidor. (implementar)
                            if(strcmp(buffer,"SALIR\n") == 0){
                             
                                for (clientID = 0; clientID < numClientes; clientID++){
                                    send(arrayClientes[clientID], "Desconexion servidor\n", strlen("Desconexion servidor\n"),0);
                                    close(arrayClientes[clientID]);
                                    FD_CLR(arrayClientes[clientID],&readfds);
                                }
                                    close(serverSocketDescriptor);
                                    exit(-1);
                                
                                
                            }
                            //Mensajes que se quieran mandar a los clientes (implementar)
                            
                        } 
                        else{
                            clearBuffer(buffer,sizeof(buffer));
                            
                            recibidos = recv(socketID,buffer,sizeof(buffer),0);
                            
                            if(recibidos > 0){
                                
                                if(strcmp(buffer,"SALIR\n") == 0){
                                    
                                    salirCliente(socketID,&readfds,&numClientes,arrayClientes);
                                    
                                }
                                else{
                                    
                                    sprintf(identificador,"%d: %s",socketID,buffer);
                                    clearBuffer(buffer,sizeof(buffer));
                                    strcpy(buffer,identificador);
                                    
                                    for(clientID=0; clientID<numClientes; clientID++)
                                        if(arrayClientes[clientID] != socketID)
                                            send(arrayClientes[clientID],buffer,strlen(buffer),0);

                                    
                                }
                                                                
                                
                            }
                            //Si el cliente introdujo ctrl+c
                            if(recibidos== 0)
                            {
                                printf("El socket %d, ha introducido ctrl+c\n", socketID);
                                //Eliminar ese socket
                                salirCliente(socketID,&readfds,&numClientes,arrayClientes);
                            }
                        }
                    }
                }
            }
		}

	close(serverSocketDescriptor);
	return 0;
	
}

void salirCliente(int socket, fd_set * readfds, int * numClientes, int arrayClientes[]){
  
    char buffer[250];
    int client;
    
    close(socket);
    FD_CLR(socket,readfds);
    
    //Re-estructurar el array de clientes
    for (client = 0; client < (*numClientes) - 1; client++)
        if (arrayClientes[client] == socket)
            break;
    for (; client < (*numClientes) - 1; client++)
        (arrayClientes[client] = arrayClientes[client+1]);
    
    (*numClientes)--;
    
    clearBuffer(buffer,sizeof(buffer));
    sprintf(buffer,"Desconexión del cliente: %d\n",socket)  ;
    
    for(client=0; client<(*numClientes); client++)
        if(arrayClientes[client] != socket)
            send(arrayClientes[client],buffer,strlen(buffer),0);


}


void manejador (int signum){
    printf("\nSe ha recibido la señal sigint\n");
    signal(SIGINT,manejador);
    
    //Implementar lo que se desee realizar cuando ocurra la excepción de ctrl+c en el servidor
}
