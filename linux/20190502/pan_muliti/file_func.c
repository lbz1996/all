#include "head.h"
#include "md5.h"



//ls实现
int client_ls(int socket_fd,int dir_id,char *user_name)
{
    int ret;
    int command_result;
    send(socket_fd,&dir_id,sizeof(int),0);
    send(socket_fd,user_name,32,0);
    recv(socket_fd,&command_result,sizeof(int),0);
    if(0>=command_result)
    {
        printf("当前目录下么有文件/目录\n");
        return 0;
    }
    else
    {
        file_data_array file_data_array0;
        //memset(&file_data_array0,0,sizeof(file_data_array0));
        //printf("file_data_array0 is %ld\n",sizeof(file_data_array0));
        ret=recv(socket_fd,&file_data_array0,sizeof(file_data_array0),MSG_WAITALL);
        //printf("recv ret is %d\n",ret);
        for(long r=0;r<file_data_array0.length;++r)
        {
            printf("%s ",file_data_array0.file_data0[r].file_name);
            printf("%s ",file_data_array0.file_data0[r].user);
            printf("%s ",file_data_array0.file_data0[r].md5);
            printf("%c ",file_data_array0.file_data0[r].file_type);
            printf("%s ",file_data_array0.file_data0[r].file_size);
            printf("%s",file_data_array0.file_data0[r].finished);
            printf("\n");
        }
        return 1;
    }
}


int server_ls(int client_fd)
{
    int ret;
    int command_result;
    int dir_id;
    char user_name[32];
    bzero(user_name,32);
    recv(client_fd,&dir_id,sizeof(int),0);
    recv(client_fd,user_name,32,0);
    char dir_id_str[11];
    sprintf(dir_id_str,"%d",dir_id);printf("dir_id_str is %s\n",dir_id_str);
    file_data_array file_data_array0;
    bzero(&file_data_array0,sizeof(file_data_array));
    char temp_str[4096];
    bzero(temp_str,4096);
    sprintf(temp_str,"%s' and user = '%s",dir_id_str,user_name);
    //printf("debug: temp_str is %s\n",temp_str);
    command_result=mysql_find("select * from file where father_dir_file_id ='",temp_str,"'",(void*)&file_data_array0,2);
    send(client_fd,&command_result,sizeof(int),0);
    if(0<command_result)
    {
        //printf("debug: file_data_array0.length is %ld\n",file_data_array0.length);
        //printf("debug: file_data_array0.file_data[0].file_name is %s\n",file_data_array0.file_data0[0].file_name);
        ret=send(client_fd,&file_data_array0,sizeof(file_data_array),0);
        //printf("send ret is %d\n",ret);
        /*
        for(long r=0;r<file_data_array0.length;++r)
        {
            //printf("file_id is %s\n",file_data_array0.file_data0[r].file_id);
            printf("%s ",file_data_array0.file_data0[r].file_name);
            printf("%s ",file_data_array0.file_data0[r].user);
            printf("%s \n",file_data_array0.file_data0[r].md5);
            //printf("father is %s\n",file_data_array0.file_data0[r].father_dir_file_id);
            printf("%s ",file_data_array0.file_data0[r].file_size);
            //printf("absolute_path is %s\n",file_data_array0.file_data0[r].absolute_path);
            printf("%s",file_data_array0.file_data0[r].finished);
            printf("\n");
        }
        */
    }
    return 1;
}






//cd实现
int client_cd(int socket_fd,int *dir_id,char *user_name,char *dir_name)
{
    int command_result;
    send(socket_fd,dir_id,sizeof(int),0);
    send(socket_fd,user_name,32,0);
    send(socket_fd,dir_name,32,0);
    recv(socket_fd,&command_result,sizeof(int),0);
    if(1==command_result)
    {
        recv(socket_fd,dir_id,sizeof(int),0);
        //printf("file_id is %d\n",*dir_id);
        return 1;
    }
    else
    {
        printf("当前目录下么有这个名字的目录\n");
        return 0;
    }
}

