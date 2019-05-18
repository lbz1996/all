#include "head.h"

int verify_login(int client_fd)
{
    int first0,flag;                                                                                                                        
    char user_name[32];
    char recved_passwd[128];
    char finded_passwd[128];
    char salt[11+3];
    char passwd[16];
    int result=0;
    user_data_array user_data_array0;
    memset(&user_data_array0,0,sizeof(user_data_array));
    //先接收用户名
    bzero(user_name,sizeof(user_name));
    recv(client_fd,user_name,32,0);
    printf("user_name is %s\n",user_name);
    //发送查询结果
    //sprintf(user_name,"%s%s",user_name,"'");
    flag=mysql_find("select * from user where user_name='",user_name,"'",(void *)&user_data_array0,1);
    printf("find result is %d\n",flag);
    send(client_fd,&flag,sizeof(int),0);

    if(1==flag)
    {
        printf("user_id is %s\n",user_data_array0.user_data0[0].user_id);
        printf("user_name is %s\n",user_data_array0.user_data0[0].user_name);
        printf("salt is %s\n",user_data_array0.user_data0[0].salt);
        printf("passwd is %s\n",user_data_array0.user_data0[0].passwd);
        //如果存在,发送对应的盐值
        //bzero(salt,sizeof(salt));
        //strcpy(salt,"$6$5tw9BBJ2FU");
        send(client_fd,user_data_array0.user_data0[0].salt,sizeof(salt),0);
        //printf("salt is %s\n",salt);
        //接收加密后的密码
        bzero(recved_passwd,sizeof(recved_passwd));
        recv(client_fd,recved_passwd,sizeof(recved_passwd),0);
        printf("recved_passwd is %s\n",recved_passwd);
        //得到数据库中对应用户名的加密密码
        //strcpy(finded_passwd,"$6$5tw9BBJ2FU$VW01yc.Hh4G.H8TIBxXGzxJ6ipi3DdU1mGg3B85pb/zDYDKEHXCS2FUBUUIgOcMf9iBVSamkWCBeToJ6DFk6t/");
        //strcpy(finded_passwd,user_data_array0.user_data0[0].passwd);
        //进行判断,并发送判断结果
        result=strcmp(user_data_array0.user_data0[0].passwd,recved_passwd);
        send(client_fd,&result,1,0);
    }
    return !result; //服务端不用管是否登录成功,登录失败了客户端会一直要求登录,无法执行别的命令,不矛盾
}



char *generate_str()
{
    char str[STR_LEN+1]={0};
    int i,flag;
    srand(time(NULL));
    for(i=0;i<STR_LEN;++i)
    {
        flag=rand()%3;
        switch(flag)
        {
        case 0:
            str[i]=rand()%26+'a';
            break;
        case 1:
            str[i]=rand()%26+'A';
            break;
        case 2:
            str[i]=rand()%10+'0';
            break;
        }
    }
    printf("generate_str is %s\n",str);
    return str;//!!!!!!!!!!
}


int get_user_data(user_data_array *p_user_data_array0,MYSQL_ROW row,MYSQL_RES *res)
{
    int t,r=0;
    while((row=mysql_fetch_row(res))!=NULL)
    {
        printf("in get_user_data\n");
        //row=mysql_fetch_row(res);
        //printf("num=%d\n",mysql_num_fields(res));//列数
        //for(t=0;t<mysql_num_fields(res);t++)
        //{
        //printf("%8s ",row[t]);
        // memcpy(   (*p_user_data_array0).user_data0[r].user_id         ,row[0],sizeof(11));
        // memcpy(   (*p_user_data_array0).user_data0[r].user_name         ,row[1],sizeof(32));
        // memcpy(   (*p_user_data_array0).user_data0[r].salt   ,row[2],sizeof(128));
        // memcpy(   (*p_user_data_array0).user_data0[r].passwd ,row[3],sizeof(255));
        strcpy(   (*p_user_data_array0).user_data0[r].user_id         ,row[0]);
        strcpy(   (*p_user_data_array0).user_data0[r].user_name         ,row[1]);
        strcpy(   (*p_user_data_array0).user_data0[r].salt   ,row[2]);
        strcpy(   (*p_user_data_array0).user_data0[r].passwd ,row[3]);
        //}    
        //printf("\n");
        ++r;
    }
    return mysql_num_rows(res);
}
