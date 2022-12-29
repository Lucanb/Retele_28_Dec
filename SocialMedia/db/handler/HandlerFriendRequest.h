//
// Created by lolluckestar on 15.12.2022.
//

#ifndef SOCIALMEDIA_HANDLERFRIENDREQUEST_H
#define SOCIALMEDIA_HANDLERFRIENDREQUEST_H

#include "../../models/FriendRequest.h"
#include<iostream>
#include<string>
#include"GlobalFunction.h"

using namespace std;

struct HandlerFriendRequestDB {

    HandlerFriendRequestDB() = default;

    int createFriendRequest(
            FriendRequest friendRequest
    ) {
        sqlite3 *db;
        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot open database on insert friendRequest: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        string sqlVerif = "SELECT id1,id2 FROM FriendRequest WHERE id1=" + to_string(friendRequest.id1) + " AND id2=" +
                          to_string(friendRequest.id2);

        string sqlQuery = "INSERT INTO FriendRequest (id2,accepted,type) VALUES(" + to_string(friendRequest.id2) + "," +
                          "\'" + to_string(friendRequest.accepted) + "\'," +
                          "\'" + friendRequest.type + "\')";

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "We can't say anything about the existence: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            return 0;
        } else {
            vector<string> s;
            parsing(returningStr, s);
            if (s.size() != 0) {
                fprintf(stderr, "This friendship exists: %s\n", err_msg);
                sqlite3_free(err_msg);
                sqlite3_close(db);
                return 0;
            } else {
                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                if (rc != SQLITE_OK) {

                    fprintf(stderr, "SQL error on create friendRequest: %s\n", err_msg);
                    sqlite3_free(err_msg);
                    sqlite3_close(db);
                    return 0;
                } else {
                    sqlite3_close(db);
                    cout << "FriendRequest Inserted" << '\n';
                    return 1;
                }
            }
        }
    }

    FriendRequest getFriendRequest(int id1, int id2) {

        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db);

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on get FriendRequest: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return FriendRequest(-1, -1, "Error Open Data Base", false);
        }


        string sqlVerif =
                "SELECT id1,id2 FROM FriendRequest WHERE id1 = " + to_string(id1) + " AND id2 = " + to_string(id2);

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot use existance select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return FriendRequest(-2, -2, "Error at SELECT EXISTANCE", false);
        } else {
            vector<string> s;
            parsing(returningStr, s);
            if (s.size() == 0) {
                fprintf(stderr, "Cannot find the user: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return FriendRequest(-3, -3, "Error User Doesn't Exists", false);
            } else {

                string sqlQuery = "SELECT accepted,type FROM FriendRequest WHERE id1 = " + to_string(id1) +
                                  " AND id2 = " + to_string(id2);
                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                if (rc != SQLITE_OK) {

                    fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return FriendRequest(-5, -5, "Error using select", false);

                } else {
                    vector<string> s;
                    parsing(returningStr, s);
                    string type = s[0];
                    bool accepted;
                    if (s[1] == "0") {
                        accepted = 0;
                    } else {
                        accepted = 1;
                    }
                    cout << "FriendRequest Getted!" << '\n';
                    return FriendRequest(id1, id2, type, accepted);
                }
            }
        }
    }

    int updateFriendRequest(FriendRequest friendRequest) {
        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); //aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on update FriendRequest: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        string sqlVerif =
                "SELECT id1,id2 FROM FriendRequest WHERE id1 = " + to_string(friendRequest.id1) +
                " AND id2 = " + to_string(friendRequest.id2);

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

                string sqlVerif = "UPDATE FriendRequest SET accepted = " + string("\'") +
                                  to_string(friendRequest.accepted) + string("\'") + " , type = " + string("\'") +
                                  friendRequest.type + string("\'") + "WHERE id1 = " + to_string(friendRequest.id1) +
                                  " AND id2 =" + to_string(friendRequest.id2);
                rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);
                if (rc != SQLITE_OK) {
                    fprintf(stderr, "Set comand doesn t work on friendRequest: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;

                } else {
                    cout << "FriendRequest Updated" << '\n';
                    return 1;
                }
            }
        }
    }

    int deleteFriendRequest(int id1, int id2) {

        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); //aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on delete message: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        string sqlVerif =
                "SELECT id1,id2 FROM FriendRequest WHERE id1 = " + to_string(id1) + " AND id2 =" + to_string(id2);

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot check id existance select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        } else {
            vector<string> s;
            parsing(returningStr,s);

            if (s.size() == 0) {
                fprintf(stderr, "Cannot find the id: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return 0;
            } else
            {

                string sqlQuery = "DELETE FROM FriendRequest WHERE id1 = " + to_string(id1) + " AND id2 = "
                        + to_string(id2);
                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                if (rc != SQLITE_OK) {
                    fprintf(stderr, "Delete comand doesn t work: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;

                } else {
                    cout << "FriendRequest deleted" << '\n';
                    return 1;

                }
            }
        }
    }
};

#endif //SOCIALMEDIA_HANDLERFRIENDREQUEST_H
