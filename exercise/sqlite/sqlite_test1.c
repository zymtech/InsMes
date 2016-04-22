#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>

static sqlite3 *db;

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

    /*
    result--->---id------- 
              ---name----- 
              ---passwd--- 
              ---1--------
              ---zhangsan- 
              ---112233--- 
              ---2-------- 
              ---lisi-----
              ---112233---
    */
    char *query_sql = "select * from userTable";
    char **result;
    int col, row;
    ret = sqlite3_get_table(db, query_sql, &result, &row, &col, &err);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "get_table error resion:%s\n", err);
        sqlite3_close(db);
        exit(1);
    }
    
    int i;
    for (i = 0; i < col; i++) {
        printf("%s\t", result[i]);
    }
    printf("\n");
    for (i = col; i < col * row + col; i++) {
        if (i % col == 0) {
            printf("\n");
        } 
        printf("%s\t", result[i]);
    }
    printf("\n");

    sqlite3_free_table(result);

    sqlite3_close(db);

    return 0;
}




