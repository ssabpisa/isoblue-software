#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void copy_to_permanent_storage(struct isobus_mesg mes, struct timeval tv, int iface, uint8_t addr, FILE *fptr1); //the function to store the messages permanently
//void check();


void copy_to_permanent_storage(struct isobus_mesg mes, struct timeval tv, int iface, uint8_t addr, FILE *fptr1)
{
	int i;

	fprintf(fptr1, " Socket: %d PGN: %d Data: ", iface, mes.pgn);

    for (i = 0; i < mes.dlen; i++)
    {
       fprintf(fptr1, "%02x", mes.data[i]);//Array of the data
    
    }

    fprintf(fptr1, " Time: %d.%06d Address: %d \n", tv.tv_sec, tv.tv_usec, addr);
    fflush (fptr1);

}

// void check(/*TimeStamp*/)
// {
// 	char us[6]; //to hold the string for the mircoseconds
// 	char ns[16]; //to hold the timestamp (seconds) from database.txt
	
// 	fp = fopen("database.txt",r);
// 	fscanf(fptr1,"%d.%0.6d",ns,us);
	

// 	if (/*TimeStamp*/ == )
// }