#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void copy_to_permanent_storage(struct isobus_mesg mes, struct timeval tv, int iface, uint8_t addr, FILE *fptr1); //the function to store the messages permanently

void copy_to_permanent_storage(struct isobus_mesg mes, struct timeval tv, int iface, uint8_t addr, FILE *fptr1)
{
<<<<<<< HEAD
	
	fprintf(fptr1, "messages: %d %d %d %d %d\n",iface, mes.pgn, tv.tv_sec, tv.tv_usec, addr);
=======
    fprintf(fptr1, "messages: %d %d %d %d %d\n",iface, mes.pgn, tv.tv_sec, tv.tv_usec, addr);
>>>>>>> 5de8a86e1276ddc44094da316726ed0b5d9f6cd7
    fflush (fptr1);

}
