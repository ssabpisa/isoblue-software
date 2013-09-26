/*
*  Settings for setup program that setups the settings for filtering etc..
*  Draft : 1
*  Author: Pat
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
   int setup_timestamp;
   int max_concurrent_connection;
   int device_ID; /*or other structure for device identification*/
   /* buffer filename is related to device ID */
   int streamingMode;

   int filteringMode;
   int * PGN_sets;
   

} Settings;

#endif