int server_cd(int client_fd)
{
    int command_result=1;
    int dir_id;
    char user_name[32];
    char dir_name[32];
    recv(client_fd,&dir_id,sizeof(int),0);
    recv(client_fd,user_name,32,0);
    recv(client_fd,dir_name,32,0);
    file_data_array file_data_array0;
    bzero(&file_data_array0,sizeof(file_data_array));
    char temp_str[4096];
    bzero(temp_str,4096);
    //printf("dir_name is %s\n",dir_name);
    if(0==strcmp(dir_name,"..")||0==strcmp(dir_name,"../"))
    {
        if(0!=dir_id)
        {
            sprintf(temp_str,"%d",dir_id);
            command_result=mysql_find("select * from file where file_id = ",temp_str," ",(void*)&file_data_array0,2);
            send(client_fd,&command_result,sizeof(int),0); 
            int out_id=atoi(file_data_array0.file_data0[0].father_dir_file_id);
            send(client_fd,&out_id,sizeof(int),0);
            //sprintf(temp_str,"%d",dir_id);
            //command_result=mysql_find("select * from file where file_id = ",temp_str," ",(void*)&file_data_array0,2);
            //send(client_fd,&command_result,sizeof(int),0);
            //printf("debug: command_result is %d\n",command_result);
            //if(1==command_result)
            //{
            //    int out_id=atoi(file_data_array0.file_data0[0].father_dir_file_id);
            //    send(client_fd,&out_id,sizeof(int),0);
            //}
        }
        else
        {
            command_result=1;
            send(client_fd,&command_result,sizeof(int),0);

            int out_id=0;
            send(client_fd,&out_id,sizeof(int),0);
        }

    }
    else
    {
        sprintf(temp_str,"%d and user = '%s' and file_type = 1 and file_name = '%s",dir_id,user_name,dir_name);
        command_result=mysql_find("select * from file where father_dir_file_id = ",temp_str,"'",(void*)&file_data_array0,2);
        send(client_fd,&command_result,sizeof(int),0);
        //printf("debug: command_result is %d\n",command_result);
        if(1==command_result)
        {
            int out_id=atoi(file_data_array0.file_data0[0].file_id);
            send(client_fd,&out_id,sizeof(int),0);
        }

    }
    //send(client_fd,&command_result,sizeof(int),0);
    return command_result;
}











