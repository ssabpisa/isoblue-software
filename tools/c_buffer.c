#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void copy_to_permanent_storage(struct isobus_message mes, struct timeval tv, int iface, uint8_t addr, FILE *fptr1); //the function to store the messages permanently

void copy_to_permanent_storage(struct isobus_message mes, struct timeval tv, int iface, uint8_t addr, FILE *fptr1)
{
	
	fprintf(fptr1, "%d %d %d %d %d",iface, mes.pgn, tv.tv_sec, tv.tv_usec, addr);
    fflush (fptr1);

}