#include "head.h"
#include "md5.h"


//ls实现
int client_ls(int socket_fd,int dir_id,char *user_name)
{
    int command_result;
    send(socket_fd,&dir_id,sizeof(int),0);
    send(socket_fd,user_name,32,0);
    recv(socket_fd,&command_result,sizeof(int),0);
    file_data_array file_data_array0;
    bzero(&file_data_array0,sizeof(file_data_array));
    if(0==command_result)
    {
        printf("当前目录下么有文件\n");
        return 0;
    }
    else
    {
        recv(socket_fd,&file_data_array0,sizeof(file_data_array),0);
        for(long r=0;r<file_data_array0.length;++r)
        {
            printf("file_id is %s\n",file_data_array0.file_data0[r].file_id);
            printf("file_name is %s\n",file_data_array0.file_data0[r].file_name);
            printf("user is %s\n",file_data_array0.file_data0[r].user);
            printf("md5 is %s\n",file_data_array0.file_data0[r].md5);
            printf("father is %s\n",file_data_array0.file_data0[r].father_dir_file_id);
            printf("file_size is %s\n",file_data_array0.file_data0[r].file_size);
            printf("absolute_path is %s\n",file_data_array0.file_data0[r].absolute_path);
            printf("finished is %s\n",file_data_array0.file_data0[r].finished);
            printf("\n");
        }
        return 1;
    }
}







