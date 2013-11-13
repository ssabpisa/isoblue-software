#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void copy_to_permanent_storage(struct isobus_mesg mes, struct timeval tv, int iface, uint8_t addr, FILE *fptr1); //the function to store the messages permanently

void copy_to_permanent_storage(struct isobus_mesg mes, struct timeval tv, int iface, uint8_t addr, FILE *fptr1)
{
	
	fprintf(fptr1, "Socket: %d pgn: %d time: %d.%d Address: %d\n",iface, mes.pgn, tv.tv_sec, tv.tv_usec, addr);
    fflush (fptr1);

}