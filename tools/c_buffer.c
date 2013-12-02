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
int check();

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


int check()
{
    char line[1024] = {0,};
    int n2 = 0;
    int n3 = 0;
    
    double r_1 = 0;
    double r_2 = 0;
    double result = 0;

    int hold; //Send to android device as confirmation or as a string message
    double c_num = 1385144575.788001; //Testing timestamp


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

            if (result == c_num)
            {
                hold = 0;
                //printf("Success\n");
                //printf("hold: %d\n", hold);
                //printf("%.6f\n", result); 
            }

            else
            {
                hold = 1;
                //printf("No Success\n");
                //printf("hold: %d\n", hold);
                //printf("%.6f\n", result);
            }

            //The result from txt file
            //printf("%d.%d\n", n2, n3);
        }
    }
    return(hold);

    //printf("%d\n", hold);
}

int main(int argc, char *argv[]) 
{
    int save;
    //Figure out the arguements

    if(argc != 2) 
    {
        return -1;
        //Checks if the two arguments in argv are real (The check and copy function)
    }

    if(0 == strcmp(argv[1], "copy_to_permanent_storage"))
    {
        copy_to_permanent_storage(struct isobus_mesg mes, struct timeval tv, int iface, uint8_t addr, FILE *fptr1);
    }

    else if (0 == strcmp(argv[1] "check"))
    {
        save = check();
        printf("checking for timestamp\n");
        printf("hold: %d", save);
    }
    else 
    {
         return -1; 
    }


    return(0);
}

