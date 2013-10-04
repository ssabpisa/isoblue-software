/*
* ISOBlue Setup Daemon
* Description: runs in background and waits for command sent via bluetooth by the BBB.
* 
* Author : Pat SSabpisal  <ssabpisa@purdue.edu>
*        : <contributors> 
*        : <contributors>
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

void writeConfig(FILE * a, Settings * b);
void dispatchProcess(char * filterskey); 
/* 
dispatchProcess: manages spawning of filter based on filterskey
                 filterkey is the concatenated list of PGNs user want to filter
  		 if two phone request to filter using the same filterkey,
 		 dispatchProcess will not spawn new process for the second device
		 but it will use the first process to send data to both device1 and device2.
*/

Settings * command_listen(Settings * st, const char * sfname){
   struct sockaddr_rc localaddr = { 0 }; 
   struct sockaddr_rc remoteaddr = { 0 };
   char buf[2048] = { 0 };
   int s, client, bytes_read;
   socklen_t opt = sizeof(remoteaddr); //Size of Address
   //connect to socket
   printf("Connecting to socket..\n");
   s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
   //defining the family of radio to use
   localaddr.rc_family = AF_BLUETOOTH;
   localaddr.rc_bdaddr = *BDADDR_ANY;
   localaddr.rc_channel = (uint8_t) 1; //port 1
   //bind socket to port 1 of first available BT adapter
   printf("Binding socket to port..\n");
   bind(s, (struct sockaddr *)&localaddr, sizeof(localaddr));
   listen(s, 5); //backlog = 1, maximum length to which the queue of pending connection may grow
   //begin accepting connections
   printf("Waiting for client..\n");
   while(1){ //keep trying 
   	client = accept(s, (struct sockaddr *)&remoteaddr, &opt); 
        if(client >= 0) break;
   }
   //convert address structure to string
   ba2str(&remoteaddr.rc_bdaddr, buf);
   printf("connected to %s\n", buf);
   
   Settings * sob = calloc(sizeof(Settings),1);
   strcpy(sob->device_ID, buf);

   int countcmd = 0; //count how many command has been issued from client
   int countpgn = 0; //count how many pgn has been set (temp)
   int MODE_SETFILTER = 0; //flag to check what type of data is the client sending
   sob->PGN_sets = malloc(sizeof(int)*20); /*max 20 pgns , for now*/
   memset(buf, 0, sizeof(buf));
   while(1){ //keep receiving until stop is encountered
      bytes_read = read(client, buf, sizeof(buf));
      if(bytes_read > 0){
         printf(">> %s\n", buf);
	 countcmd += 1;
      }
      /* TODO:try
         recv(s, buf, sizeof(buf), 0);
      */
      
      if(!strcmp(buf,SIGNAL_FINISH)){
        //if buffer is "finish"
	printf("FINISH SIGNAL received!!\n");
	printf("Spawning Filter..\n");
	char filterarg[1024] = "./filter vcan0 vcan0 -f ";
	char basename[1024] = "";
	strcpy(basename, sfname);
	strcat(basename, "_setting.config");
	strcat(filterarg, basename);
	system(filterarg);
        //Note: above commands should pass in "setting file" 
	// filter.c need to open up setting file (binary) and read the PGN_sets data

	//TODO: replace system with dispatch process

  	break;
      }

      
     
      if (!strcmp(buf,SIGNAL_SETFILTER)){ //if command is to set filter (defined in commands.h)
 	printf("Recognized Request to set filter\n");
	MODE_SETFILTER = 1;  //mark the flag 
      }else if(!strcmp(buf,SIGNAL_ENDLIST)){ 
        MODE_SETFILTER = 0; //unflag the setfilter flag
        printf("Filter saved\n");
      }else if(MODE_SETFILTER){ //if flagged
        printf("Adding %s to filter (%d)\n", buf, countpgn);
	sob->PGN_sets[countpgn++] = atoi(buf); //add to pgn sets
      }


      memset(buf,0,sizeof(buf)); //clear buffer so we can start reading again
   }
   

   close(client);
   close(s);
  
   return (countcmd == 0 ? NULL : sob);
   
}

void writeConfig(FILE * fp, Settings * st){
/*    int i = 0;
    fprintf(fp, "MASTER:%s\n", st->device_ID);
    fprintf(fp,"%s","ALLOW:");
    for(i = 0; i < 20; i++){ 
      fprintf(fp,"%d ",st->PGN_sets[i]);
    }
    fprintf(fp,"%s","\n");*/
    fwrite(st->device_ID, sizeof(char),20,fp);
    fwrite(st->PGN_sets,sizeof(int),20,fp);
}

int main(int argc, const char *argv[]){
   
   char * basename = malloc(sizeof(char)*(20+strlen(argv[1])));
   strcpy(basename,argv[1]);
   strcat(basename,"_setting.config");
   FILE * fout = fopen(basename, "wb"); 
   printf("Ready.\n");
   Settings * sob = command_listen(sob,argv[1]);
   if(sob == NULL){
       printf("Unable to create filter.");
       return EXIT_FAILURE;
   }
    
   //fwrite(sob, sizeof(Settings), 1,fout); 

   writeConfig(fout, sob);

   printf("\nOperation successful. Written to file %s\n",basename);
   free(sob);
   return EXIT_SUCCESS;
}
