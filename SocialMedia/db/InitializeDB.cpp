//
// Created by lolluckestar on 11.12.2022.
//
//
// Created by lolluckestar on 11.12.2022.
//
#include<iostream>
#include<string>
#include<stdio.h>
#include "dbRequest.h"
#include "mydb/sqlite3.h"

using namespace std;

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

int formTable(const char *sqlQuery, const char *tableName) {
    char *err = nullptr;

    int open = sqlite3_open("mydb.db", &db);
    int execute = sqlite3_exec(db, sqlQuery, 0, 0, &err);

    if (open != SQLITE_OK) {
        cout << "Cannot open the data base";
        sqlite3_close(db);
        return 0;
    }
    if (execute != SQLITE_OK) {
        cout << "Cannot create " << tableName << " table";
        return 0;
    }
    int close = sqlite3_close(db);

    if (close != SQLITE_OK) {
        cout << "Cannot close db!";
        return 0;
    }
    return 1;
}


int createTables() {
    int sw;
    sw = formTable(
            "CREATE TABLE IF NOT EXISTS Users(id INTEGER PRIMARY KEY, isAdmin INTEGER,userName TEXT,firstname TEXT,lastname TEXT,birthday TEXT,accountCreationDate TEXT,profileDescription TEXT);",
            "Users"
    );
    if (!sw) {
        cout << "Users Error";
        return 0;
    }

    sw = formTable(
            "CREATE TABLE IF NOT EXISTS Friend(id1 INTEGER PRIMARY KEY, id2 INTEGER ,type TEXT);",
            "Friend"                                  //aici vezi cheile.
    );
    if (!sw) {
        cout << "Friend Error";
        return 0;
    }
    sw = formTable(
            "CREATE TABLE IF NOT EXISTS Chat(idChat INTEGER PRIMARY KEY,idList TEXT,idMessages TEXT,title TEXT);",
            "Chat"
    );
    if (!sw) {
        cout << "Chat Error";
        return 0;
    }
    sw = formTable(
            "CREATE TABLE IF NOT EXISTS FriendRequest(id1 INTEGER PRIMARY KEY, id2 INTEGER,type TEXT,accepted INTEGER);",
            "FriendRequest"
    );
    if (!sw) {
        cout << "FriendRequest Error";
        return 0;
    }
    sw = formTable(
            "CREATE TABLE IF NOT EXISTS Message(id INTEGER PRIMARY KEY, chatId INTEGER,date TEXT,message TEXT);",
            "Message"
    );
    if (!sw) {
        cout << "Message Error";
        return 0;
    }

    sw = formTable(
            "CREATE TABLE IF NOT EXISTS News(id INTEGER PRIMARY KEY, authorId INTEGER,title TEXT,content TEXT,type TEXT);",
            "News"
    );
    if (!sw) {
        cout << "News Error";
        return 0;
    }
    return 1;
}
/*
int Interogate()
{
    char *err=nullptr;
    const char *test="INSERT INTO Users VALUES(0,0,'abc','def','efg','hij','asd','fdg')";
    int vfComand=sqlite3_exec(db, test, 0, 0, &err);
    if(vfComand != SQLITE_OK)
    {
        cout<<"Cannot insert in table";
        return 0;
    }
    return 1;
}
*/
/*
int getUser()
{
    char *err=nullptr;
    const char *test="SELECT * FROM Users";
    int vfComand=sqlite3_exec(db, test, callback, 0, &err);
    if(vfComand != SQLITE_OK)
    {
        cout<<"Cannot select in table";
        return 0;
    }
    return 1;
}

*/

int main() {
    createTables();

    //   Interogate();
//    getUser();
    cout << "DB INITIALIZED\n";
}
