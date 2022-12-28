//
// Created by lolluckestar on 11.12.2022.
//

#ifndef SOCIALMEDIA_HANDLERUSERDB_H
#define SOCIALMEDIA_HANDLERUSERDB_H

#include "../../models/User.h"
#include "../../db/mydb/sqlite3.h"
#include <iostream>
#include <string>
#include<vector>

using namespace std;

string returningStr;

void parsing(string s, vector<string> &result) {
    string copy = "";
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '=') {
            copy = "";
        }
        if (s[i] != '=' && s[i] != '\n')
            copy += s[i];

        if (s[i] == '\n') {
            result.push_back(copy);
            copy = "";
        }
    }

}

static int callback(void *data, int argc, char **argv, char **azColName) {
    returningStr = ""; //Aici initializez global ul;
    int i;

    for (i = 0; i < argc; i++) {
        returningStr += azColName[i];
        returningStr += "=";
        returningStr += argv[i] ? argv[i] : "NULL";
        returningStr += "\n";
    }
    return 0;
}

struct HandlerUserDB {

    HandlerUserDB() = default;

    int createUser(
            struct User user) {

        sqlite3 *db;
        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db);

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on insert user: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);

            return 0;
        }

        // TODO: VERIFICA DACA USERNAME-ul nu e luat
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

        if (rc != SQLITE_OK) {
            fprintf(stderr, "Select doesn't work %s\n", err_msg);
            return 0;
        } else {

            vector<string> s;
            parsing(returningStr, s);
            if (int(s.size()) == 1) {

                rc = sqlite3_exec(db, sqlQuery.c_str(), 0, 0, &err_msg);
                if (rc != SQLITE_OK) {

                    fprintf(stderr, "SQL error on insert user: %s\n", err_msg);

                    sqlite3_free(err_msg);
                    sqlite3_close(db);
                    return 0;
                } else {
                    cout << "User Created!" << '\n';
                    return 1;
                }
            } else {
                fprintf(stderr, "SQL error on user already exists: %s\n");
                sqlite3_close(db);
                return 0;
            }
        }
    }

    User getUser(int id) {

        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db);

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on get user: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return User(-1, -1, "Error Open Data Base", "Error", "Error", "Error", "Error", "Error");
        }


        string sqlVerif = "SELECT id FROM Users WHERE id=" + to_string(id);

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot use existance select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return User(-2, -2, "Error at SELECT EXISTANCE", "Error", "Error", "Error", "Error", "Error");
        } else {
            vector<string> s;
            parsing(returningStr, s);
            if (s.size() < 1) {
                fprintf(stderr, "Cannot find the user: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return User(-3, -3, "Error User Doesn't Exists", "Error", "Error", "Error", "Error", "Error");
            } else
            {

                string sqlQuery =
                        "SELECT isAdmin,userName,firstname,lastname,birthday,accountCreationDate FROM Users WHERE id=" +
                        to_string(id);

                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                if (rc != SQLITE_OK) {
                    fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return User(-5, -5, "Error using select", "Error", "Error", "Error", "Error", "Error");
                } else {
                    vector<string> s;
                    parsing(returningStr, s);
                    bool isAdmin;

                    if(s[0]=="0")
                        isAdmin=0;
                    else
                        isAdmin=1;
                    std::string userName=s[1];
                    std::string firstname=s[2];
                    std::string lastname=s[3];
                    std::string birthday=s[4];
                    std::string accountCreationDate=s[5];
                    std::string profileDescription=s[6];

                    cout << "User Getted!" << '\n';
                    return User(id, isAdmin, userName, firstname, lastname, birthday, accountCreationDate,
                                profileDescription);
                }
            }
        }

    }

    /*
           functia primeste ca si parametru un User object
           faci update in Users table unde id din parametru = id din tabel
           daca reuseste, returneaza 1, daca da fail, returneaza 0
  */
    int updateUser(User users) {
        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); // aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on update users: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        /// Aici trebuie sa vad daca exista utilizatorul meu. Altfel returnez iar cv
        /*
            string sqlVerif="SELECT EXISTS(SELECT id FROM Users WHERE id = users.id)"; //

            rc = sqlite3_exec(db,sqlVerif.c_str(),0,0,&err_msg);
            ///Ar trb in loc de 0 sa bag si functia callback ca sa iau din acel select cv

    /// Test : nu prea e oke
            if(rc!=SQLITE_OK)
            {
                fprintf(stderr, "Cannot check id existance select: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return 0;
            }
            else
            {
                int exists=sqlite3_column_int(stmt,0); ///Atentie ca asta cred ca retureaza mereu 0 si daca pun callnack-ul
                if(exists == 0) {
                    fprintf(stderr, "Cannot find the id: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;
                }
                else  ///Am gasit id-ul
                {
                */
        /// AICI FAC SET-UL   ; l comment i am pus strig sqlVerif si la rc am scus int rc.
        string sqlVerif = "UPDATE Users SET isAdmin = " + to_string(users.isAdmin) + ", userName = " + users.userName +
                          ", firstname = users.firstname , lastname = users.lastname , birthday = users.birthday , accountCreationDate = users.accountCreationDate , profileDescription = users.profileDescription WHERE id = users.id";
        rc = sqlite3_exec(db, sqlVerif.c_str(), 0, 0, &err_msg); /// Callback
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        } else {
            cout << "User Updated!" << '\n';
            return 1;
        }
    }
    // }
    // }
    /*
         functia primeste ca si parametru un id
         stergi din tabel user-ul cu id-ul ala
         daca reuseste, returneaza 1, daca da fail, returneaza 0
     */
    int deleteUser(int id) {

        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); // aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on delete user: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        /// Aici trebuie sa vad daca exista utilizatorul meu. Altfel returnez iar cv

        string sqlVerif = "SELECT EXISTS(SELECT id FROM Users WHERE Users.id = id)"; // Da seg fault

        rc = sqlite3_exec(db, sqlVerif.c_str(), 0, 0, &err_msg);
        /// Ar trb in loc de 0 sa bag si functia callback ca sa iau din acel select cv

        /// Test : nu prea e oke e pus cu comm mai jos :
        /*
                    if(rc!=SQLITE_OK)
                    {
                        fprintf(stderr, "Cannot check id existance select: %s\n", sqlite3_errmsg(db));
                        sqlite3_close(db);
                        return 0;
                    }
                    else
                    {
                        int exists=sqlite3_column_int(stmt,0); ///Atentie ca asta cred ca retureaza mereu 0 si daca pun callnack-ul
                        if(exists == 0) {
                            fprintf(stderr, "Cannot find the id: %s\n", sqlite3_errmsg(db));
                            sqlite3_close(db);
                            return 0;
                        }
                        else  ///Am gasit id-ul
                        {
                        */
        sqlVerif = "DELETE FROM Users WHERE Users.id = id";      /// Atentie trebuia users (corrected)
        rc = sqlite3_exec(db, sqlVerif.c_str(), 0, 0, &err_msg); /// Callback
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Delete comand doesn t work: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        } else {
            cout << "User Deleted!" << '\n';
            return 1;
        }
        cout << "nici aici nush ce sa i fac" << '\n';
        return 1;
    }
    //          }

    //   }
};

#endif // SOCIALMEDIA_HANDLERUSERDB_H
