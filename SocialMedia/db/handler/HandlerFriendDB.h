//
// Created by lolluckestar on 15.12.2022.
//

#ifndef SOCIALMEDIA_HANDLERFRIENDDB_H
#define SOCIALMEDIA_HANDLERFRIENDDB_H
#include "../../models/Friend.h"
#include<iostream>
#include<string>
#include"GlobalFunction.h"

using namespace std;

struct HandlerFriendDB {

    HandlerFriendDB()=default;

    int createFriend(
            Friend friendd
    ) {
        sqlite3 *db;
        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); //aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot open database on insert friend: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

///id-urile nu sunt sigur daca trb inserat.

        string sqlQuery = "INSERT INTO Friend (id2,type) VALUES(" + to_string(friendd.id2) + "," +
                          "\'" + friendd.type + "\')";

        rc = sqlite3_exec(db, sqlQuery.c_str(), 0, 0, &err_msg);
        if (rc != SQLITE_OK) {

            fprintf(stderr, "SQL error on create friend: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            return 0;
        } else {
            sqlite3_close(db);
            cout << "Friend Inserted" << '\n';
            return 1;
        }
    }

    Friend getFriend(  int id1,int id2){

        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); //aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on get Friend: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return Friend(-1, -1, "Error Open Data Base");
        }

        /// Aici trebuie sa vad daca exista utilizatorul meu. Altfel returnez iar cv ; trb rez ca la userHandler
/*
        string sqlVerif = "SELECT EXISTS(SELECT id1,id2 FROM Friend WHERE id1 = Friend.id1 AND id2 = Friend.id2)";

        rc = sqlite3_exec(db, sqlVerif.c_str(), 0, 0, &err_msg);
        ///Ar trb in loc de 0 sa bag si functia callback ca sa iau din acel select cv

/// Test : nu prea e oke
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot use existance select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return Friend(-2, -2, "Error at SELECT EXISTANCE");
        } else {
            int exists = sqlite3_column_int(stmt,
                                            0); ///Atentie ca asta cred ca retureaza mereu 0 si daca pun callnack-ul
            if (exists == 0) {
                fprintf(stderr, "Cannot find the friend: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return Friend(-3, -3, "Error User Doesn't Exists");
            } else  ///Am gasit userul
            {
            */
                    string sqlVerif = "SELECT type FROM Friend WHERE id1 = Friend.id1 AND id2=Friend.id2";
                    rc = sqlite3_exec(db, sqlVerif.c_str(), 0, 0, &err_msg);
                    if (rc != SQLITE_OK) {

                        fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
                        sqlite3_close(db);
                        return Friend(-5, -5, "Error using select");

                    } else {
                        const unsigned char *types = sqlite3_column_text(stmt, 0);
                        std::string type;
                        /*
                                type = types;    /// REINTERPRET_CAST TRB SA-I DAU

                     */
                        cout << "Friend Getted!" << '\n';
                        return Friend(id1,id2,type);

                    }
    }

    int updateFriend(Friend friendd){
        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); //aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on update Friend: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        /// Aici trebuie sa vad daca exista utilizatorul meu. Altfel returnez iar cv
        /*
            string sqlVerif="SELECT EXISTS(SELECT id1,id2 FROM FriendRequest WHERE id1 = friendd.id1 AND id2=friendd.id2)"; //

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
                    ///AICI FAC SET-UL   ; NU MERGE : Set doesn t work on Friend no such column friendd.type.(nu se cheama la fel ca sa l confunde)
                    string sqlVerif = "UPDATE Friend SET type = friendd.type WHERE id1 = friendd.id1 AND id2 = friendd.id2";
                    rc = sqlite3_exec(db, sqlVerif.c_str(), 0, 0, &err_msg); ///Callback
                    if (rc != SQLITE_OK) {
                        fprintf(stderr, "Set comand doesn t work on Friend %s\n", sqlite3_errmsg(db));
                        sqlite3_close(db);
                        return 0;
                    } else {
                        cout << "Friend Updated" << '\n';
                        return 1;
                    }
    }

    int deleteFriend( int id1,int id2) {
        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); //aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK)
        {

            fprintf(stderr, "Cannot open database on delete friend: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        /// Aici trebuie sa vad daca exista utilizatorul meu. Altfel returnez iar cv

        string sqlVerif = "SELECT EXISTS(SELECT id1,id2 FROM Friend WHERE Friend.id1 = id1 AND Friend.id2=id2)";

        rc = sqlite3_exec(db, sqlVerif.c_str(), 0, 0, &err_msg);
        ///Ar trb in loc de 0 sa bag si functia callback ca sa iau din acel select cv

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
                    sqlVerif = "DELETE FROM Friend WHERE id1 = Friend.id1 AND id2 = Friend.id2";   ///Atentie trebuia users (corrected)
                    rc = sqlite3_exec(db, sqlVerif.c_str(), 0, 0, &err_msg);
                    if (rc != SQLITE_OK) {
                        fprintf(stderr, "Delete comand doesn t work: %s\n", sqlite3_errmsg(db));
                        sqlite3_close(db);
                        return 0;

                    } else {
                        cout << "Friend Deleted!" << '\n';
                        return 1;

                    }
    }
};
#endif //SOCIALMEDIA_HANDLERFRIENDDB_H
