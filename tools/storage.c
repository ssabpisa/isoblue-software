/*
 * ISOBlue Data Replay Library
 */

#include <stdlib.h>
#include <stdio.h>

typedef struct isodata{
  int TS_created;
  int TS_modified;
  
  int num_record;
  struct record * table;

}isodata;
/* interface for "playback" save type */

typedef struct record{
  int id;
  int PGN;
  int bin_data;
  int TS;
  struct isoblue_record * next;	
}record;
/* interface for data record type */

ISODATA * search_isodata();
/* check if this BBB contains past data
   return NULL if not found
   return file pointer to data if found

