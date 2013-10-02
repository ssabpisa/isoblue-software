#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include "../settings.h"
#include "../commands.h"

int main(int argc, char **argv)
{
    struct sockaddr_rc addr = { 0 };
    int s, status;
    char dest[18] = "";
    strcpy(dest,argv[1]); //take first argument as server address
 
    // allocate a socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    printf("%d",s);
    // set the connection parameters (who to connect to)
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;
    str2ba( dest, &addr.rc_bdaddr );

    // connect to server
    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));

    // send a message
    if( status == 0 ) {
      int a = 0;
      for(a=2;a<argc;a++){
     	send(s, argv[a], strlen(argv[a]),0);
      }
      send(s, SIGNAL_FINISH, strlen(SIGNAL_FINISH),0); 
   }
    
    if( status < 0 ){
 	perror(dest);
    }
    

    close(s);
    return 0;
}

