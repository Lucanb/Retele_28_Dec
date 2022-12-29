//
// Created by lolluckestar on 15.12.2022.
//

#ifndef SOCIALMEDIA_HANDLERMESSAGEDB_H
#define SOCIALMEDIA_HANDLERMESSAGEDB_H

#include "../../models/Message.h"
#include<iostream>
#include<string>
#include"GlobalFunction.h"

using namespace std;

struct HandlerMessageDB {

    HandlerMessageDB() = default;

    int createMessage(
            Message message
    ) {
        sqlite3 *db;
        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot open database on insert message: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        string sqlVerif = "Select id from Message WHERE id=" + to_string(message.id);

        string sqlQuery = "INSERT INTO Message (chatId,date,message) VALUES(" + to_string(message.chatId) + "," +
                          "\'" + message.date + "\'," +
                          "\'" + message.message + "\')";
        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Can't verify if the id exists on message: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            return 0;
        } else {
            vector<string> s;
            parsing(returningStr, s);
            if (s.size() != 0) {
                fprintf(stderr, "This Message doesn't Creeate because the id exists: %s\n", err_msg);
                sqlite3_free(err_msg);
                sqlite3_close(db);
                return 0;
            } else {
                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                if (rc != SQLITE_OK) {

                    fprintf(stderr, "SQL error on create message: %s\n", err_msg);
                    sqlite3_free(err_msg);
                    sqlite3_close(db);
                    return 0;
                } else {
                    sqlite3_close(db);
                    cout << "Message Inserted" << '\n';
                    return 1;
                }
            }
        }
    }

    Message getMessage(int id, int chatId) {

        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); //aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on get Message: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return Message(-1, -1, "Error Open Data Base", "Error");
        }


        string sqlVerif =
                "SELECT id,chatId FROM Message WHERE id =" + to_string(id) + " AND chatId =" + to_string(chatId);

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);


        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot use existance select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return Message(-2, -2, "Error at SELECT EXISTANCE", "Error");
        } else {
            vector<string> s;
            parsing(returningStr, s);
            if (s.size() == 0) {
                fprintf(stderr, "Cannot find the user: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return Message(-3, -3, "Error User Doesn't Exists", "Error");
            } else {

                string sqlQuery = "SELECT date,message FROM Message WHERE id =" + to_string(id) + " AND chatId =" +
                                  to_string(chatId);
                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                if (rc != SQLITE_OK) {

                    fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return Message(-5, -5, "Error using select", "Error");

                } else {
                    vector<string> s;
                    parsing(returningStr, s);

                    std::string date = s[0];
                    std::string message = s[1];

                    cout << "Message Getted!" << '\n';
                    return Message(id, chatId, date, message);
                }
            }
        }
    }

    int updateMessage(Message message) {
        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db);

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on update Message: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }


        string sqlVerif = "SELECT id,chatId FROM Message WHERE id =" + to_string(message.id) + " AND chatId = " +
                          to_string(message.chatId); //

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

                string sqlQuery = "UPDATE Message SET date = " + string("\'") + message.date + string("\'") +
                                  " , message = " + string("\'") + message.message + string("\'") + "WHERE id = "
                                  + to_string(message.id) + " AND chatId= " + to_string(message.chatId);
                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                if (rc != SQLITE_OK) {
                    fprintf(stderr, "Set comand doesn t work on message: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;

                } else {
                    cout << "Message Updated" << '\n';
                    return 1;
                }
            }
        }
    }

    int deleteMessage(int id, int chatId) {
        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db);

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on delete message: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        string sqlVerif =
                "SELECT id,chatId FROM Message WHERE id =" + to_string(id) + " AND chatId =" + to_string(chatId);

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

                string sqlQuery =
                        "DELETE FROM Message WHERE id = " + to_string(id) + " AND chatId = " + to_string(chatId);
                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                if (rc != SQLITE_OK) {
                    fprintf(stderr, "Delete comand doesn t work: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;

                } else {
                    cout << "Message deleted" << '\n';
                    return 1;

                }
            }
        }
    }

};

#endif //SOCIALMEDIA_HANDLERMESSAGEDB_H
