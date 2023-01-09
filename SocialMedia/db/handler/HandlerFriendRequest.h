//
// Created by lolluckestar on 15.12.2022.
//

#ifndef SOCIALMEDIA_HANDLERFRIENDREQUEST_H
#define SOCIALMEDIA_HANDLERFRIENDREQUEST_H

#include "../../models/FriendRequest.h"
#include <iostream>
#include <string>
#include "GlobalFunction.h"

using namespace std;

struct HandlerFriendRequestDB
{

    HandlerFriendRequestDB() = default;

    int createFriendRequest(
        FriendRequest friendRequest)
    {
        sqlite3 *db;
        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("db/mydb.db", &db);

        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "Cannot open database on insert friendRequest: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        string sqlVerif = "SELECT id1,id2 FROM FriendRequest WHERE id1=" + to_string(friendRequest.id1) + " AND id2=" +
                          to_string(friendRequest.id2);

        string sqlVerif2 = "SELECT id1,id2 FROM FriendRequest WHERE id1=" + to_string(friendRequest.id2) + " AND id2=" +
                           to_string(friendRequest.id1);

        string sqlQuery = "INSERT INTO FriendRequest (id1,id2,accepted,type) VALUES(" + to_string(friendRequest.id1) + "," +
                          to_string(friendRequest.id2) + "," +
                          "\'" + to_string(friendRequest.accepted) + "\'," +
                          "\'" + friendRequest.type + "\')";
        string sqlQuery2="INSERT INTO FriendRequest (id2,id1,accepted,type) VALUES(" + to_string(friendRequest.id1) + "," +
                         to_string(friendRequest.id2) + "," +
                         "\'" + to_string(friendRequest.accepted) + "\'," +
                         "\'" + friendRequest.type + "\')";

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);
        int rc2 = sqlite3_exec(db, sqlVerif2.c_str(), callback2, 0, &err_msg);

        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "We can't say anything about the existence on 1st check: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            return 0;
        }
        if (rc2 != SQLITE_OK)
        {
            fprintf(stderr, "We can't say anything about the existence on 2nd check: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            return 0;
        }
        else
        {
            // CHECK FOR S2
            vector<string> s;
            parsing(returningStr, s);
            vector<string>s2;
            parsing(returningStr2,s2);
            if (s.size() != 0)
            {
                fprintf(stderr, "This friendship exists: %s\n", err_msg);
                sqlite3_free(err_msg);
                sqlite3_close(db);
                return 0;
            }else if(s2.size()!=0){
                fprintf(stderr, "This friendship exists: %s\n", err_msg);
                sqlite3_free(err_msg);
                sqlite3_close(db);
                return 0;
            }
            else
            {
                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                rc2 = sqlite3_exec(db, sqlQuery2.c_str(), callback2, 0, &err_msg);
                if (rc != SQLITE_OK)
                {

                    fprintf(stderr, "SQL error on create friendRequest: %s\n", err_msg);
                    sqlite3_free(err_msg);
                    sqlite3_close(db);
                    return 0;
                } else if(rc2 != SQLITE_OK)
                {
                    fprintf(stderr, "SQL error on create friendRequest: %s\n", err_msg);
                    sqlite3_free(err_msg);
                    sqlite3_close(db);
                    return 0;
                }
                else
                {
                    sqlite3_close(db);
                    cout << "FriendRequest Inserted" << '\n';
                    return 1;
                }
            }
        }
    }

    FriendRequest getFriendRequest(int id1, int id2)
    {

        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("db/mydb.db", &db);

        if (rc != SQLITE_OK)
        {

            fprintf(stderr, "Cannot open database on get FriendRequest: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return FriendRequest(-1, -1, -1, "Error Open Data Base", false);
        }

        string sqlVerif =
            "SELECT id,id1,id2 FROM FriendRequest WHERE id1 = " + to_string(id1) + " AND id2 = " + to_string(id2);

        string sqlVerif2 =
                "SELECT id,id1,id2 FROM FriendRequest WHERE id1=" + to_string(id2) + " AND id2=" + to_string(id1);

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);
        int rc2=sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);
        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "Cannot use existance select first one: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return FriendRequest(-2, -2, -2, "Error at SELECT EXISTANCE", false);
        }
        else if( rc2 != SQLITE_OK){
            fprintf(stderr, "Cannot use existance select second one: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return FriendRequest(-2, -2, -2, "Error at SELECT EXISTANCE", false);
        }
        else
        {
            vector<string> s,s2;
            parsing(returningStr, s);
            parsing(returningStr2,s2);
            if (s.size() == 0)
            {
                fprintf(stderr, "Cannot find the user: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return FriendRequest(-3, -3, -3, "Error User Doesn't Exists", false);
            }
            else if(s2.size())
            {
                fprintf(stderr, "Cannot find the user: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return FriendRequest(-3, -3, -3, "Error User Doesn't Exists", false);
            }
            else
            {

                string sqlQuery = "SELECT accepted,type FROM FriendRequest WHERE id1 = " + to_string(id1) +
                                  " AND id2 = " + to_string(id2);

                string sqlQuery2 = "SELECT accepted,type FROM FriendRequest WHERE id1 = " + to_string(id2) +
                                  " AND id2 = " + to_string(id1);

                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                rc2 = sqlite3_exec(db, sqlQuery2.c_str(), callback2, 0, &err_msg);
                if (rc != SQLITE_OK)
                {

                    fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return FriendRequest(-5, -5, -5, "Error using select", false);
                }
                else if(rc2 != SQLITE_OK)
                {
                    fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return FriendRequest(-5, -5, -5, "Error using select", false);
                }
                else
                {
                    vector<string> s,s2;
                    parsing(returningStr, s);
                    parsing(returningStr2,s2);
                    if(s.size()!=0) {
                        string type = s[0];
                        bool accepted;
                        if (s[1] == "0") {
                            accepted = 0;
                        } else {
                            accepted = 1;
                        }
                        cout << "FriendRequest Getted!" << '\n';
                        return FriendRequest(0, id1, id2, type, accepted);
                    }
                    else
                        if(s2.size() !=0 )
                        {
                            string type = s2[0];
                            bool accepted;
                            if (s2[1] == "0") {
                                accepted = 0;
                            } else {
                                accepted = 1;
                            }
                            cout << "FriendRequest Getted!" << '\n';
                            return FriendRequest(0, id1, id2, type, accepted);
                        }
                }
            }
        }
    }

    vector<string> GetRequestNames(string name) //vedem daa facem si cu type si bag numele meu ; e ca sa vad toti prietenii
    {
        vector<string> collect;
        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("db/mydb.db", &db);

        if (rc != SQLITE_OK)
        {

            fprintf(stderr, "Cannot open database on get Friend: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            collect.push_back("fail");
            return collect;
        }

        string sqlVerif = "SELECT id FROM Users WHERE userName = " + string("\'") + name+ string("\'");

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);
        if(rc!=SQLITE_OK)
        {
            fprintf(stderr, "Cannot verify existence of that user name %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            collect.push_back("fail");
            return collect;
        }
        else
        {
            vector<string> s;
            parsing(returningStr,s);
            if(s.size() == 0)
            {
                fprintf(stderr, "user name does not exists %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                collect.push_back("fail");
                return collect;
            }
            else
            {
                int id = stoi(s[0]);
                string sqlQuery = "SELECT userName FROM Users JOIN FriendRequest ON" + string("(") +
                                  "Users.id = FriendRequest.id1 AND FriendRequest.id2 = "+ to_string(id) + ")"; //aici scot toti userii care au id ul 1 in Friends

                rc = sqlite3_exec(db, sqlQuery.c_str(), callback2, 0, &err_msg);
                if(rc != SQLITE_OK)
                {
                    fprintf(stderr, "cannot take Friend Request list %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    collect.push_back("fail");
                    return collect;
                }
                else {
                    printf("Show Friend Request List Succes");
                    parsing(returningStr2, collect);
                    return collect;
                }
            }
        }
    }



    int updateFriendRequest(FriendRequest friendRequest)
    {
        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("db/mydb.db", &db); // aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK)
        {

            fprintf(stderr, "Cannot open database on update FriendRequest: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        string sqlVerif =
            "SELECT id1,id2 FROM FriendRequest WHERE id1 = " + to_string(friendRequest.id1) +
            " AND id2 = " + to_string(friendRequest.id2);

        string sqlVerif2 = "SELECT id1,id2 FROM FriendRequest WHERE id1=" + to_string(friendRequest.id2) + " AND id2=" +
                           to_string(friendRequest.id1);

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);
        int rc2 = sqlite3_exec(db, sqlVerif2.c_str(), callback2, 0, &err_msg);
        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "Cannot check id existance select first one: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }
        else if(rc2!= SQLITE_OK)
        {
            fprintf(stderr, "Cannot check id existance select second one: %s\n", sqlite3_errmsg(db));
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

                string sqlQuery = "UPDATE FriendRequest SET accepted = " + string("\'") +
                                  to_string(friendRequest.accepted) + string("\'") + " , type = " + string("\'") +
                                  friendRequest.type + string("\'") + "WHERE id1 = " + to_string(friendRequest.id1) +
                                  " AND id2 =" + to_string(friendRequest.id2);

                string sqlQuery2 = "UPDATE FriendRequest SET accepted = " + string("\'") +
                                  to_string(friendRequest.accepted) + string("\'") + " , type = " + string("\'") +
                                  friendRequest.type + string("\'") + "WHERE id1 = " + to_string(friendRequest.id2) +
                                  " AND id2 =" + to_string(friendRequest.id1);

                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                int rc2 = sqlite3_exec(db, sqlQuery2.c_str(), callback2, 0, &err_msg);
                if (rc != SQLITE_OK)
                {
                    fprintf(stderr, "Set comand doesn t work on friendRequest: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;
                }
                else if(rc2 != SQLITE_OK)
                {
                    fprintf(stderr, "Set comand doesn t work on friendRequest: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;
                }
                else
                {
                    cout << "FriendRequest Updated" << '\n';
                    return 1;
                }
            }
        }
    }

    int deleteFriendRequest(int id1, int id2)
    {

        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("db/mydb.db", &db); // aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK)
        {

            fprintf(stderr, "Cannot open database on delete message: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        string sqlVerif =
            "SELECT id1,id2 FROM FriendRequest WHERE id1 = " + to_string(id1) + " AND id2 =" + to_string(id2);
        string sqlVerif2 =
                "SELECT id1,id2 FROM FriendRequest WHERE id1 = " + to_string(id2) + " AND id2 =" + to_string(id1);

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);
        int rc2=sqlite3_exec(db, sqlVerif.c_str(), callback2, 0, &err_msg);

        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "Cannot check id existance select on first: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        } else if(rc2 != SQLITE_OK)
        {
            fprintf(stderr, "Cannot check id existance select on second: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }
        else
        {
            vector<string> s,s2;
            parsing(returningStr, s);
            parsing(returningStr2,s2);
            if (s.size() == 0)
            {
                fprintf(stderr, "Cannot find the id: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return 0;
            }else if(s2.size()==0)
            {
                fprintf(stderr, "Cannot find the id: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return 0;
            }
            else
            {

                string sqlQuery = "DELETE FROM FriendRequest WHERE id1 = " + to_string(id1) + " AND id2 = " + to_string(id2);
                string sqlQuery2 = "DELETE FROM FriendRequest WHERE id1 = " + to_string(id2) + " AND id2 = " + to_string(id1);
                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                rc2 = sqlite3_exec(db, sqlQuery2.c_str(), callback2, 0, &err_msg);
                if (rc != SQLITE_OK)
                {
                    fprintf(stderr, "Delete comand doesn t work: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;
                } else if (rc2 != SQLITE_OK)
                {
                    fprintf(stderr, "Delete comand doesn t work: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;
                }
                else
                {
                    cout << "FriendRequest deleted" << '\n';
                    return 1;
                }
            }
        }
    }
};

#endif // SOCIALMEDIA_HANDLERFRIENDREQUEST_H
