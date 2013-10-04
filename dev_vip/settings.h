/*
*  Settings for setup program that setups the settings for filtering etc..
*  Draft : 1
*  Author: Pat Sabpisal <ssabpisa@purdue.edu>
*/

#ifndef ISOB_SETTINGS_H
#define ISOB_SETTINGS_H

#define DOWNLOAD_PAST 0           // Just stuff in the past
#define RT_STREAM 1	          // Realtime streaming from now on
#define DOWNLOAD_SPECIFIC 2       // Just some specific timeframe
#define RT_STREAM_AND_DOWNLOAD 3  // Realtime streaming (while downloading past data)

#define BLOCK_PGN_SET 0
#define ALLOW_PGN_SET 1
#define ALLOW_ALL_PGN 2

typedef struct _Settings{
   //Note Setting structure is 1 object per device
   int setup_timestamp;
   int max_concurrent_connection;
   char device_ID[20]; 
   /*or other structure for device identification*/
   /* buffer filename is related to device ID */
   /* different devices will spawn new process of daemon anyway */
   /* and each daemon will just create new files */
   
   int streamingMode;

   int filteringMode;
   int * PGN_sets;  
   int tractor_makeModel_ID; //Relates to what tractor so we can later find out what PGN means what
   

} Settings;

#endif
