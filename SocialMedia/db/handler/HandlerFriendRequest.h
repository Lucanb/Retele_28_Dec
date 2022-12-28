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

    HandlerFriendRequestDB()=default;

    int createFriendRequest(
            FriendRequest friendRequest
    ) {
        sqlite3 *db;
        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); //aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot open database on insert friendRequest: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

///chatId nu sunt sigur daca trb inserat.

        string sqlQuery = "INSERT INTO FriendRequest (id2,accepted,type) VALUES(" + to_string(friendRequest.id2) + "," +
                          "\'" + to_string(friendRequest.accepted) + "\'," +
                          "\'" + friendRequest.type + "\')";


        rc = sqlite3_exec(db, sqlQuery.c_str(), 0, 0, &err_msg);
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

    FriendRequest getFriendRequest( int id1,int id2)
    {

        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); //aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on get FriendRequest: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return FriendRequest(-1, -1, "Error Open Data Base", false);
        }

        /// Aici trebuie sa vad daca exista utilizatorul meu. Altfel returnez iar cv ; trb rez ca la userHandler
/*
        string sqlVerif = "SELECT EXISTS(SELECT id1,id2 FROM FriendRequest WHERE id1 = FriendRequest.id1 AND id2 = FriendRequest.id2)";

        rc = sqlite3_exec(db, sqlVerif.c_str(), 0, 0, &err_msg);
        ///Ar trb in loc de 0 sa bag si functia callback ca sa iau din acel select cv

/// Test : nu prea e oke
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot use existance select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return FriendRequest(-2, -2, "Error at SELECT EXISTANCE", "Error", false);
        } else {
            int exists = sqlite3_column_int(stmt,
                                            0); ///Atentie ca asta cred ca retureaza mereu 0 si daca pun callnack-ul
            if (exists == 0) {
                fprintf(stderr, "Cannot find the user: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return FriendRequest(-3, -3, "Error User Doesn't Exists", "Error", false);
            } else  ///Am gasit userul
            {
            */
        string sqlVerif = "SELECT accepted,type FROM FriendRequest WHERE id1 = FriendRequest.id1 AND id2=FriendRequest.id2";
        rc = sqlite3_exec(db, sqlVerif.c_str(), 0, 0, &err_msg);
        if (rc != SQLITE_OK) {

            fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return FriendRequest(-5, -5, "Error using select", false);

        } else {
            int accept= sqlite3_column_int(stmt,0);
            const unsigned char *types = sqlite3_column_text(stmt, 1);
            std::string type;
            bool accepted;
            /*
                   type = types;    /// REINTERPRET_CAST TRB SA-I DAU
                   accepted  = bool(accept);
          */
            cout << "FriendRequest Getted!" << '\n';
            return FriendRequest(id1,id2,type,accepted);
        }
    }

    int updateFriendRequest( FriendRequest friendRequest){
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

        /// Aici trebuie sa vad daca exista utilizatorul meu. Altfel returnez iar cv
        /*
            string sqlVerif="SELECT EXISTS(SELECT type,accepted FROM FriendRequest WHERE id1 = friendRequest.id1 AND id2=friendRequest.id2)"; //

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
        ///AICI FAC SET-UL   ; l comment i am pus strig sqlVerif si la rc am scus int rc.
        string sqlVerif = "UPDATE FriendRequest SET accepted = friendRequest.accepted , type = friendRequest.type  WHERE friendRequest.id1 = FriendRequest.id1 AND friendRequest.id2 = FriendRequest.id2";
        rc = sqlite3_exec(db, sqlVerif.c_str(), 0, 0, &err_msg); ///Callback
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Set comand doesn t work on friendRequest: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;

        } else {
            cout << "FriendRequest Updated" << '\n';
            return 1;
        }
    }

    int deleteFriendRequest( int id1,int id2){

        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); //aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK)
        {

            fprintf(stderr, "Cannot open database on delete message: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        /// Aici trebuie sa vad daca exista utilizatorul meu. Altfel returnez iar cv

        string sqlVerif="SELECT EXISTS(SELECT id1,id2 FROM FriendRequest WHERE FriendRequest.id1 = id1 AND FriendRequest.id2=id2)";

        rc = sqlite3_exec(db,sqlVerif.c_str(),0,0,&err_msg);
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
        sqlVerif = "DELETE FROM FriendRequest WHERE id1 = FriendRequest.id1 AND id2 = FriendRequest.id2";   ///Atentie trebuia users (corrected)
        rc = sqlite3_exec(db,sqlVerif.c_str(),0,0,&err_msg);
        if(rc!=SQLITE_OK)
        {
            fprintf(stderr, "Delete comand doesn t work: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;

        }
        else
        {
            cout<<"FriendRequest deleted"<<'\n';
            return 1;

        }
    }

};
#endif //SOCIALMEDIA_HANDLERFRIENDREQUEST_H
