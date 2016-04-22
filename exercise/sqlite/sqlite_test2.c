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

    char *sql = "create table if not exists passwdTable(id integer not null, passwd text)";
    sqlite3_stmt *stmt;
    ret = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "perpare error\n");
        sqlite3_close(db);
        exit(1);
    } else {
        ret = sqlite3_step(stmt);
        if (ret != SQLITE_DONE) {
            fprintf(stderr, "step error\n");
            sqlite3_close(db);
            exit(1);
        }
    }

    char *insert_sql = "insert into passwdTable(id, passwd) values(?, ?)";
    ret = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, NULL);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "prepare error\n");
        sqlite3_close(db);
        exit(1);
    } else {
        sqlite3_bind_int(stmt, 1, 0);
        sqlite3_bind_text(stmt, 2, "'123456'", -1, NULL);
        ret = sqlite3_step(stmt);
        if (ret != SQLITE_DONE) {
            fprintf(stderr, "step error\n");
            sqlite3_close(db);
            exit(1);
        } 
    }

    char *query_sql = "select * from passwdTable where id=?";
    ret = sqlite3_prepare_v2(db, query_sql, -1, &stmt, NULL);
    int id;
    const unsigned char *passwd;
    if (ret != SQLITE_OK) {
        fprintf(stderr, "prepare error\n");
        sqlite3_close(db);
        exit(1);
    } else {
        sqlite3_bind_int(stmt, 1, 0);
        while (1) {
            ret = sqlite3_step(stmt);
            if (ret != SQLITE_DONE && ret != SQLITE_ROW) {
                fprintf(stderr, "step error\n");
                continue;
            } else if (ret == SQLITE_DONE) {
                break;
            } else if (ret == SQLITE_ROW) {
                id = sqlite3_column_int(stmt, 0);
                passwd = sqlite3_column_text(stmt, 1); 
                printf("%d\t%s\n", id, passwd);
            }
        }
    }

    sqlite3_finalize(stmt);

    sqlite3_close(db);

    return 0;
}




