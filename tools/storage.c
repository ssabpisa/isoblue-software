/*
 * ISOBlue Data Replay Library
 */

#include <stdlib.h>
#include <stdio.h>

//list_H will be replaced by the data file with PGN
#ifndef LIST_H
#define LIST_H

typedef struct record{
  long id; //running record ID for synchronization 
  int PGN;
  int bin_data;
  int TS;

  struct record * next; 
}record;
/* interface for data record type */

typedef struct bluDB{  
  long num_record;
  long running_id; //current maximum ID reached
  long updated_time;

  FILE * src; //char * src
  record * table;
}bluDB;
/* interface for "playback" save type */


void insert_record(record * r, bluDB * b);
bluDB * get_DB();
bluDB * build_DB();
int save_DB(bluDB * d);

bluDB * get_DB(){
  FILE * f = fopen("store.data","rb+");
  if(f == NULL){
    return NULL;
  }
  bluDB * b = malloc(sizeof(bluDB));
  //load data
  size_t header_status = fread(b,sizeof(bluDB),1,f);

  printf("Updated Time: %ld\n", b->updated_time);
  printf("# Records: %ld\n", b->num_record);

  
  int rc = 0;
  while(rc < b->num_record){
    record * rtemp = malloc(sizeof(record));
    size_t ss = fread(rtemp,sizeof(record),1,f);
    printf("ID: %02d | PGN: %ld | data: <0x%08x> | TS: %010ld  \n", rc, rtemp->PGN, rtemp->bin_data, rtemp->TS);
    free(rtemp);
    rc++;
  }

  return b;
}

bluDB * build_DB(){
  //build a database
  FILE * f = fopen("store.data","wb");
  bluDB * newdb = malloc(sizeof(bluDB));
  newdb->num_record = 0;
  newdb->running_id = 0;
  newdb->updated_time = 90000044; //dummy value
  newdb->table = NULL;
  newdb->src = NULL;

  fwrite(newdb,sizeof(bluDB),1,f);
  fclose(f);
  return newdb;
}

//*Search Function -Using Linked list
//Record is node, r = head, bluDB * b is int v, work in progress
void insert_search(record * r, bluDB * b)
{
  record * r = b->table; //head node of the list/database
  while (r != NULL)
  {
    if ((r -> bluDB * b))
    {
      return r;
    }
    r = r -> next; 
  }
  return r;
}

void insert_record(record * r, bluDB * b){
  if(r == NULL){
    fprintf(stderr, "Record cannot be NULL!");
    return;
  }
  if(b->table == NULL){ //table is empty
    b->table = r;
  }else{
    record * Nx = b->table;
    record * Px = NULL;
    while(Nx != NULL){
      Px = Nx;
      Nx = Nx->next;
    }
  
    Px = r;
  }


  b->num_record = b->num_record + 1;
  
  //rewrite header at beginning of file
  FILE * fh = fopen("store.data","rb+");
  fwrite(b,sizeof(bluDB),1,fh);
  fclose(fh);


  //append record to end of file
  FILE * f = fopen("store.data","ab+");
  fwrite(r,sizeof(record),1,f);
  fclose(f);

  return;
}

//*Joseph's Function-work in progress, delete function
void delete_record(record * r, bluDB * b)
{
  printf("delete %d\n", bluDB * b)
  r = b->table;
  record * r =  bluDB * b;
  if (r == NULL) /*do nothing as it is an empty list*/
  {
    return r;
  }

  /*delete the first node*/
  if ((r -> value) == v)
  {
    r = r -> next;
    free (head);
    return r;
  }
//Not deleting the first node

  record * r = r -> next;
  q = r -> next;
  while ((q != NULL)  &&  ((q -> value) != v))
  {
    //Checking if q is NULL
    r = r -> next;
    q = q -> next;
  }

  if (q  != NULL)
  {
    r -> next = q -> next;
    free (q);
  }

return r;

}

int main(){
  bluDB * d = build_DB();
  

  int i;
  for(i = 0; i< 100; i++){
   record * r = malloc(sizeof(record));
   r->PGN = i + 300;
   r->bin_data = 0x01 << i ;
   r->TS = i*2 + 9000000;
   r->next = NULL;
   insert_record(r,d);   
  }
  bluDB * x = get_DB();

  return 0;
}

