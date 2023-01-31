//
// Created by lolluckestar on 07.01.2023.
//
#pragma once
#ifndef SOCIALMEDIA_HANDLERPASSWORDSDB_H
#define SOCIALMEDIA_HANDLERPASSWORDSDB_H

#include "GlobalFunction.h"
#include "../../models/Passwords.h"
#include "../../db/mydb/sqlite3.h"
#include <iostream>
#include <string>
#include <vector>
/*
 * int id;
    std::string userName;
    std::string password;
*/
using namespace std;

struct HandlerPasswordsDB {

    HandlerPasswordsDB() = default;

    int createPassword(
            struct Passwords passwords) {

        sqlite3 *db;
        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("db/mydb.db", &db);

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on insert password: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);

            return 0;
        }

        string sqlVerif;
        sqlVerif =
                "SELECT userName FROM Passwords WHERE userName=" +
                string("\'") + passwords.userName + string("\'");
        string sqlQuery =
                "INSERT INTO Passwords (userName,password) VALUES(" +
                std::string("\'") + passwords.userName + std::string("\'") + "," +
                "\'" + passwords.password + "\')";

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "Select doesn't work %s\n", err_msg);
            return 0;
        } else {

            vector<string> s;
            parsing(returningStr, s);
            // cout<<s.size();
            if (int(s.size()) == 0) { // daca ==1 inseamna ca a gasit un user deci exista deja.

                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                if (rc != SQLITE_OK) {

                    fprintf(stderr, "SQL error on insert user: %s\n", err_msg);
                    sqlite3_free(err_msg);
                    sqlite3_close(db);
                    return 0;
                } else {
                    cout << "Passwords Created!" << '\n';
                    return 1;
                }
            } else {
                fprintf(stderr, "SQL error on password user already exists: %s\n");
                sqlite3_close(db);
                return 0;
            }
        }
    }


    Passwords getPasswordId(int id) {

        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("db/mydb.db", &db);

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on get password: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return Passwords(-1, "Error Open Data Base", "Error");
        }

        string sqlVerif =
                "SELECT id FROM Passwords WHERE id=" + to_string(id); ///Careful

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot use existance select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return Passwords(-2, "Error Open Data Base", "Error");
        } else {
            vector<string> s;
            parsing(returningStr, s);
            if (s.size() == 0) {
                fprintf(stderr, "Cannot find the user for password: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return Passwords(-3, "Error Open Data Base", "Error");
            } else {

                string sqlQuery =
                        "SELECT userName,password FROM Passwords WHERE id=" + to_string(id);

                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                if (rc != SQLITE_OK) {
                    fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return Passwords(-4, "Error Open Data Base", "Error");
                } else {
                    vector<string> s;
                    parsing(returningStr, s);
                    std::string userName = s[0];
                    std::string password = s[1];

                    cout << "User Getted!" << '\n';
                    return Passwords(id, userName, password);
                }
            }
        }
    }


    Passwords getPassword(string userName) {

        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("db/mydb.db", &db);

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on get password: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return Passwords(-1, "Error Open Data Base", "Error");
        }

        string sqlVerif =
                "SELECT userName FROM Passwords WHERE userName=" + string("\'") + userName + string("\'"); ///Careful

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot use existance select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return Passwords(-2, "Error Open Data Base", "Error");
        } else {
            vector<string> s;
            parsing(returningStr, s);
            if (s.size() == 0) {
                fprintf(stderr, "Cannot find the user for password: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return Passwords(-3, "Error Open Data Base", "Error");
            } else {

                string sqlQuery =
                        "SELECT userName,password,id FROM Passwords WHERE userName=" +
                        string("\'") + userName + string("\'");

                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                if (rc != SQLITE_OK) {
                    fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return Passwords(-4, "Error Open Data Base", "Error");
                } else {
                    vector<string> s;
                    parsing(returningStr, s);
                    std::string userName = s[0];
                    std::string password = s[1];
                    int id = stoi(s[2]);

                    cout << "User Getted!" << '\n';
                    return Passwords(id, userName, password);
                }
            }
        }
    }

    int updatePassword(Passwords passwords) {
        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("db/mydb.db", &db);

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on update password users: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        string sqlVerif = "SELECT id FROM Passwords WHERE id =" + to_string(passwords.id);

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
                        "UPDATE Passwords SET userName = " + string("\'") + passwords.userName + string("\'") +
                        +", password =" + string("\'") + passwords.password + string("\'");

                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg); /// Callback
                if (rc != SQLITE_OK) {
                    fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;
                } else {
                    cout << "Passwords Updated!" << '\n';
                    return 1;
                }
            }
        }
    }

    int deletePasswords(int id) {

        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("db/mydb.db", &db); // aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on delete user: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        string sqlVerif = "SELECT id FROM Passwords WHERE id = " + to_string(id); // Da seg fault

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

                string sqlQuery = "DELETE FROM Passwords WHERE id = " + to_string(id);
                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                if (rc != SQLITE_OK) {
                    fprintf(stderr, "Delete comand doesn t work: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;
                } else {
                    cout << "Password Deleted!" << '\n';
                    return 1;
                }
            }
        }
    }
};


#endif //SOCIALMEDIA_HANDLERPASSWORDSDB_H
