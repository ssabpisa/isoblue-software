/*
* ISOBlue Circular Buffer
* Creates a database.txt to store incoming data such as pgn, socket, Timestamp and Address
*
* Accepts incoming Android device messages to check if its data(through unix timestamp) is up to data
* Finds the current timestamp from database.txt, compares to the android's timestamp and sends 
* back a confirmation
*
* Author(s): Joseph Chiu <chiu12@purdue.edu>
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *sync;

void copy_to_permanent_storage(struct isobus_mesg mes, struct timeval tv, int iface, uint8_t addr, FILE *fptr1); //the function to store the messages permanently


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

    exit(0);


}


//Issue, how to run this function once the first function stops
//Have timestamp (in unix time) from android
/*
int main(void)
{
    char line[1024] = {0,};
    int n2 = 0;
    int n3 = 0;
    
    double r_1 = 0;
    double r_2 = 0;
    double result = 0;

    double c_num = 1385144575.788001; //Testing check

    int hold; //Send to android device or change to string as a message


    sync = fopen("database.txt","r");
    
    
    if(sync != NULL) 
    {
        while( fgets(line, 1024, sync) != NULL)
        {
            //Nothing
        }

        fclose(sync);

        if (sscanf(line, "%*[^T]Time: %d.%d", &n2, &n3))
        {
            //to convert the n2 and n3 into the timestamp
            r_1 = n2;
            r_2 = n3 / 1000000.0;
            result = r_1 + r_2;
            // printf("%.6f\n", result);
            //Replace c_num with the android timestamp

            if ( result == c_num)
            {
                //printf("Success\n");
                hold = 0;
            }

            else
            {
                //printf("No Success\n");
                hold = 1;
            }

            //The result from txt file
            //printf("%d.%d\n", n2, n3);
        }
    }

   
}
*/
