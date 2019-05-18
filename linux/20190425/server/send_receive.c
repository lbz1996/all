//#include "head.h"
int sendfd(int pass_fd,int transed_fd)
{
    struct msghdr msghdr0;
    memset(&msghdr0,0,sizeof(struct msghdr));

    char tempstr[6]="hello";
    struct iovec iov;
    iov.iov_base=&tempstr;
    iov.iov_len=5;
    
    msghdr0.msg_iov=&iov;
    msghdr0.msg_iovlen=1;
    
    struct cmsghdr *cmsghdr0;
    cmsghdr0=(struct cmsghdr *) calloc(0,1);
    int len=CMSG_LEN(sizeof(int));
    cmsghdr0->cmsg_len=len;
    cmsghdr0->cmsg_type=SCM_RIGHTS;
    cmsghdr0->cmsg_level=SOL_SOCKET;
    *(int *)CMSG_DATA(cmsghdr0)=transed_fd;
    msghdr0.msg_control=cmsghdr0;
    msghdr0.msg_controllen=len;

    int ret;
    ret=sendmsg(pass_fd,&msghdr0,0);
    if(-1==ret)
    {
        perror("sendmsg");
        return -1;
    }
    return 0;
}

int recvfd(int pass_fd,int *transed_fd)
{
    struct msghdr msghdr0;
    memset(&msghdr0,0,sizeof(struct msghdr));

    char tempstr[6]="hello";
    struct iovec iov;
    iov.iov_base=&tempstr;
    iov.iov_len=5;
    
    msghdr0.msg_iov=&iov;
    msghdr0.msg_iovlen=1;
    
    struct cmsghdr *cmsghdr0;
    cmsghdr0=(struct cmsghdr *) calloc(0,1);
    int len=CMSG_LEN(sizeof(int));
    cmsghdr0->cmsg_len=len;
    cmsghdr0->cmsg_type=SCM_RIGHTS;
    cmsghdr0->cmsg_level=SOL_SOCKET;
    //*(int *)CMSG_DATA(cmsghdr0)=transed_fd;
    msghdr0.msg_control=cmsghdr0;
    msghdr0.msg_controllen=len;

    int ret;
    ret=recvmsg(pass_fd,&msghdr0,0);
    if(-1==ret)
    {
        perror("sendmsg");
        return -1;
    }
    *transed_fd=*(int *)CMSG_DATA(cmsghdr0);
    printf("transed_fd is %d\n",*transed_fd);
    return 0;
}

