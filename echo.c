/******************************************************************************
Copyright (c) 2014 Murray Grace

Echo-Server is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

Echo-Server is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>  /* define socket */
#include <netinet/in.h>  /* define internet socket */
#include <netdb.h>       /* define internet socket */

#define SERVER_PORT 7777        /* define a server port number */

struct in_addr addr;
int sock;

int main()
{
  int client, receive;
	struct sockaddr_in server_addr = { AF_INET, htons( SERVER_PORT ) };
  struct sockaddr_in client_addr = { AF_INET };
  int client_len = sizeof( client_addr );
  char buf[512], *host;
  int i = 1;
	addr = server_addr.sin_addr;
  // Create Socket
  if( ( sock = socket( AF_INET, SOCK_STREAM, 0 ) ) == -1 )
    {
      perror( "Socket Failure" );
      exit( 1 );
    }
	 
  // Bind Socket
  if( bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1 )
    {
      perror( "Port Bind Failure" );
      exit( 1 );
    }
    
		
  // Listen for Clients
  if (listen(sock,1)==-1)
    {
      perror("Listen Failure");
      exit(1);
    }
		
  while(1)
	{
		printf("Listening...\n");
		if((client = accept(sock, (struct sockaddr*)&client_addr, &client_len))== - 1)
		{
			perror("Accept Failure");
			exit(1);
		}
		
		printf("Accept successful, client connected\n");
		
		while((receive = read(client, buf, sizeof(buf)))!=0)
		{
		  printf("Message Received: %s\n", buf);
			write(client,buf,receive);
		}
		
		close(client);
	}
	
  close(sock);
  unlink(server_addr.sin_addr);

  return 0;
}