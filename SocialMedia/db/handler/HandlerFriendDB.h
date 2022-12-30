//
// Created by lolluckestar on 15.12.2022.
//

#ifndef SOCIALMEDIA_HANDLERFRIENDDB_H
#define SOCIALMEDIA_HANDLERFRIENDDB_H

#include "../../models/Friend.h"
#include <iostream>
#include <string>
#include "GlobalFunction.h"
#include<sstream>
using namespace std;

stringstream ss1,ss2;

struct HandlerFriendDB
{

    HandlerFriendDB() = default;

    int createFriend(
        Friend friendd)
    {
        sqlite3 *db;
        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db);

        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "Cannot open database on insert friend: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        string sqlVerif = "SELECT id1,id2 FROM Friend WHERE id1 = " + to_string(friendd.id1) + " AND id2 = "
                + to_string(friendd.id2);

        string sqlVerif2 = "SELECT id1,id2 FROM Friend WHERE id1 = " + to_string(friendd.id2) + " AND id2 = "
                + to_string(friendd.id1);

        string sqlQuery = "INSERT INTO Friend (id1,id2,type) VALUES(" + to_string(friendd.id1) + ","
                + to_string(friendd.id2) + "," + "\'" + friendd.type + "\')";

        string sqlQuery2 = "INSERT INTO Friend (id1,id2,type) VALUES(" + to_string(friendd.id2) + ","
                + to_string(friendd.id1) + "," + "\'" + friendd.type + "\')";

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);
      int rc2 = sqlite3_exec(db, sqlVerif2.c_str(), callback2, 0, &err_msg);
        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "Can't say nothing about existance condition: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            return 0;
        } else if(rc2 != SQLITE_OK)
        {
            fprintf(stderr, "Can't say nothing about existance condition: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            return 0;
        }
        else
        {
            vector<string> s,s2;
            parsing(returningStr, s);
            parsing(returningStr2, s2);
            if (s.size() != 0)
            {
                fprintf(stderr, "It still exists a user with this id %s\n", err_msg);
                sqlite3_free(err_msg);
                sqlite3_close(db);
                return 0;
            } else if(s2.size() != 0)
            {
                fprintf(stderr, "It still exists a user with this id %s\n", err_msg);
                sqlite3_free(err_msg);
                sqlite3_close(db);
                return 0;
            }
            else
            {
                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                rc2= sqlite3_exec(db, sqlQuery2.c_str(), callback2, 0, &err_msg);
                if (rc != SQLITE_OK)
                {

                    fprintf(stderr, "SQL error on create friend: %s\n", err_msg);
                    sqlite3_free(err_msg);
                    sqlite3_close(db);
                    return 0;
                } else if(rc2 != SQLITE_OK)
                {
                    fprintf(stderr, "SQL error on create friend: %s\n", err_msg);
                    sqlite3_free(err_msg);
                    sqlite3_close(db);
                    return 0;
                }
                else
                {
                    sqlite3_close(db);
                    cout << "Friend Inserted" << '\n';
                    return 1;
                }
            }
        }
    }

    Friend getFriend(int id1, int id2)
    {

        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db);

        if (rc != SQLITE_OK)
        {

            fprintf(stderr, "Cannot open database on get Friend: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return Friend(-1, -1, -1, "Error Open Data Base");
        }

        string sqlVerif = "SELECT id1,id2 FROM Friend WHERE id1 = " + to_string(id1) + " AND id2 = " + to_string(id2);
        string sqlVerif2 = "SELECT id1,id2 FROM Friend WHERE id1 = " + to_string(id2) + " AND id2 = " + to_string(id1);

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);
       int rc2 = sqlite3_exec(db, sqlVerif2.c_str(), callback2, 0, &err_msg);
        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "Cannot use existance select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return Friend(-2, -2, -2, "Error at SELECT EXISTANCE");
        }
        else if(rc2!= SQLITE_OK)
        {
            fprintf(stderr, "Cannot use existance select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return Friend(-2, -2, -2, "Error at SELECT EXISTANCE");
        }
        else
        {
            vector<string> s,s2;
            parsing(returningStr, s);
            parsing(returningStr2, s2);
            if (s.size() == 0)
            {
                fprintf(stderr, "Cannot find the friend: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return Friend(-3, -3, -3, "Error User Doesn't Exists");
            }else if(s2.size() == 0)
            {
                fprintf(stderr, "Cannot find the friend: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return Friend(-3, -3, -3, "Error User Doesn't Exists");
            }
            else
            {
                 string sqlQuery =
                    "SELECT type FROM Friend WHERE id1 = " + to_string(id1) + " AND id2 = " + to_string(id2);
                string sqlQuery2=
                        "SELECT type FROM Friend WHERE id1 = " + to_string(id2) + " AND id2 = " + to_string(id1);
                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                int rc2 = sqlite3_exec(db, sqlQuery2.c_str(), callback2, 0, &err_msg);
                if (rc != SQLITE_OK)
                {
                    fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return Friend(-5, -5, -5, "Error using select");
                }else if(rc2 != SQLITE_OK)
                {
                    fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return Friend(-5, -5, -5, "Error using select");
                }
                else
                {
                    vector<string> s,s2;
                    parsing(returningStr, s);
                    parsing(returningStr2, s2);

                    if(s.size()!=0) {
                        std::string type = s[0];
                        std::string idQuery = "SELECT id FROM Friend WHERE id1 = " + to_string(id1) + " AND id2 = " +
                                to_string(id2);

                       int rcId= sqlite3_exec(db, idQuery.c_str(), callback, 0, &err_msg);
                       if(rcId != SQLITE_OK)
                       {
                           fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
                           sqlite3_close(db);
                           return Friend(-5, -5, -5, "Error using select id first");
                       }
                       else {
                           vector<string> sId;
                           parsing(returningStr, sId);
                           string idd = sId[0];
                            int a;
                             ss1<<idd;
                            ss1>>a;
                           cout << "Friend Getted!" << '\n';
                           return Friend(a, id1, id2, type);
                       }
                    }
                    else if(s2.size() != 0)
                    {
                        std::string type = s2[0];
                        std::string idQuery2 = "SELECT id FROM Friend WHERE id1 = " + to_string(id1) + " AND id2 = " +
                                              to_string(id2);

                        int rcId = sqlite3_exec(db, idQuery2.c_str(), callback2, 0, &err_msg);
                        if(rcId != SQLITE_OK)
                        {
                            fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
                            sqlite3_close(db);
                            return Friend(-5, -5, -5, "Error using select id second");
                        }
                        else {
                            vector<string> sId2;
                            parsing(returningStr2, sId2);
                            string idd = sId2[0];
                            int a;
                            ss2<<idd;
                            ss2>>a;
                            cout << "Friend Getted!" << '\n';
                            return Friend(a, id1, id2, type);
                        }
                    }
                }
            }
        }
    }

    int updateFriend(Friend friendd)
    {
        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db);

        if (rc != SQLITE_OK)
        {

            fprintf(stderr, "Cannot open database on update Friend: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        string sqlVerif = "SELECT id1,id2 FROM FriendRequest WHERE id1 = " + to_string(friendd.id1) +
                          " AND id2 = " + to_string(friendd.id2);
        string sqlVerif2 = "SELECT id1,id2 FROM FriendRequest WHERE id1 = " + to_string(friendd.id2) +
                          " AND id2 = " + to_string(friendd.id1);

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);
     int rc2 = sqlite3_exec(db, sqlVerif2.c_str(), callback2, 0, &err_msg);
        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "Cannot check id existance select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }
        else if(rc2 != SQLITE_OK)
        {
            fprintf(stderr, "Cannot check id existance select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }
        else
        {
            vector<string> s,s2;
            parsing(returningStr, s);
            parsing(returningStr2, s2);

            if (s.size() == 0)
            {
                fprintf(stderr, "Cannot find the id: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return 0;
            }
            else if(s2.size() == 0)
            {
                fprintf(stderr, "Cannot find the id: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return 0;
            }
            else
            {

                string sqlQuery =
                    "UPDATE Friend SET type =" + string("\'") + friendd.type + string("\'") + "WHERE id1 = " + to_string(friendd.id1) + " AND id2 = " + to_string(friendd.id2);
                string sqlQuery2 =
                        "UPDATE Friend SET type =" + string("\'") + friendd.type + string("\'") + "WHERE id1 = " + to_string(friendd.id2) + " AND id2 = " + to_string(friendd.id1);

                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                int rc2=sqlite3_exec(db, sqlQuery2.c_str(), callback2, 0, &err_msg);
                if (rc != SQLITE_OK)
                {
                    fprintf(stderr, "Set comand doesn t work on Friend %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;
                } else if(rc2 != SQLITE_OK){
                    fprintf(stderr, "Set comand doesn t work on Friend %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;
                }
                else
                {
                    cout << "Friend Updated" << '\n';
                    return 1;
                }
            }
        }
    }

    int deleteFriend(int id1, int id2)
    {
        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); // aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK)
        {

            fprintf(stderr, "Cannot open database on delete friend: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        string sqlVerif = "SELECT id1,id2 FROM Friend WHERE id1 = " + to_string(id1) + " AND id2 = " + to_string(id2);
        string sqlVerif2 = "SELECT id1,id2 FROM Friend WHERE id1 = " + to_string(id2) + " AND id2 = " + to_string(id1);

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);
      int rc2 = sqlite3_exec(db, sqlVerif2.c_str(), callback2, 0, &err_msg);
        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "Cannot check id existance select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }
        else if(rc2 != SQLITE_OK)
        {
            fprintf(stderr, "Cannot check id existance select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }
        else
        {
            vector<string> s,s2;
            parsing(returningStr, s);
            parsing(returningStr2, s2);
            if (s.size() == 0)
            {
                fprintf(stderr, "Cannot find the id: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return 0;
            }
            else if(s2.size() == 0)
            {
                fprintf(stderr, "Cannot find the id: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return 0;
            }
            else
            {

                string sqlQuery = "DELETE FROM Friend WHERE id1 = " + to_string(id1) + " AND id2 = " + to_string(id2);
                string sqlQuery2 = "DELETE FROM Friend WHERE id1 = " + to_string(id2) + " AND id2 = " + to_string(id1);
                rc = sqlite3_exec(db, sqlQuery.c_str(), 0, 0, &err_msg);
               int rc2 = sqlite3_exec(db, sqlQuery2.c_str(), 0, 0, &err_msg);
                if (rc != SQLITE_OK)
                {
                    fprintf(stderr, "Delete comand doesn t work: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;
                }else if(rc2 != SQLITE_OK)
                {
                    fprintf(stderr, "Delete comand doesn t work: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;
                }
                else
                {
                    cout << "Friend Deleted!" << '\n';
                    return 1;
                }
            }
        }
    }
};

#endif // SOCIALMEDIA_HANDLERFRIENDDB_H