//获得文件的md5
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
lable0:
    send(socket_fd,&ret,sizeof(int),0);
    if(-1==file_fd || -1==ret)
    {
        printf("路径输入错误或文件不存在\n");
        return -1;
    }
    else
        printf("开始上传\n");



    //保存文件信息到file_data0
    file_data file_data0;
    memset(&file_data0,0,sizeof(file_data));
    strcpy(file_data0.file_name,file_name);

    strcpy(file_data0.user,user_name); 


    char temp[20];
    memset(temp,0,20);
    char md5[32];
    bzero(md5,32);
    Compute_file_md5(path,md5);
    //printf("path is %s\n",path);
    //printf("md5 is %s\n",md5);
    strcpy(file_data0.md5,md5);

    memset(temp,0,20);
    sprintf(temp,"%ld",stat0.st_size);//都是字符串....
    strcpy(file_data0.file_size,temp);

    char father_dir_file_id[11];
    sprintf(father_dir_file_id,"%d",dir_id);
    strcpy(file_data0.father_dir_file_id,father_dir_file_id);
    //printf("debug%d: father_dir_file_id is %s\n",__LINE__,file_data0.father_dir_file_id);
    //printf("dir_id is %d\n",dir_id);
    //file_data0.reall_file_type=stat0.st_mode;
    char temp_str_275[11];memset(temp_str_275,0,sizeof(temp_str_275));
    sprintf(temp_str_275,"%d",stat0.st_mode);
    strcpy(file_data0.reall_file_type,temp_str_275);
    //先判断是不是目录
    ret=S_ISDIR(stat0.st_mode);
    send(socket_fd,&ret,sizeof(int),0);
    if(1==ret)
    {
        //file_data0.file_type='1'; 
        printf("上传的是一个目录\n");
    }
    else
    {
        file_data0.file_type='0';
        //发送文件信息
        send(socket_fd,&file_data0,sizeof(file_data),0);
        //接收dir_id下有没有md5相同且完成的文件
        recv(socket_fd,&ret,sizeof(int),0);
        if(0<ret)
        {
            recv(socket_fd,&ret,sizeof(int),0);
            if(0<ret)
            {
                printf("目录上有同名文件\n");
            }
            else
            {
                printf("磁盘上有,秒传\n");
            }
        }
        else
        {
            recv(socket_fd,&ret,sizeof(int),0);
            if(0<ret)
            {
                printf("%d目录下有同名文件\n",__LINE__);
                recv(socket_fd,&ret,sizeof(int),0);
                if(0==ret)
                {
                    printf("上传的断点续传(有空做....)\n");

                }
                else
                {
                    printf("不允许覆盖同路径下同名文件\n");
                }
            }
            else
            {
                printf("%d当前目录下不存在同名文件\n",__LINE__);
                //接收传输方式
                int use_mmap,write_to_tail;
                recv(socket_fd,&use_mmap,sizeof(int),0);
                //开始上传
                if(0==use_mmap||1==use_mmap)
                {
                    train train0;
                    memset(&train0,0,sizeof(train));
                    long send_file_len=stat0.st_size;
                    long sended_file_len=0;
                    while(sended_file_len<=send_file_len)
                    {
                        memset(&train0,0,sizeof(train));
                        ret=read(file_fd,train0.data,sizeof(char)*1000);
                        sended_file_len+=ret;
                        if(-1==ret)
                        {
                            perror("read");
                            return -1;
                        }
                        else if(0==ret)
                        {
                            train0.data_len=-1;
                            send(socket_fd,&train0,sizeof(train),0);
                            break;
                        }
                        else
                        {
                            train0.data_len=ret;
                            send(socket_fd,&train0,sizeof(train),0);
                        }
                    }
                }

            }
        }

    }
    return 0;
}
//服务器端接收一个文件
int server_recv_file(int client_fd)
{
    int ret;
    //接收命令是否非法
    printf("in server_recv_file\n");
    int find_result;  
    recv(client_fd,&find_result,sizeof(int),MSG_WAITALL);
    if(-1==find_result)
    {
        printf("不必执行啦\n");
        return -1;
    }
    else
        printf("开始接收\n");
    recv(client_fd,&ret,sizeof(int),0);
    if(1==ret)
    {
        printf("上传的是目录...\n");

    }
    else
    {
        //printf("debug%d:in recv file\n",__LINE__);
        printf("上传的是文件\n");
        //接收文件信息
        file_data file_data0;
        memset(&file_data0,0,sizeof(file_data));
        recv(client_fd,&file_data0,sizeof(file_data),MSG_WAITALL);

        file_data_array file_data_array0;
        memset(&file_data_array0,0,sizeof(file_data_array));
        //判断服务器里面有没有完成的同md5的文件
        char temp_str[4096];memset(temp_str,0,4096);
        sprintf(temp_str,"select * from file where md5 = '%s' and finished = 1",file_data0.md5);
        find_result=mysql_find(" ",temp_str," ",(void *) &file_data_array0,2);
        send(client_fd,&find_result,sizeof(int),0);
        if(0>=find_result)//没有,需要传
        {
            //printf("debug%d: in no file need recv\n",__LINE__);
            printf("磁盘上没有,需要传\n");
            //判断目录下是否有这个名字的文件
            memset(temp_str,0,4096);
            sprintf(temp_str,"select * from file where file_name = '%s' and user = '%s' and father_dir_file_id = %d",file_data0.file_name,file_data0.user,atoi(file_data0.father_dir_file_id));  
            find_result=mysql_find(" ",temp_str," ",(void *)&file_data_array0,2);
            send(client_fd,&find_result,sizeof(int),0);
            if(0<find_result)//目录下存在该名字的文件
            {
                printf("当前目录存在该名字的文件\n");
                ret=strcmp(file_data_array0.file_data0[0].md5,file_data0.md5);
                send(client_fd,&ret,sizeof(int),0);
                if(0==ret)
                {
                    printf("断点续传\n");
                }
                else
                {
                    printf("不允许覆盖同路径下同名文件\n");
                }
            }
            else//目录下不存在该名字的文件
            {
                printf("%d:当前虚拟目录不存在该名字的文件\n",__LINE__);
                //确定接收方式
                int use_mmap=0,write_to_tail=0;//0不是1是,全是-1表示磁盘上我有了
                printf("%d:file_size is %ld\n",__LINE__,atol(file_data0.file_size));
                if(atol(file_data0.file_size)>100*1024*1024)
                    use_mmap=1;
                //发送接收方式
                send(client_fd,&use_mmap,sizeof(int),0);
                //开始接收
                printf("开始接收 %d\n",__LINE__);
                int new_recved_file_fd;
                new_recved_file_fd=open(file_data0.md5,O_CREAT|O_RDWR,0777);            
                ftruncate(new_recved_file_fd,atol(file_data0.file_size));
                //new_recved_file_fd=open(file_data0.md5,O_CREAT|O_APPEND|O_WRONLY,0777);
                char s2[4096];memset(s2,0,4096);
                //printf("debug%d: file_type is %c ,father_dir_file_id is %s\n",__LINE__,file_data0.file_type,file_data0.father_dir_file_id);
                sprintf(s2,"insert into file(file_name , user ,file_type , md5 , father_dir_file_id , file_size , absolute_path , finished , really_file_type ) values('%s','%s',%c,'%s',%d,%ld,'%s',0,'%s')",file_data0.file_name,file_data0.user,file_data0.file_type,file_data0.md5,atoi(file_data0.father_dir_file_id),atol(file_data0.file_size),"/home/lbz/20190502/pan_muliti/",file_data0.reall_file_type);
                mysql_insert(" ",s2);
                if(0==use_mmap)
                {
                    train train0;
                    memset(&train0,0,sizeof(train));
                    long file_len=atol(file_data0.file_size);
                    long recved=0;
                    while(recved<=file_len)
                    {
                        memset(&train0,0,sizeof(train));
                        ret=recv(client_fd,&train0,sizeof(train),0);
                        if(-1==ret)
                        {
                            perror("recv");
                            return -1;
                        }
                        //if(0==ret)
                        if(-1==train0.data_len)
                        {
                            printf("over\n");
                            break;
                        }
                        write(new_recved_file_fd,train0.data,train0.data_len);
                        recved+=train0.data_len;
                    }
                }
                else //if(1==use_mmap)
                {
                    //printf("%d: use_mmap\n",__LINE__);
                    //long recved_file_size=0;
                    long temp_len;
                    if(0==write_to_tail)
                        temp_len=atol(file_data0.file_size);
                    else
                        temp_len=atol(file_data0.file_size)-atol(file_data_array0.file_data0[0].file_size);
                    char *p=NULL;
                    printf("mmap失败?\n");
                    printf("temp_len is %ld\n",temp_len);
                    p=(char*) mmap(NULL,temp_len,PROT_WRITE,MAP_SHARED,new_recved_file_fd,0);
                    //printf("p is %xxd\n",*p);
                    train train0;
                    memset(&train0,0,sizeof(train));

                    long file_len=temp_len;
                    long recved=0;
                    while(recved<=file_len)
                    {
                        memset(&train0,0,sizeof(train));
                        ret=recv(client_fd,&train0,sizeof(train),0);
                        //printf("ret is %d,recved is %ld\n",ret,recved);
                        if(-1==ret)
                        {
                            //printf("%d\n",__LINE__);
                            perror("recv");
                            return -1;
                        }
                        if(0==ret||-1==train0.data_len)
                        {
                            printf("over\n");
                            break;
                        }
                        //write(new_recved_file_fd,train0.data,train0.data_len);
                        memcpy(p+recved,train0.data,train0.data_len);
                        recved+=train0.data_len;
                    }
                    //msync(p,temp_len,MS_SYNC);
                    munmap(p,temp_len);
                }
                printf("over\n");
                memset(s2,0,sizeof(s2));
                sprintf(s2,"update file set finished =1 where file_name = '%s' and user = '%s' and father_dir_file_id = %d",file_data0.file_name,file_data0.user,atoi(file_data0.father_dir_file_id));
                mysql_insert(" ",s2);
                close(new_recved_file_fd);
            }
        }
        else
        {
            char s2[4096];memset(s2,0,4096);
            sprintf(s2,"select * from file where file_name = '%s' and user = '%s' and father_dir_file_id = %d ",file_data0.file_name,file_data0.user,atoi(file_data0.father_dir_file_id));
            ret=mysql_find(" ",s2," ",(void *)&file_data_array0,2);
            send(client_fd,&ret,sizeof(int),0);
            if(0<ret)
            {
                printf("目录下有同名文件");
            }
            else
            {
                printf("秒传\n");
                sprintf(s2,"insert into file(file_name , user ,file_type , md5 , father_dir_file_id , file_size , absolute_path , finished , really_file_type ) values('%s','%s',%c,'%s',%d,%ld,'%s',1,'%s')",file_data0.file_name,file_data0.user,file_data0.file_type,file_data0.md5,atoi(file_data0.father_dir_file_id),atol(file_data0.file_size),"/home/lbz/20190502/pan_muliti/",file_data0.reall_file_type);
                mysql_insert(" ",s2);
            }
        }
    }

    //还得改finished
    return 0;
}



