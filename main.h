#ifndef MAIN_H
#define MAIN_H

#define _TIMESPEC_DEFINED
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql.h>

#define QUERY_LENGTH 1024

typedef struct{
    MYSQL *connection;
    MYSQL_RES *result;
    MYSQL_ROW row;
    MYSQL_FIELD *column;
    char query[QUERY_LENGTH];
} Sql;


#endif