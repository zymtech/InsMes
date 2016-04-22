#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>

static sqlite3 *db;

/*
    col_name--->----"id"------
                ----"name"----
                ----"passwd"--
*/

int callback(void *data, int col, char**col_value, char**col_name)
{
    static int flag = 0;
    int i = 0;

    if (flag == 0) {    
        for (i = 0; i < col; i++) {
            printf("%s\t", col_name[i]);
        }
        printf("\n");
        flag = 1;
    }

    for (i = 0; i < col; i++) {
        printf("%s\t", col_value[i]);
    }
    printf("\n");

    return 0;
}

int main(void)
{
    int ret;

    ret = sqlite3_open("./test.sqlite", &db); 
    if (ret != SQLITE_OK) {
        fprintf(stderr, "sqlite3_open error\n");
        exit(1);
    }

    char *sql = "create table if not exists userTable(id integer not null primary key autoincrement, name text not null, passwd text not null)";
    char *err;
    ret = sqlite3_exec(db, sql, NULL, NULL, &err);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "create table error resion:%s\n", err);
        sqlite3_close(db);
        exit(1);
    }

    char *insert_sql = "insert into userTable(name, passwd) values('zhangsan', '112233')";
    ret = sqlite3_exec(db, insert_sql, NULL, NULL, &err);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "insert error resion:%s\n", err);
        sqlite3_close(db);
        exit(1);
    }

    char *query_sql = "select * from userTable";
    ret = sqlite3_exec(db, query_sql, callback, NULL, &err);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "select error resion:%s\n", err);
        sqlite3_close(db);
        exit(1);
    }

    sqlite3_close(db);

    return 0;
}