int client_download_file(int socket_fd,char *download_file_name,char *user_name,int dir_id)
{
    //printf("工作目录下重名比它大的不会下载,比它小的如何确定是不是自己?\n");
    int ret;
    int find_result;
    //send文件信息
    send(socket_fd,download_file_name,32,0);
    send(socket_fd,user_name,32,0);
    send(socket_fd,&dir_id,sizeof(int),0);
    recv(socket_fd,&find_result,sizeof(int),0);
    if(1==find_result)
    {
        //int file_fd=open(download_file_name,O_CREAT|O_EXCL|O_WRONLY,0777);
        int file_fd=open(download_file_name,O_CREAT|O_WRONLY,0777);
        lseek(file_fd,0,SEEK_END);
        long file_len;
        recv(socket_fd,&file_len,sizeof(long),0);
        printf("file_len is %ld\n",file_len);

        struct stat stat0;
        ret=fstat(file_fd,&stat0);
        FUNC_ERROR(ret,-1,"fstat"); 
        printf("i have %ld \n",stat0.st_size);
        send(socket_fd,&stat0.st_size,sizeof(long),0);
        file_len=file_len-stat0.st_size;
        printf("%ld should be recved\n",file_len);
        if(file_len<0)
            printf("重名但是不可能续传\n");
        else
        {
            train train0;
            memset(&train0,0,sizeof(train));
            long recved=0;
            while(recved<=file_len)
            {
                memset(&train0,0,sizeof(train));
                ret=recv(socket_fd,&train0,sizeof(train),MSG_WAITALL);
                if(-1==ret)
                {
                    perror("recv");
                    return -1;
                }
                //if(0==ret||-1==train0.data_len)
                if(-1==train0.data_len)
                {
                    printf("over\n");
                    break;
                }
                write(file_fd,train0.data,train0.data_len);
                recved+=train0.data_len;
            }
            printf("i recv %ld\n",recved);
        }
        return 1;
    }
    else
    {
        printf("没有那个文件或其他错误(有那个文件但是没完成上传?...)\n");
        return 0;
    }
}


