#include "head.h"
#include "sql_func.c"
#include "user_func.c"
#include "file_func.c"
#include "pthread_func.c"
int main(int argc,char **argv)
{
    int ret;
    //链接服务端
    //printf("Hello world\n");                               if(2!=argc) { printf("wrong input\n"); return -1; }
    int socket_fd=socket(AF_INET,SOCK_STREAM,0);           FUNC_ERROR(socket_fd,-1,"socket"); 
    //printf("socket_fd is %d\n",socket_fd);
    struct sockaddr_in sockaddr_in_0;                      bzero(&sockaddr_in_0,sizeof(struct sockaddr_in));
    sockaddr_in_0.sin_port=htons((short) 1234);
    sockaddr_in_0.sin_family=AF_INET;
    sockaddr_in_0.sin_addr.s_addr=inet_addr(argv[1]);
    ret=connect(socket_fd,(struct sockaddr*)&sockaddr_in_0,sizeof(sockaddr_in_0));    FUNC_ERROR(ret,-1,"connect");
    int reuse=1;                                                                                                                                
    ret=setsockopt(socket_fd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int)); FUNC_ERROR(socket_fd,-1,"setsockopt");
    int is_main=1;
    send(socket_fd,&is_main,sizeof(int),0);
    qnode qnode0;    memset(&qnode0,0,sizeof(qnode));
    ////测试收发
    //ret=recv(socket_fd,buf,5,0);
    //printf("recv_ret is %d\n",ret);
    //printf("%s\n",buf);
    //printf("\n\n\n");

    //先登录
    //测试不断尝试登录
    //char user_name[32]="lbz";
    char user_name[32];     bzero(user_name,32);
    qnode0.command_code=1;
    while(1)
    {
        send(socket_fd,&qnode0,sizeof(qnode),0);
        if(1==client_login(socket_fd,user_name))
            break;
    }

    //登录成功了就建立个新的socket_fd
    int socket_fd2=socket(AF_INET,SOCK_STREAM,0);           FUNC_ERROR(socket_fd,-1,"socket"); 
    //printf("socket_fd2 is %d\n",socket_fd2);
    struct sockaddr_in sockaddr_in_2;                      bzero(&sockaddr_in_0,sizeof(struct sockaddr_in));
    sockaddr_in_2.sin_port=htons((short) 1234);
    sockaddr_in_2.sin_family=AF_INET;
    sockaddr_in_2.sin_addr.s_addr=inet_addr(argv[1]);
    ret=connect(socket_fd2,(struct sockaddr*)&sockaddr_in_2,sizeof(sockaddr_in_2));    FUNC_ERROR(ret,-1,"connect");
    is_main=0;
    send(socket_fd2,&is_main,sizeof(int),0);

    //建立子线程
    transed transed0;                                                                                                                           
    pthread_mutex_t lock;
    ret=pthread_mutex_init(&lock, NULL);         if(0!=ret){printf("pthread_mutex_init is wrong\n");return -1;}
    transed0.p_lock=&lock;
    pthread_cond_t cond;
    pthread_cond_init(&cond, NULL);
    transed0.p_cond=&cond;


    //建立多线程
    queue_stat queue_stat_0;                      memset(&queue_stat_0,0,sizeof(queue_stat));
    transed0.p_queue_stat_0=&queue_stat_0;
    pthread_t pthread_id_array[MAX_PTHREAD_NUM];  memset(&pthread_id_array,0,sizeof(pthread_id_array));
    transed0.flag=2;
    transed0.socket_fd2=socket_fd2;
    //ret=pthread_create(&pthread_id,NULL,pthread_func_execute,(void *) &transed0);                    if(0!=ret){printf("pthread_create wrong\n");return -1;}
    //for(int i=0;i<MAX_PTHREAD_NUM;++i)
    //{
    pthread_t pthread_id;
    ret=pthread_create(&pthread_id,NULL,pthread_func_execute,(void *) &transed0);                if(0!=ret){printf("pthread_create wrong\n");return -1;}
    //}

    //printf("debug: user_name is %s\n",user_name);
    //char pwd[4096];         memset(pwd,0,sizeof(pwd));sprintf(pwd,"%s/",user_name);//printf("pwd is %s\n",pwd);
    int dir_id=0;
    char command[4096];
    //printf("开始不断接收命令\n");
    char c=getchar();//printf("debug46:before1 is %d\n",c);//c=getchar();printf("debug47:before1 is %d\n",c);

    while(1)
    {
        //读取命令
        bzero(command,4096);
        if(NULL==fgets(command,4096,stdin))
            continue;//scanf("%s",command);//getchar();
        //printf("\ncommand is %s",command);//所以有回车....
        which_command_ok(socket_fd,user_name,&dir_id,command,transed0);
    }
    return 0;
}

