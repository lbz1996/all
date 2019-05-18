//#include "head.h"

int trans_file(int new_Fd)
{
    printf("%s will be transed\n",file_name);
    send(new_Fd,"hello",5,0);
    int file_fd=open(file_name,O_RDONLY);
    if(-1==file_fd)
    {
        perror("open");
        return -1;
    }
    int ret;
    struct stat statbuf;
    memset(&statbuf,0,sizeof(struct stat));
    ret=fstat(file_fd,&statbuf);
    if(-1==ret)
    {
        perror("fstat");
        return -1;
    }
    printf("it has %ld\n",statbuf.st_size);
    printf("-----------------------------------------\n");

    train train0;
    memset(&train0,0,sizeof(train));
    train0.data_len=statbuf.st_size;
    memcpy(train0.buf,file_name,strlen(file_name));
    send(new_Fd,&train0,sizeof(train),0);

    long send_file_len=statbuf.st_size;
    long sended_file_len=0;
    while(sended_file_len<=send_file_len)
    {
        memset(&train0,0,sizeof(train));
        ret=read(file_fd,train0.buf,sizeof(char)*100);
        sended_file_len+=ret;
        if(-1==ret)
        {
            perror("read");
            return -1;
        }
        else if(0==ret)
        {
             train0.data_len=-1;
             send(new_Fd,&train0,sizeof(train),0);
            break;
        }
        else
        {
             train0.data_len=ret;
             send(new_Fd,&train0,sizeof(train),0);
        }
    }
    return 0;
}
