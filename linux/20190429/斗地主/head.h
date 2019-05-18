#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
#define MAX_TABLES_LEN 10
typedef struct table
{
    int people_lenth;
    int stat;
}table,*ptable;

typedef struct hall
{
    table tables[MAX_TABLES_LEN];
}hall,*phall;



