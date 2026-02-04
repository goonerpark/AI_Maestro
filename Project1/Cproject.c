#include <stdio.h>
#include <mysql.h>

int main()
{
    MYSQL* conn;
    MYSQL* conn_result;
    unsigned int timeout_sec = 1;

    conn = mysql_init(NULL);
    mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout_sec);
    conn_result = mysql_real_connect(conn, "127.0.0.1", "root", "0909", "storefamily", 3307, NULL, 0);

    if (NULL == conn_result)
    {
        printf("DB Connection Fail\n");
    }
    else
    {
        printf("DB Connection Success\n");

        char query[1024];
        MYSQL_RES* result;
        MYSQL_ROW row;

        snprintf(query, 1024, "SELECT bno FROM fill");

        if (mysql_query(conn, query))
        {
            printf("SELECT Fail\n");
        }
        result = mysql_store_result(conn);

        int fields = mysql_num_fields(result);

        while ((row = mysql_fetch_row(result)) != NULL)
        {
            for (int i = 0; i < fields; i++)
            {
                printf("%s   ", row[i]);
            }
            printf("\n");
        }

        mysql_free_result(result);
        mysql_close(conn);
    }

    return 0;
}
