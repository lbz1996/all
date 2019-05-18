#include "head.h"
#include "sql_func.c"
#include "user_func.c"
#include "file_func.c"
int main(int argc,char **argv)
{
    int ret;
    char buf[128];
    bzero(buf,sizeof(buf));
    //链接服务端
    printf("Hello world\n");
    if(2!=argc)
    {
        printf("wrong input\n");
        return -1;
    }
    int socket_fd=socket(AF_INET,SOCK_STREAM,0);
    FUNC_ERROR(socket_fd,-1,"socket"); 
    struct sockaddr_in sockaddr_in_0;
    bzero(&sockaddr_in_0,sizeof(struct sockaddr_in));
    sockaddr_in_0.sin_port=htons((short) 1234);
    sockaddr_in_0.sin_family=AF_INET;
    sockaddr_in_0.sin_addr.s_addr=inet_addr(argv[1]);
    ret=connect(socket_fd,(struct sockaddr*)&sockaddr_in_0,sizeof(sockaddr_in_0));
    FUNC_ERROR(ret,-1,"connect");
    //测试收发
    ret=recv(socket_fd,buf,5,0);
    printf("recv_ret is %d\n",ret);
    printf("%s\n",buf);
    printf("\n\n\n");
    //先登录
    //测试不断尝试登录
    //char user_name[32]="lbz";
    char user_name[32];
    bzero(user_name,32);

    while(1)
        if(1==client_login(socket_fd,user_name))
            break;
    
    printf("debug: user_name is %s\n",user_name);
    //测试不断接收命令并发送
    char pwd[4096];
    memset(pwd,0,sizeof(pwd));
    sprintf(pwd,"%s/",user_name);
    printf("pwd is %s\n",pwd);
    int dir_id=0;

    int command_code=16;
    int command_result=0;
    int command_count;
    char command1[4096];
    char command2[4096];

        //bzero(buf,128);
        //gets(buf);//scanf("%s",buf);
        //getchar();
        //读取命令
        bzero(command1,4096);
        bzero(command2,4096);
        command_count=scanf("%s %s",command1,command2);  printf("command1 is %s\n command2 is %s\n",command1,command2);
        //先识别命令,(不考虑参数合法才)发送命令码
        command_code=1;
        send(socket_fd,&command_code,sizeof(int),0);
        //获得参数
        //发送命令?还是就参数?
        send(socket_fd,buf,128,0);
        //对接执行命令
            //client_upload_file(socket_fd,"/home/lbz/20190502/pan_save_file/test_file","test_file","lbz",0);
            //client_ls(socket_fd,dir_id,user_name);
            //client_cd(socket_fd,&dir_id,user_name,command2);
            //client_download_file(socket_fd,command2,user_name,dir_id);
            //client_pwd(socket_fd,user_name,dir_id);
            //client_mkdir(socket_fd,command2,user_name,dir_id);
            client_remove(socket_fd,command2,user_name,dir_id);
        //接收命令结果
        recv(socket_fd,&command_result,sizeof(int),0);
        printf("command_result is %d\n",command_result);
        if(1==command_result)
            printf("执行命令成功\n");
        else
        {
            printf("执行命令失败\n");
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
        printf("flag is %d\n",flag);
        if(1==flag)
        {
            //如果存在,再接收用户名对应的盐值
            bzero(salt,11+3);
            recv(socket_fd,salt,11+3,0);
            printf("salt is %s\n",salt);
            //从标准输入接收密码
            bzero(passwd,16);
            printf("input passwd\n");
            scanf("%s",passwd);
            printf("passwd is %s\n",passwd);
            //进行加密,然后发送给服务端
            printf("%s",crypt(passwd,salt));
            send(socket_fd,crypt(passwd,salt),128,0);         
            //接收判断结果
            recv(socket_fd,&result,sizeof(int),0);//我在里面改了判断条件没事么?....
            printf("\nresult is %d\n",result);
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