int server_send_file(int client_fd)
{
    int find_result;
    //接收文件信息
    char download_file_name[32];
    char user_name[32];
    int dir_id;
    recv(client_fd,download_file_name,32,0);
    recv(client_fd,user_name,32,0);
    recv(client_fd,&dir_id,sizeof(int),0);

    //查找文件库中的信息
    file_data_array file_data_array0;
    memset(&file_data_array0,0,sizeof(file_data_array));
    char temp_str[4196];
    sprintf(temp_str,"%s' and finished = 1 and file_type = 0 and father_dir_file_id = %d and user = '%s",download_file_name,dir_id,user_name);
    find_result=mysql_find("select * from file where file_name ='",temp_str,"'",(void *)&file_data_array0,2);
    send(client_fd,&find_result,sizeof(int),0);
    if(1==find_result)
    {
        train train0;
        memset(&train0,0,sizeof(train));
        long send_file_len=atol(file_data_array0.file_data0[0].file_size);
        printf("file_len is %ld\n",send_file_len);
        send(client_fd,&send_file_len,sizeof(long),0);

        sprintf(temp_str,"%s%s",file_data_array0.file_data0[0].absolute_path,file_data_array0.file_data0[0].md5);
        int file_fd=open(temp_str,O_RDONLY,0777);
        long offset;
        recv(client_fd,&offset,sizeof(long),0);
        printf("send from %ld\n",offset);
        lseek(file_fd,offset,SEEK_SET);
        send_file_len=send_file_len-offset;

        if(send_file_len<0)
            printf("同目录下存在同名且比他大的文件\n");
        else
        {
            int ret;
            long sended_file_len=0;
            while(sended_file_len<=send_file_len)
            {
                memset(&train0,0,sizeof(train));
                ret=read(file_fd,train0.data,sizeof(char)*1000);
                sended_file_len+=ret;
                if(-1==ret)
                {
                    perror("read");
                    return -1;
                }
                else if(0==ret)
                {
                    train0.data_len=-1;
                    send(client_fd,&train0,sizeof(train),0);
                    break;
                }
                else
                {
                    train0.data_len=ret;
                    send(client_fd,&train0,sizeof(train),0);
                }
            }
            printf("i send %ld\n",sended_file_len);
        }
        return 1;
    }
    else
        return 0;
}