int server_ls(int client_fd)
{
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
    printf("debug: temp_str is %s\n",temp_str);
    command_result=mysql_find("select * from file where father_dir_file_id ='",temp_str,"'",(void*)&file_data_array0,2);
    send(client_fd,&command_result,sizeof(int),0);
    if(0==command_result)
    {
        return 0;
    }
    else
    {
        printf("debug: file_data_array0.length is %ld\n",file_data_array0.length);
        printf("debug: file_data_array0.file_data[0].file_name is %s\n",file_data_array0.file_data0[0].file_name);
        send(client_fd,&file_data_array0,sizeof(file_data_array),0);
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
    if(0==command_result)
    {
        printf("当前目录下么有这个路径\n");
        return 0;
    }
    else
    {   if(-1==command_result)
        {
            printf("输入的不是目录!\n");
        }
        else if(1==command_result)
        {
            recv(socket_fd,dir_id,sizeof(file_data_array),0);
            printf("file_id is %d\n",*dir_id);
            //并用pwd打印;
        }
    }
    return 1;
}





int server_cd(int client_fd)
{
    int command_result;
    int dir_id;
    char user_name[32];
    char dir_name[32];
    recv(client_fd,&dir_id,sizeof(int),0);
    recv(client_fd,user_name,32,0);
    recv(client_fd,dir_name,32,0);
    char dir_id_str[11];
    bzero(dir_id_str,11);
    sprintf(dir_id_str,"%d",dir_id);printf("dir_id_str is %s\n",dir_id_str);

    file_data_array file_data_array0;
    bzero(&file_data_array0,sizeof(file_data_array));
    char temp_str[4096];
    bzero(temp_str,4096);
    sprintf(temp_str,"%s' and user = '%s' and file_name = '%s",dir_id_str,user_name,dir_name);
    //printf("debug: temp_str is %s\n",temp_str);
    command_result=mysql_find("select * from file where father_dir_file_id ='",temp_str,"'",(void*)&file_data_array0,2);
    if(S_ISDIR(file_data_array0.file_data0[0].file_type))
    {
        command_result=-1;
    }
    send(client_fd,&command_result,sizeof(int),0);
    printf("debug: command_result is %d\n",command_result);
    if(1!=command_result)
    {
        return 0;
    }
    else
    {
        printf("debug: file_data_array0.length is %ld\n",file_data_array0.length);
        printf("debug: file_data_array0.file_data[0].file_name is %s\n",file_data_array0.file_data0[0].file_name);
        send(client_fd,&file_data_array0.file_data0[0].file_id,11,0);
    }
    return 1;
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
    sprintf(temp,"%ld",stat0.st_size);//都是字符串....
    strcpy(file_data0.file_size,temp);
    memset(temp,0,20);
    sprintf(temp,"%d",dir_id);
    strcpy(file_data0.father_dir_file_id,temp);
    char md5[32];
    bzero(md5,32);
    Compute_file_md5(path,md5);
    printf("path is %s\n",path);
    printf("md5 is %s\n",md5);
    strcpy(file_data0.md5,md5);
    char father_dir_file_id[11];
    sprintf(father_dir_file_id,"%d",dir_id);
    strcpy(file_data0.father_dir_file_id,father_dir_file_id);
    file_data0.file_type=stat0.st_mode;
    //发送文件信息
    send(socket_fd,&file_data0,sizeof(file_data),0);
    //接收传输方式
    int use_mmap,write_to_tail;
    recv(socket_fd,&use_mmap,sizeof(int),0);
    recv(socket_fd,&write_to_tail,sizeof(int),0);
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
            ret=read(file_fd,train0.data,sizeof(char)*100);
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
    return 0;
}
//服务器端接收一个文件
int server_recv_file(int client_fd)
{
    int ret;
    //接收命令是否非法
    printf("in server_recv_file\n");
    int find_result;  
    recv(client_fd,&find_result,sizeof(int),0);
    if(-1==find_result)
    {
        printf("不必执行啦\n");
        return -1;
    }
    else
        printf("开始接收\n");





    //接收文件信息
    file_data file_data0;
    memset(&file_data0,0,sizeof(file_data));
    recv(client_fd,&file_data0,sizeof(file_data),0);
    //查找文件库中的信息
    file_data_array file_data_array0;
    memset(&file_data_array0,0,sizeof(file_data_array));
    find_result=mysql_find("select * from file where md5 ='",file_data0.md5,"'",(void *)&file_data_array0,2);
    //确定接收方式
    int use_mmap=0,write_to_tail=0;//0不是1是,全是-1表示磁盘上我有了
    long recved_file_size=0;
    sscanf(file_data0.file_size,"%ld",&recved_file_size);printf("recved_file_size is %ld\n",recved_file_size);
    if(0==find_result)
    {
        if(recved_file_size>100*1024*1024)
            use_mmap=1;
    }
    else if(1==find_result) 
    {
        printf("磁盘上已经有这个文件啦\n");
        if(0==atoi(file_data_array0.file_data0[0].finished))
        {
            write_to_tail=1;
            if(recved_file_size-atol(file_data_array0.file_data0[0].file_size)>100*1024*1024)
                use_mmap=1;
            else
                use_mmap=0;
        }
        else//(磁盘上有完整的)
        {
            use_mmap=-1;
            write_to_tail=-1;
            file_data_array file_data_array1;
            memset(&file_data_array1,0,sizeof(file_data_array));
            char temp176[4096];memset(temp176,0,sizeof(temp176));
            sprintf(temp176,"%s' and user = '%s",file_data0.md5,file_data0.user);
            find_result=mysql_find("select * from file where md5 ='",temp176,"'",(void *)&file_data_array1,2);
            if(0==find_result)//(么有完全相同的文件信息)
            {
                //mysql_insert("insert into file (file_id,file_name,user,file_type,md5,father_dir_file_id,file_size,absolute_path,finished) values(");
            }
            else if(1==find_result)
            {

            }
        }
    }
    //发送接收方式
    send(client_fd,&use_mmap,sizeof(int),0);
    send(client_fd,&write_to_tail,sizeof(int),0);
    //开始接收
    printf("debug 180line\n");
    int new_recved_file_fd;
    if(0==write_to_tail)
    {
        new_recved_file_fd=open(file_data0.md5,O_CREAT|O_EXCL|O_WRONLY,0777);
    }
    else if(1==write_to_tail)
    {
        new_recved_file_fd=open(file_data0.md5,O_CREAT|O_APPEND|O_WRONLY,0777);
    }
    if(0==use_mmap)
    {
        char s2[4096];
        //mysql_insert("insert into file(file_name,user,file_type,md5,father_dir_file_id,file_size)",);
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
            if(0==ret||-1==train0.data_len)
            {
                printf("over\n");
                break;
            }
            write(new_recved_file_fd,train0.data,train0.data_len);
            recved+=train0.data_len;
        }
    }
    else if(1==use_mmap)
    {
        long temp_len;
        if(0==write_to_tail)
            temp_len=recved_file_size;
        else
            temp_len=recved_file_size-atol(file_data_array0.file_data0[0].file_size);
        char *p;
        p=(char*) mmap(0,temp_len,PROT_WRITE,MAP_SHARED,new_recved_file_fd,0);
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
            if(0==ret||-1==train0.data_len)
            {
                printf("over\n");
                break;
            }
            //write(new_recved_file_fd,train0.data,train0.data_len);
            memcpy(p,train0.data,train0.data_len);
            recved+=train0.data_len;
        }
        msync(p,temp_len,MS_SYNC);
        munmap(p,temp_len);
    }
    close(new_recved_file_fd);
    //还得改finished
    return 0;
}


