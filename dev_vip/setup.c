/*
* ISOBlue Setup Daemon
* Description: runs in background and waits for command sent via bluetooth by the BBB.
* 
* Author : Pat S. <ssabpisa@purdue.edu>
*        : 
*        :
*/


#include <stdio.h>
#include <stdlib.h>
#include "settings.h"
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include "commands.h"

void dispatchProcess(char * filterskey); 
/* 
dispatchProcess: manages spawning of filter based on filterskey
                 filterkey is the concatenated list of PGNs user want to filter
  		 if two phone request to filter using the same filterkey,
 		 dispatchProcess will not spawn new process for the second device
		 but it will use the first process to send data to both device1 and device2.
*/

void command_listen(Settings * st){
   struct sockaddr_rc localaddr = { 0 }; 
   struct sockaddr_rc remoteaddr = { 0 };
   char buf[2048] = { 0 };
   int s, client, bytes_read;
   socklen_t opt = sizeof(remoteaddr); //Size of Address
   //connect to socket
   printf("Connecting to socket..\n");
   s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
   localaddr.rc_family = AF_BLUETOOTH;
   localaddr.rc_bdaddr = *BDADDR_ANY;
   localaddr.rc_channel = (uint8_t) 1; //port 1
   //bind socket to port 1 of first available BT adapter
   printf("Binding socket to port..\n");
   bind(s, (struct sockaddr *)&localaddr, sizeof(localaddr));
   listen(s, 1); //backlog = 1, maximum length to which the queue of pending connection may grow
   //begin accepting connections
   printf("Waiting for client..\n");
   client = accept(s, (struct sockaddr *)&remoteaddr, &opt); 
   //convert address structure to string
   ba2str(&remoteaddr.rc_bdaddr, buf);
   printf("connected to %s\n", buf);
   //clear buffer
   memset(buf, 0, sizeof(buf));
 
   //keep reading until halt is encountered
   //while(strcmp(buf,"halt") != 0){
   while(1){
      bytes_read = read(client, buf, sizeof(buf));
      if(bytes_read > 0){
         printf("received: %s\n", buf);
      }
      /* TRY:
         recv(s, buf, sizeof(buf), 0);
      */
      memset(buf,0,sizeof(buf)); 
   }
   
   close(client);
   close(s);
   return;
   
}

int main(int argc, const char *argv[]){
   Settings * sob = calloc(sizeof(Settings),1); 
   char * basename = malloc(sizeof(char)*(20+strlen(argv[1])));
   strcpy(basename,argv[1]);
   strcat(basename,"_setting.config");

   FILE * fout = fopen(basename,"wb"); 
   
   printf("Ready.\n");
   command_listen(sob);
   
   fwrite(sob, sizeof(Settings), 10,fout); 
   return EXIT_SUCCESS;
}