//pwd
int client_pwd(int socket_fd,char *user_name,int dir_id)
{
    int find_result;
    send(socket_fd,user_name,32,0);
    send(socket_fd,&dir_id,sizeof(int),0);
    //int begin;
    recv(socket_fd,&find_result,sizeof(int),0);
    if(1==find_result)
    {
        //printf("recv to pwd\n");
        char out_str[4096];
        bzero(out_str,4096);
        //recv(socket_fd,&begin,sizeof(int),0);
        recv(socket_fd,out_str,4096,0);
        printf("%s\n",out_str);
        return 1;
    }
    else if(233==find_result)
    {
        printf("%s/\n",user_name);
        return 1;
    }
    else
    {
        printf("出错啦\n");
        return 0;
    }
}

int server_pwd(int client_fd)
{
    int ret;
    int find_result;
    char user_name[32];bzero(user_name,32);
    int dir_id;
    recv(client_fd,user_name,32,0);
    recv(client_fd,&dir_id,sizeof(int),0);

    //查找文件库中的信息
    file_data_array file_data_array0; memset(&file_data_array0,0,sizeof(file_data_array));
    //if(0==atoi(file_data_array0.file_data0[0].file_id))
    if(0==dir_id)
    {
        find_result=233;
        send(client_fd,&find_result,sizeof(int),0);
        ret=1;
    }
    else
    {
        char temp_str[4096];
        bzero(temp_str,4096);
        sprintf(temp_str,"select *from file where file_id = %d and file_type = 1 and user = '",dir_id);
        find_result=mysql_find(temp_str,user_name,"'",(void *)&file_data_array0,2);
        send(client_fd,&find_result,sizeof(int),0);
        char out_str[4096];memset(out_str,0,4096);
        if(1==find_result)
        {
            int father_dir_file_id=dir_id;
            while(0<find_result)
            {
                //printf("/---    %s/",out_str);
                bzero(temp_str,4096);
                sprintf(temp_str,"select *from file where file_id = %d and user = '",father_dir_file_id);
                find_result=mysql_find(temp_str,user_name,"'",(void *)&file_data_array0,2);
                bzero(temp_str,4096);
                sprintf(temp_str,"%s/",file_data_array0.file_data0[0].file_name);
                strcat(temp_str,out_str);
                strcpy(out_str,temp_str); 
                father_dir_file_id=atoi(file_data_array0.file_data0[0].father_dir_file_id);
                if(father_dir_file_id==0)
                {
                    break;
                }
            }
                sprintf(temp_str,"%s/",user_name);
                strcat(temp_str,out_str);
                strcpy(out_str,temp_str); 
            //send(client_fd,&begin,sizeof(int),0);
            send(client_fd,out_str,4096,0);
            ret=1;
        }
        else
            ret=0;
    }
    return ret;
}


