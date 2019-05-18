#include "head.h"
#include "md5.h"
int Compute_file_md5(const char *file_path, char *md5_str)
{
    int i;
    int fd;
    int ret;
    unsigned char data[READ_DATA_SIZE];
    unsigned char md5_value[MD5_SIZE];
    MD5_CTX md5;

    fd = open(file_path, O_RDONLY);
    if (-1 == fd)
    {
        perror("open");
        return -1;

    }
    //init md5
    MD5Init(&md5);
    while (1)
    {
        ret = read(fd, data, READ_DATA_SIZE);
        if (-1 == ret)
        {
            perror("read");
            return -1;
        }

        MD5Update(&md5, data, ret);

        if (0 == ret || ret < READ_DATA_SIZE)
        {
            break;
        }
    }

    close(fd);
    MD5Final(&md5, md5_value);
    for(i = 0; i < MD5_SIZE; i++)
    {
        snprintf(md5_str + i*2, 2+1, "%02x", md5_value[i]);
    }
    md5_str[MD5_STR_LEN] = '\0'; // add end
    return 0;
}

//客户端上传一个文件
int client_upload_file(int socket_fd,char *path,char *file_name,char *user_name,int dir_id)
{
    int ret;
    int file_fd;
    file_fd=open(path,O_RDONLY);
    //FUNC_ERROR(file_fd,-1,"open");//文件打不开会爆炸....
    if(-1==file_fd)
        goto lable0;
    struct stat stat0;
    ret=fstat(file_fd,&stat0);
    send(socket_fd,&ret,sizeof(int),0);
lable0:
    if(-1==file_fd || -1==ret)
    {
        printf("路径输入错误或文件不存在\n");
        return -1;
    }
    else
        printf("开始上传\n");
    file_data file_data0;
    memset(&file_data0,0,sizeof(file_data));
    strcpy(file_data0.file_name,file_name);
    strcpy(file_data0.user,user_name);
    file_data0.father_dir_file_id=dir_id;
    char md5[32];
    bzero(md5,32);
    Compute_file_md5(path,md5);
    printf("path is %s\n",path);
    printf("md5 is %s\n",md5);
    strcpy(file_data0.md5,md5);
    send(socket_fd,&file_data0,sizeof(file_data),0);
    return 0;
}
/*
int server_recv_file(int client_fd)
{
    int find_result;  
    recv(client_fd,&find_result,sizeof(int),0);
    if(-1==find_result)
    {
        printf("不必执行啦\n");
        return -1;
    }
    else
        printf("开始接收\n");
    
    file_data file_data0;
    memset(&file_data0,0,sizeof(file_data));
    recv(client_fd,&file_data0,sizeof(file_data),0);

    //find_result=mysql_find("select * from file where md5='",)
    if(1==find_result)
    {

    }
    else
    {
        
    }
    return 0;
}
*/
/*
int client_downlaod_file(int socket_fd,char *path)
{




}
*/
