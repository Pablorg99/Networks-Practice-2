#include <stdio.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>


int main ( )
{
  
	/*---------------------------------------------------- 
		Descriptor del socket y buffer de datos                
	-----------------------------------------------------*/
	int clientSocketDescriptor;
	struct sockaddr_in clientSocketData;
	char buffer[250];
	socklen_t len_clientSocketData;
    fd_set readfds, auxfds;
    int salida;
    int fin = 0;
	
    
	/* --------------------------------------------------
		Se abre el socket 
	---------------------------------------------------*/
  	clientSocketDescriptor = socket (AF_INET, SOCK_STREAM, 0);
	if (clientSocketDescriptor == -1)
	{
		perror("No se puede abrir el socket cliente\n");
    		exit (1);	
	}

   
    
	/* ------------------------------------------------------------------
		Se rellenan los campos de la estructura con la IP del 
		servidor y el puerto del servicio que solicitamos
	-------------------------------------------------------------------*/
	clientSocketData.sin_family = AF_INET;
	clientSocketData.sin_port = htons(2000);
	clientSocketData.sin_addr.s_addr =  inet_addr("172.16.218.20");

	/* ------------------------------------------------------------------
		Se solicita la conexión con el servidor
	-------------------------------------------------------------------*/
	len_clientSocketData = sizeof(clientSocketData);
	
	if (connect(clientSocketDescriptor, (struct sockaddr *)&clientSocketData, len_clientSocketData) == -1)
	{
		perror ("Error de conexión");
		exit(1);
	}
    
    //Inicializamos las estructuras
    FD_ZERO(&auxfds);
    FD_ZERO(&readfds);
    
    FD_SET(0,&readfds);
    FD_SET(clientSocketDescriptor,&readfds);

    
	/* ------------------------------------------------------------------
		Se transmite la información
	-------------------------------------------------------------------*/
	do
	{
        auxfds = readfds;
        salida = select(clientSocketDescriptor+1,&auxfds,NULL,NULL,NULL);
        
        //Tengo mensaje del servidor
        if(FD_ISSET(clientSocketDescriptor, &auxfds)){
            
            clearBuffer(buffer,sizeof(buffer));
            recv(clientSocketDescriptor,buffer,sizeof(buffer),0);
            
            printf("\n%s\n",buffer);
            
            if(strcmp(buffer,"Demasiados clientes conectados\n") == 0)
                fin =1;
            
            if(strcmp(buffer,"Desconexion servidor\n") == 0)
                fin =1;
            
        }
        else
        {
            
            //He introducido información por teclado
            if(FD_ISSET(0,&auxfds)){
                clearBuffer(buffer,sizeof(buffer));
                
                fgets(buffer,sizeof(buffer),stdin);
                
                if(strcmp(buffer,"SALIR\n") == 0){
                        fin = 1;
                
                }
                
                send(clientSocketDescriptor,buffer,sizeof(buffer),0);
                
            }
            
            
        }
        
        
				
    }while(fin == 0);
		
    close(clientSocketDescriptor);

    return 0;
		
}





