//mkdir
int client_mkdir(int socket_fd,char *dir_name,char *user_name,int dir_id)
{
    //printf("int client_mkdir: my pwd is %d\n",dir_id);
    int find_result;
    send(socket_fd,user_name,32,0);
    send(socket_fd,&dir_id,sizeof(int),0);
    send(socket_fd,dir_name,4096,0);
    recv(socket_fd,&find_result,sizeof(int),0);
    return find_result;
}
int server_mkdir(int client_fd)
{
    int find_result;
    char dir_name[32];bzero(dir_name,32);
    char user_name[32];bzero(user_name,32);
    int dir_id;
    recv(client_fd,user_name,32,0);
    //printf("debug639:user_name is %s\n",user_name);
    recv(client_fd,&dir_id,sizeof(int),0);
    recv(client_fd,dir_name,32,0);
    file_data_array file_data_array0; memset(&file_data_array0,0,sizeof(file_data_array));
    char temp_str[4096];
    bzero(temp_str,4096);
    sprintf(temp_str,"select *from file where father_dir_file_id = %d and file_type = 1 and file_name = '%s' and user = '",dir_id,dir_name);
    //printf("debug645:in server_mkdir user_name is %s\n",user_name);
    find_result=mysql_find(temp_str,user_name,"'",(void *)&file_data_array0,2);
    //printf("find_result is %d\n",find_result);
    if(1!=find_result)
    {
        find_result=1;
        sprintf(temp_str,"insert into file (file_name,user,file_type,md5,father_dir_file_id,file_size,absolute_path,finished) values('%s','%s',%d,'假的他没有',%d,0,'假的他没有',1)",dir_name,user_name,1,dir_id);
        mysql_insert(temp_str," ");
        send(client_fd,&find_result,sizeof(int),0);
        return 1;
    }
    else
    {
        find_result=0;
        //printf("该目录下已经有这个目录名了或出了错\n");
        send(client_fd,&find_result,sizeof(int),0);
        return 0;
    }
}

