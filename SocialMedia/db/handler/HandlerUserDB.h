//
// Created by lolluckestar on 11.12.2022.
//
#pragma once
#ifndef SOCIALMEDIA_HANDLERUSERDB_H
#define SOCIALMEDIA_HANDLERUSERDB_H
#include "GlobalFunction.h"
#include "../../models/User.h"
#include "../../db/mydb/sqlite3.h"
#include <iostream>
#include <string>
#include <vector>


using namespace std;

struct HandlerUserDB
{

    HandlerUserDB() = default;

    int createUser(
        struct User user)
    {

        sqlite3 *db;
        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db);

        if (rc != SQLITE_OK)
        {

            fprintf(stderr, "Cannot open database on insert user: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);

            return 0;
        }

        string sqlVerif;
        sqlVerif =
            "SELECT userName FROM Users WHERE userName=" +
            string("\'") + user.userName + string("\'");
        string sqlQuery =
            "INSERT INTO Users (isAdmin,userName,firstname,lastname,birthday,accountCreationDate,profileDescription) VALUES(" +
            to_string(user.isAdmin) + "," +
            "\'" + user.userName + "\'," +
            "\'" + user.firstname + "\'," +
            "\'" + user.lastname + "\'," +
            "\'" + user.birthday + "\'," +
            "\'" + user.accountCreationDate + "\'," +
            "\'" + user.profileDescription + "\')";

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);

        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "Select doesn't work %s\n", err_msg);
            return 0;
        }
        else
        {

            vector<string> s;
            parsing(returningStr, s);
            // cout<<s.size();
            if (int(s.size()) < 1)
            { // daca ==1 inseamna ca a gasit un user deci exista deja.

                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                if (rc != SQLITE_OK)
                {

                    fprintf(stderr, "SQL error on insert user: %s\n", err_msg);
                    sqlite3_free(err_msg);
                    sqlite3_close(db);
                    return 0;
                }
                else
                {
                    cout << "User Created!" << '\n';
                    return 1;
                }
            }
            else
            {
                fprintf(stderr, "SQL error on user already exists: %s\n");
                sqlite3_close(db);
                return 0;
            }
        }
    }

    User getUser(int id)
    {

        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db);

        if (rc != SQLITE_OK)
        {

            fprintf(stderr, "Cannot open database on get user: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return User(-1, -1, "Error Open Data Base", "Error", "Error", "Error", "Error", "Error");
        }

        string sqlVerif = "SELECT id FROM Users WHERE id=" + to_string(id);

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);

        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "Cannot use existance select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return User(-2, -2, "Error at SELECT EXISTANCE", "Error", "Error", "Error", "Error", "Error");
        }
        else
        {
            vector<string> s;
            parsing(returningStr, s);
            if (s.size() == 0)
            {
                fprintf(stderr, "Cannot find the user: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return User(-3, -3, "Error User Doesn't Exists", "Error", "Error", "Error", "Error", "Error");
            }
            else
            {

                string sqlQuery =
                    "SELECT isAdmin,userName,firstname,lastname,birthday,accountCreationDate,profileDescription FROM Users WHERE id=" +
                    to_string(id);

                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                if (rc != SQLITE_OK)
                {
                    fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return User(-4, -4, "Error using select", "Error", "Error", "Error", "Error", "Error");
                }
                else
                {
                    vector<string> s;
                    parsing(returningStr, s);
                    // cout<<returningStr;
                    bool isAdmin;

                    if (s[0] == "0")
                        isAdmin = 0;
                    else
                        isAdmin = 1;
                    std::string userName = s[1];
                    std::string firstname = s[2];
                    std::string lastname = s[3];
                    std::string birthday = s[4];
                    std::string accountCreationDate = s[5];
                    std::string profileDescription = s[6];

                    cout << "User Getted!" << '\n';
                    return User(id, isAdmin, userName, firstname, lastname, birthday, accountCreationDate,
                                profileDescription);
                }
            }
        }
    }

    int updateUser(User users)
    {
        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db);

        if (rc != SQLITE_OK)
        {

            fprintf(stderr, "Cannot open database on update users: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        string sqlVerif = "SELECT id FROM Users WHERE id =" + to_string(users.id);

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);

        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "Cannot check id existance select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }
        else
        {
            vector<string> s;
            parsing(returningStr, s);
            if (s.size() == 0)
            {
                fprintf(stderr, "Cannot find the id: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return 0;
            }
            else
            {

                string sqlQuery =
                    "UPDATE Users SET isAdmin = " + to_string(users.isAdmin) + ", userName = " + string("\'") +
                    users.userName +
                    string("\'") + ", firstname =" + string("\'") + users.firstname + string("\'") +
                    ", lastname =" + string("\'") + users.lastname +
                    string("\'") + ", birthday =" + string("\'") + users.birthday + string("\'") +
                    ", accountCreationDate =" + string("\'") + users.accountCreationDate + string("\'") + ", profileDescription =" + string("\'") +
                    users.profileDescription + string("\'") +
                    " WHERE id =" + to_string(users.id);
                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg); /// Callback
                if (rc != SQLITE_OK)
                {
                    fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;
                }
                else
                {
                    cout << "User Updated!" << '\n';
                    return 1;
                }
            }
        }
    }

    int deleteUser(int id)
    {

        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); // aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK)
        {

            fprintf(stderr, "Cannot open database on delete user: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        string sqlVerif = "SELECT id FROM Users WHERE id = " + to_string(id); // Da seg fault

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);

        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "Cannot check id existance select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }
        else
        {
            vector<string> s;
            parsing(returningStr, s);
            if (s.size() == 0)
            {
                fprintf(stderr, "Cannot find the id: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return 0;
            }
            else
            {

                string sqlQuery = "DELETE FROM Users WHERE id = " + to_string(id);
                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                if (rc != SQLITE_OK)
                {
                    fprintf(stderr, "Delete comand doesn t work: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;
                }
                else
                {
                    cout << "User Deleted!" << '\n';
                    return 1;
                }
            }
        }
    }
};

#endif // SOCIALMEDIA_HANDLERUSERDB_H
