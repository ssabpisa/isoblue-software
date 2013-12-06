/*
*   Second part of the buffer, Activiates when android asks for the list of messages and data based on timestamp
*
*
* Author(s): Joseph Chiu
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check();

int check()
{
    char line[1024] = {0,};
    int n2 = 0;
    int n3 = 0;
    
    double r_1 = 0;
    double r_2 = 0;
    double result = 0;

    int hold; //Send to android device as confirmation or as a string message
    double c_num = 1385144575.788001; //Testing timestamp pretend it is from android


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