//remove
int client_remove(int socket_fd,char *file_name,char *user_name,int dir_id)
{
    //int find_result;
    send(socket_fd,user_name,32,0);
    send(socket_fd,&dir_id,sizeof(int),0);
    send(socket_fd,file_name,4096,0);
    //recv(socket_fd,&find_result,sizeof(int),0);
    char out[50];bzero(out,50);
    recv(socket_fd,out,50,0);
    printf("%s\n",out);
    return 1;
}
int server_remove(int client_fd)
{
    int find_result;
    char file_name[32];bzero(file_name,32);
    char user_name[32];bzero(user_name,32);
    int dir_id;
    recv(client_fd,user_name,32,0);
    recv(client_fd,&dir_id,sizeof(int),0);
    recv(client_fd,file_name,32,0);
    file_data_array file_data_array0; memset(&file_data_array0,0,sizeof(file_data_array));
    char temp_str[4096];
    bzero(temp_str,4096);
    sprintf(temp_str,"select *from file where father_dir_file_id = %d and file_name = '%s' and user = '",dir_id,file_name);
    find_result=mysql_find(temp_str,user_name,"'",(void *)&file_data_array0,2);
    //printf("in remove %d find_result is %d\n",__LINE__,find_result);
    char out[50];bzero(out,50);
    if(1==find_result)
    {
        if('0'==file_data_array0.file_data0[0].file_type)
        {
            sprintf(temp_str,"delete from file where file_type = 0 and file_name = '%s' and user = '%s' and father_dir_file_id = %d",file_name,user_name,dir_id);
            mysql_insert(temp_str," "); 
            strcpy(out,"删除成功");
            send(client_fd,out,50,0);
        }
        else if('1'==file_data_array0.file_data0[0].file_type)
        {
            strcpy(out,"这是个目录啊....(未完成)");
            send(client_fd,out,50,0);
        }
        //send(client_fd,&find_result,sizeof(int),0);
        return 1;
    }
    else
    {
        strcpy(out,"该目录下没有这个名字的东西");
        send(client_fd,out,50,0);
        send(client_fd,&find_result,sizeof(int),0);
        return 0;
    }
}







int get_file_data(file_data_array *p_user_data_array0,MYSQL_ROW row,MYSQL_RES *res)
{
    //printf("debug array0 is %p\n",p_user_data_array0);
    int r=0;
    while((row=mysql_fetch_row(res))!=NULL)
    {   
        //printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
        // printf("in get_file_data\n");
        //row=mysql_fetch_row(res);//......

        strcpy(   (*p_user_data_array0).file_data0[r].file_id        ,row[0] );
        //printf("file_id is %s\n",(*p_user_data_array0).file_data0[r].file_id);

        strcpy(   (*p_user_data_array0).file_data0[r].file_name        ,row[1] );
        //printf("file_name is %s\n",(*p_user_data_array0).file_data0[r].file_name);

        strcpy(   (*p_user_data_array0).file_data0[r].user        ,row[2] );
        //printf("user is %s\n",(*p_user_data_array0).file_data0[r].user);

        (*p_user_data_array0).file_data0[r].file_type=*(row[3]);
        //printf("file_type is %c\n",(*p_user_data_array0).file_data0[r].file_type);

        strcpy(   (*p_user_data_array0).file_data0[r].md5        ,row[4] );
        //printf("md5 is %s\n",(*p_user_data_array0).file_data0[r].md5);

        strcpy(   (*p_user_data_array0).file_data0[r].father_dir_file_id        ,row[5] );
        //printf("father is %s\n",(*p_user_data_array0).file_data0[r].father_dir_file_id);

        strcpy(   (*p_user_data_array0).file_data0[r].file_size        ,row[6] );
        //printf("file_size is %s\n",(*p_user_data_array0).file_data0[r].file_size);

        strcpy((*p_user_data_array0).file_data0[r].absolute_path,row[7]);
        //printf("absolute_path is %s\n",(*p_user_data_array0).file_data0[r].absolute_path);

        strcpy((*p_user_data_array0).file_data0[r].finished,row[8]);
        //strcpy((*p_user_data_array0).file_data0[r].reall_file_type,row[9]);
        //printf("finished is %s\n",(*p_user_data_array0).file_data0[r].finished);
        ++r;
        //printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
    }
    (*p_user_data_array0).length=mysql_num_rows(res);
    return (*p_user_data_array0).length;
}         

