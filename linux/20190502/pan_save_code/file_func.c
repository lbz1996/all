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
int client_upload_file(int socket_fd,char *path)
{
    char md5[32];
    bzero(md5,32);
    Compute_file_md5(path,md5);
    printf("path is %s\n",path);
    printf("md5 is %s\n",md5);
    return 0;
}
int server_recv_file(int client_fd,char *file_name,char *user_name)
{
    



}

int client_downlaod_file(int socket_fd,char *path)
{




}