int client_download_file(int socket_fd,char *download_file_name,char *user_name,int dir_id)
{
    int ret;
    int find_result;
    //send文件信息
    send(socket_fd,download_file_name,32,0);
    send(socket_fd,user_name,32,0);
    send(socket_fd,&dir_id,sizeof(int),0);
    recv(socket_fd,&find_result,sizeof(int),0);
    if(1==find_result)
    {
        int file_fd=open(download_file_name,O_CREAT|O_EXCL|O_WRONLY,0777);
        long file_len;
        recv(socket_fd,&file_len,sizeof(long),0);
        printf("file_len is %ld\n",file_len);
        train train0;
        memset(&train0,0,sizeof(train));
        long recved=0;
        while(recved<=file_len)
        {
            memset(&train0,0,sizeof(train));
            ret=recv(socket_fd,&train0,sizeof(train),0);
            if(-1==ret)
            {
                perror("recv");
                return -1;
            }
            if(0==ret||-1==train0.data_len)
            {
                printf("over\n");
                break;
            }
            write(file_fd,train0.data,train0.data_len);
            recved+=train0.data_len;
        }
        return 1;
    }
    else
    {
        printf("没有那个文件或其他错误\n");
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
    char temp_str[4096];
    sprintf(temp_str,"%s' and father_dir_file_id = %d and user = '%s",download_file_name,dir_id,user_name);
    find_result=mysql_find("select * from file where file_name ='",temp_str,"'",(void *)&file_data_array0,2);
    send(client_fd,&find_result,sizeof(int),0);
    if(1==find_result)
    {
        train train0;
        memset(&train0,0,sizeof(train));
        long send_file_len=atol(file_data_array0.file_data0[0].file_size);
        printf("file_len is %ld\n",send_file_len);
        send(client_fd,&send_file_len,sizeof(long),0);
        int file_fd=open(file_data_array0.file_data0[0].absolute_path,O_RDONLY,0777);
        int ret;
        long sended_file_len=0;
        while(sended_file_len<=send_file_len)
        {
            memset(&train0,0,sizeof(train));
            ret=read(file_fd,train0.data,sizeof(char)*100);
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
    recv(socket_fd,&find_result,sizeof(int),0);
    if(1==find_result)
    {
        printf("recv to pwd\n");
        char out_str[4096];
        bzero(out_str,4096);
        recv(socket_fd,out_str,4096,0);
        printf("%s/\n",out_str);
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
    if(0==atoi(file_data_array0.file_data0[0].file_id))
    {
        find_result=233;
        send(client_fd,&find_result,sizeof(int),0);
        return 1;
    }
    else
    {
        char temp_str[4096];
        bzero(temp_str,4096);
        sprintf(temp_str,"select *from file where file_id = %d and user = '",dir_id);
        find_result=mysql_find(temp_str,user_name,"'",(void *)&file_data_array0,2)&&S_ISDIR(file_data_array0.file_data0[0].file_type);
        send(client_fd,&find_result,sizeof(int),0);
        char out_str[4096];
        if(1==find_result)
        {
            int father_dir_file_id=atoi(file_data_array0.file_data0[0].file_id);
            while(0!=find_result)
            {
                strcat(out_str,file_data_array0.file_data0[0].file_name);
                strcat(out_str,"/");
                father_dir_file_id=atoi(file_data_array0.file_data0[0].file_id);
                bzero(temp_str,4096);
                sprintf(temp_str,"select *from file where file_id = %d and user = '",father_dir_file_id);
                find_result=mysql_find(temp_str,user_name,"'",(void *)&file_data_array0,2)&&S_ISDIR(file_data_array0.file_data0[0].file_type);
            }
            strcat(out_str,user_name);
            strcat(out_str,"/");
            send(client_fd,out_str,4096,0);
            return 1;
        }
        else
            return 0;
    }
}


//mkdir
int client_mkdir(int socket_fd,char *dir_name,char *user_name,int dir_id)
{
    //int find_result;
    send(socket_fd,user_name,32,0);
    send(socket_fd,&dir_id,sizeof(int),0);
    send(socket_fd,dir_name,4096,0);
    //recv(socket_fd,&find_result,sizeof(int),0);
    return 1;
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
    sprintf(temp_str,"select *from file where father_dir_file_id = %d and file_name = %s and user = '",dir_id,dir_name);
    //printf("debug645:user_name is %s\n",user_name);
    find_result=mysql_find(temp_str,user_name,"'",(void *)&file_data_array0,2)&&S_ISDIR(file_data_array0.file_data0[0].file_type);
    if(0==find_result)
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
        printf("该目录下已经有这个目录名了或出了错\n");
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
    if(1==find_result)
    {
        if('0'==file_data_array0.file_data0[0].file_type)
        {
            sprintf(temp_str,"delete from file where file_name = '%s' and user = '%s' and father_dir_file_id = %d",file_name,user_name,dir_id);
            mysql_insert(temp_str," ");
        }
        else if('1'==file_data_array0.file_data0[0].file_type)
        {
            printf("这是个目录啊....");
        }
        send(client_fd,&find_result,sizeof(int),0);
        return 1;
    }
    else
    {
        printf("该目录下没有这个名字的东西\n");
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
        printf("in get_file_data\n");
        //row=mysql_fetch_row(res);//......

        strcpy(   (*p_user_data_array0).file_data0[r].file_id        ,row[0] );
        printf("file_id is %s\n",(*p_user_data_array0).file_data0[r].file_id);

        strcpy(   (*p_user_data_array0).file_data0[r].file_name        ,row[1] );
        printf("file_name is %s\n",(*p_user_data_array0).file_data0[r].file_name);

        strcpy(   (*p_user_data_array0).file_data0[r].user        ,row[2] );
        printf("user is %s\n",(*p_user_data_array0).file_data0[r].user);

        strcpy(   (*p_user_data_array0).file_data0[r].md5        ,row[4] );
        printf("md5 is %s\n",(*p_user_data_array0).file_data0[r].md5);

        strcpy(   (*p_user_data_array0).file_data0[r].father_dir_file_id        ,row[5] );
        printf("father is %s\n",(*p_user_data_array0).file_data0[r].father_dir_file_id);

        strcpy(   (*p_user_data_array0).file_data0[r].file_size        ,row[6] );
        printf("file_size is %s\n",(*p_user_data_array0).file_data0[r].file_size);

        strcpy((*p_user_data_array0).file_data0[r].absolute_path,row[7]);
        printf("absolute_path is %s\n",(*p_user_data_array0).file_data0[r].absolute_path);

        strcpy((*p_user_data_array0).file_data0[r].finished,row[8]);
        printf("finished is %s\n",(*p_user_data_array0).file_data0[r].finished);
        ++r;
    }
    (*p_user_data_array0).length=mysql_num_rows(res);
    return (*p_user_data_array0).length;
}         

