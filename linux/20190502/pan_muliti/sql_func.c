#include "head.h"


int mysql_find(char *s1,char *s2,char *s3,void *save,int which)
{//-1表示查询失败,0表示查询无结果,1表示查询有结果
    int flag;
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char* server="localhost";
    char* user="lbz";
    char* password="123";
    char* database="pan";//要访问的数据库名称
    char query[300];//="select * from user where user_name='";
    //sprintf(query,"%s%s%s",s1,s2,"'");
    sprintf(query,"%s%s%s",s1,s2,s3);
    //strcpy(query,"select * from Person");
    puts(query);
    int t,r;
    conn=mysql_init(NULL);
    if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
    {
        printf("Error connecting to database:%s\n",mysql_error(conn));
        return -1;
    }
    else
    {
        printf("Connected...\n");
    }

    t=mysql_query(conn,query);
    if(t)
    {
        printf("Error making query:%s\n",mysql_error(conn));
        flag=-1;
    }
    else
    {
        res=mysql_use_result(conn);
        if(NULL!=res)//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        {
            printf("in\n");
            
            if(1==which)
                if(0==get_user_data((user_data_array *)save,row,res))
                {
                    flag=0;
                    goto lable_sql_find; 
                }
            printf("debug array is %p\n",save);
            if(2==which)
                if(0==get_file_data((file_data_array *)save,row,res))
                {
                    printf("in mysql_find %d\n ",__LINE__);
                    flag=0;
                    goto lable_sql_find; 
                }
            flag=1;
        }
        else
        {
            printf("Don't find data\n");
            flag=0;
        }
lable_sql_find:
        mysql_free_result(res);
    }
    mysql_close(conn);
    return flag;
}


int mysql_insert(char *s1,char *s2)
{//失败返回0,成功返回1
 //其实好像可以和上面弄成一个....
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char* server="localhost";
    char* user="lbz";
    char* password="123";
    char* database="pan";//要访问的数据库名称
    char query[300];//="select * from user where user_name='";
    sprintf(query,"%s%s",s1,s2);
    //strcpy(query,"select * from Person");
    puts(query);
    int t,flag;
    conn=mysql_init(NULL);
    if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
    {
        printf("Error connecting to database:%s\n",mysql_error(conn));
        return 0;//这样失败还用链接conn嘛...
    }
    else
    {
        printf("Connected...\n");
    }

    t=mysql_query(conn,query);
    if(t)
    {
        printf("Error making query:%s\n",mysql_error(conn));
        flag=0;
    }
    else
    {
        printf("insert success\n");
        flag=1;
    }
    mysql_close(conn);
    return flag;
}