int which_command_ok(int socket_fd,char *user_name,int *dir_id,char *command,transed transed0)
{
    char command1[8],command2[4096-8];                             bzero(command1,8);bzero(command2,4096-8);
    int command_len=strlen(command);
    int j=0,i=0;
    for(;i<command_len;++i)
    {
        if(command[i]!='\n'&&command[i]!=' '&&j<8)
            command1[j++]=command[i];
        else
            break;
    }
    j=0;i+=1;
    for(;i<command_len;++i)
    {
        if(command[i]!='\n'&&j<4096-8)
            command2[j++]=command[i];
        else
            break;
    }
    //printf("command1 is %s,command2 is b|||%s\n",command1,command2);
    //先识别命令,(不考虑参数合法才)发送命令码
    int command_code;
    int command_result;
    if(0==strcmp(command1,"cd"))
    {
        command_code=2;
    }
    else if(0==strcmp(command1,"ls"))
    {
        command_code=3;
    }
    else if(0==strcmp(command1,"puts"))
    {
        command_code=4;
    }
    else if(0==strcmp(command1,"gets"))
    {
        command_code=5;
    }
    else if(0==strcmp(command1,"remove"))
    {
        command_code=6;
    }
    else if(0==strcmp(command1,"pwd"))
    {
        command_code=7;
    }
    else if(0==strcmp(command1,"mkdir"))
    {
        command_code=8;
    }
    else
    {
        printf("line%d:错误/不支持的命令\n",__LINE__);
        return 0;
    }   
    qnode qnode0;                                          memset(&qnode0,0,sizeof(qnode));
    qnode0.command_code=command_code;
    strcpy(qnode0.command,command2);
    strcpy(qnode0.user,user_name);
    qnode0.dir_id=*dir_id;
    //qnode0.fd=socket_fd;
    //发送命令
    if(4!=command_code&&5!=command_code)
    {
        send(socket_fd,&qnode0,sizeof(qnode),0);//!!!记得函数里面要发送命令好对接....//(好像还得弄个新的socket?)
        //对接执行命令
        switch (command_code)
        {
        case 2: client_cd(socket_fd,dir_id,user_name,command2);break;
        case 3: client_ls(socket_fd,*dir_id,user_name);break;
                //case 4: client_upload_file(socket_fd,command2,basename(command2),user_name,*dir_id);break;
                //case 4: client_upload_file(socket_fd,command2,command2,user_name,*dir_id);break;
                //case 5: client_download_file(socket_fd,command2,user_name,*dir_id);break;
        case 6: client_remove(socket_fd,command2,user_name,*dir_id);break;
        case 7: client_pwd(socket_fd,user_name,*dir_id);break;
        case 8: client_mkdir(socket_fd,command2,user_name,*dir_id);break;
        }
    }
    else
    {
        p_qnode p_qnode0=(p_qnode) calloc(1,sizeof(qnode));
        memcpy(p_qnode0,&qnode0,sizeof(qnode));
        pthread_mutex_lock(transed0.p_lock);
        queue_insert(p_qnode0,transed0.p_queue_stat_0);
        pthread_mutex_unlock(transed0.p_lock);
        pthread_cond_signal(transed0.p_cond);
    }
    return 0;
}






//用户登录
int client_login(int socket_fd,char *user_name_tosave)
{//0失败,1成功
    //注册登录
    int first0,flag,result=0;
    char user_name[32];
    char crypted_passwd[128];
    char salt[11+3];
    char passwd[16];
    //system("CLS");
    //printf("1.注册\n2.登录\n");
    //scanf("%d",&first0);
    //if(1==first0)
    //{
    //    printf("开始注册\n");
    //    bzero(user_name,32);
    //    printf("input user_name\n");
    //    scanf("%s",user_name);
    //    printf("%s\n",user_name);
    //    send(socket_fd,user_name,32,0);
    //    printf("input passwd\n");
    //    return 0;
    //}
    //else if(2==first0)
    //{
    printf("开始登录\n");
    //发送用户名
    bzero(user_name,32);
    printf("input user_name\n");
    scanf("%s",user_name);
    //printf("%s\n",user_name);
    send(socket_fd,user_name,32,0);
    //接收查询结果
    recv(socket_fd,&flag,sizeof(int),0);
    //printf("flag is %d\n",flag);
    if(1==flag)
    {
        //如果存在,再接收用户名对应的盐值
        bzero(salt,11+3);
        recv(socket_fd,salt,11+3,0);
        //printf("salt is %s\n",salt);
        //从标准输入接收密码
        bzero(passwd,16);
        printf("input passwd\n");
        scanf("%s",passwd);
        //printf("passwd is %s\n",passwd);
        //进行加密,然后发送给服务端
        //printf("%s",crypt(passwd,salt));
        send(socket_fd,crypt(passwd,salt),128,0);         
        //接收判断结果
        recv(socket_fd,&result,sizeof(int),0);//我在里面改了判断条件没事么?....
        //printf("\nresult is %d\n",result);
        if(0==result)
        {
            printf("登录成功\n");
            bzero(user_name_tosave,32);
            strcpy(user_name_tosave,user_name);
            return 1;
        }
        else
        {
            printf("用户名和密码不匹配\n");
            return 0;
        }
    }
    else
    {
        printf("用户不存在\n");
        return 0;
    }
    //}
    //else
    //{
    //    printf("wrong input\n");
    //    return 0;
    //}
}

