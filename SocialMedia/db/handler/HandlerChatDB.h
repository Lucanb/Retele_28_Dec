//
// Created by lolluckestar on 15.12.2022.
//

#ifndef SOCIALMEDIA_HANDLERCHATDB_H
#define SOCIALMEDIA_HANDLERCHATDB_H

#include"../../models/Chat.h"
#include<iostream>
#include<string>
#include <sstream>
#include"GlobalFunction.h"

using namespace std;


struct HandlerChatDB {

    HandlerChatDB() = default;


    int CreateChat(Chat chat) {
        sqlite3 *db;
        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot open database on insert Chat: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        string strMessages;
        string strId;

        for (auto it = chat.idMessages.begin(); it != chat.idMessages.end(); it++) {
            if (it != chat.idMessages.begin()) {
                strMessages += "";
            }
            strMessages += to_string(*it);
        }

        for (auto it = chat.idList.begin(); it != chat.idList.end(); it++) {
            if (it != chat.idList.begin()) {
                strId += "";
            }
            strId += to_string(*it);
        }


        string sqlVerif = "Select idChat FROM Chat WHERE idChat = " + to_string(chat.idChat);

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error on create Chat can't say about id existance: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            return 0;
        } else {
            vector<string> s;
            parsing(returningStr, s);
            if (s.size() == 1) {
                fprintf(stderr, "This id exist in Chat: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return 0;
            } else {
                string sqlQuery = "INSERT INTO Chat (idList,idMessages,title) VALUES(" + string("\'") + strMessages
                                  + string("\'") + string(" ,") +
                                  "\'" + strId + "\' ," +
                                  "\'" + chat.title + "\')";
                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                if (rc != SQLITE_OK) {

                    fprintf(stderr, "SQL error on create Chat: %s\n", err_msg);
                    sqlite3_free(err_msg);
                    sqlite3_close(db);
                    return 0;
                } else {
                    sqlite3_close(db);
                    cout << "Chat Inserted" << '\n';
                    return 1;
                }
            }
        }
    }

    Chat getChat(int idChat) {
        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db);

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on get Chat: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            vector<int> v1, v2;
            string st = "Error";
            return Chat(-1, v1, v2, st);
        }


        string sqlVerif = "SELECT idChat FROM Chat WHERE idChat = " + to_string(idChat);

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot use existance select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            vector<int> v1, v2;
            return Chat(-2, v1, v2, "Error at selection existance");
        } else {
            vector<string> s;
            parsing(returningStr, s);
            if (s.size() == 0) {
                fprintf(stderr, "Cannot find the user: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                vector<int> v1, v2;
                return Chat(-3, v1, v2, "Error at existance");
            } else {
                string sqlQuery = "SELECT idList,idMessages,title FROM Chat WHERE idChat = " + to_string(idChat);
                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                if (rc != SQLITE_OK) {

                    fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    vector<int> v1, v2;
                    return Chat(-3, v1, v2, "Error");

                } else {
                    vector<int> v1, v2;
                    std::string idList = s[0];
                    std::string idMessages = s[1];
                    std::string title = s[2];

                    ///Start Coversion from string to vector<int> :

                    std::stringstream iss(idList);
                    std::stringstream iss2(idMessages);
                    int number;
                    while (iss >> number)
                        v1.push_back(number);

                    while (iss2 >> number)
                        v2.push_back(number);

                    cout << "Chat Getted!" << '\n';
                    return Chat(idChat, v1, v2, title);


                }

            }
        }
    }

    int updateChat(Chat chat) {
        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db);

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on update Chat: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        string sqlVerif = "SELECT idChat FROM Chat WHERE idChat = " + to_string(chat.idChat);

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot check id existance select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        } else {
            vector<string> s;
            parsing(returningStr, s);
            if (s.size() == 0) {
                fprintf(stderr, "Cannot find the id: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return 0;
            } else {

                string strMessages;
                string strId;

                for (auto it = chat.idMessages.begin(); it != chat.idMessages.end(); it++) {
                    if (it != chat.idMessages.begin()) {
                        strMessages += "";
                    }
                    strMessages += to_string(*it);
                }

                for (auto it = chat.idList.begin(); it != chat.idList.end(); it++) {
                    if (it != chat.idList.begin()) {
                        strId += "";
                    }
                    strId += to_string(*it);
                }

                string sqlQuery =
                        "UPDATE Chat SET idList =" + string("\'") + strId + string("\'") + " , idMessages = " +
                        string("\'") + strMessages + string("\'") + ", title = " + string("\'") + chat.title +
                        string("\'")
                        + " WHERE idChat = " + to_string(chat.idChat);
                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg); ///Callback
                if (rc != SQLITE_OK) {
                    fprintf(stderr, "Set comand doesn t work on Chat: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;

                } else {
                    cout << "Chat Updated!" << '\n';
                    return 1;
                }
            }
        }
    }

    int deleteChat(int idChat) {
        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); //aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on Chat : %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        string sqlVerif = "SELECT idChat FROM Chat WHERE idChat = " + to_string(idChat);

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot check id existance select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        } else {
                   vector<string>s;
                   parsing(returningStr,s);
            if (s.size() == 0) {
                fprintf(stderr, "Cannot find the id: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return 0;
            } else
            {

                string sqlQuery = "DELETE FROM Chat WHERE idChat =" + to_string(idChat);
                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                if (rc != SQLITE_OK) {
                    fprintf(stderr, "Delete comand doesn t work: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;
                } else {
                    cout << "Chat Deleted!" << '\n';
                    return 1;

                }
            }
        }
    }

};


#endif //SOCIALMEDIA_HANDLERCHATDB_H
