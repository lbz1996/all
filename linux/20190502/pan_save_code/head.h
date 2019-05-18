#ifndef __HEAD_H__
#define __HEAD_H__
#define _XOPEN_SOURCE
#include<arpa/inet.h>
#include<crypt.h>
#include<fcntl.h>
#include<mysql/mysql.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<time.h>
#include<unistd.h>
#define FUNC_ERROR(ret,retval,func)\
{\
    if(ret==retval)\
    {    perror(func);\
        return -1;\
    }\
    else\
    printf("%s success\n",func);\
}\

#define STR_LEN 10
typedef struct train
{
    long datalen;
    char data[1000];
}train;

//用户数据
typedef struct user_data
{
    char user_id[11];
    char user_name[32];
    char salt[128];
    char passwd[255];
}user_data;
typedef struct user_data_array
{
    int length;
    user_data user_data0[128];
}user_data_array;

//文件数据
typedef struct file_data
{
    int file_data;
    char file_name[255];
    char user[32];
    int file_type;
    char md5[32];
    char absolute_path[4096];
    char relative_path[4096];
    char father_path[4096];
}file_data;
typedef struct file_data_array
{
    int length;
    file_data file_data0[128];
}file_data_array;

//md5
#define READ_DATA_SIZE  1024
#define MD5_SIZE        16
#define MD5_STR_LEN     (MD5_SIZE * 2)

//数据库操作
char *generate_str();
int mysql_find(char *s1,char *s2,void *save,int which);
int mysql_insert(char *s1,char *s2);
//用户操作
int client_login(int socket_fd);
int verify_login(int client_fd);
int get_user_data(user_data_array *p_user_data_array0,MYSQL_ROW row,MYSQL_RES *res);
//文件操作
int Compute_file_md5(const char *file_path,char *md5_str);
int client_upload_file(int socket_fd,char *path);
int server_recv_file(int client_fd,char *file_name,char *user_name,char *absolute_path,char *belong_dir_file_id);
int client_download_file(int socket_fd,char *path);
int server_trans_file();
#endif
