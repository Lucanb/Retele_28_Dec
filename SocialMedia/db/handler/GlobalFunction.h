//
// Created by lolluckestar on 25.12.2022.
//

#ifndef SOCIALMEDIA_GLOBALFUNCTION_H
#define SOCIALMEDIA_GLOBALFUNCTION_H

#endif //SOCIALMEDIA_GLOBALFUNCTION_H
#include<iostream>
#include<string>
#include"../../db/mydb/sqlite3.h"

sqlite3 *db;
sqlite3_stmt *stmt;

static int callback(void *data, int argc, char **argv, char **azColName) {
    int i;
    fprintf(stderr, "%s: ", (const char *) data);

    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}