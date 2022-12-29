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

    HandlerMessageDB()=default;

    int createMessage(
           Message message
    ) {
        sqlite3 *db;
        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); //aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot open database on insert message: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

///chatId nu sunt sigur daca trb inserat.

        string sqlQuery = "INSERT INTO Message (chatId,date,message) VALUES(" + to_string(message.chatId) + "," +
                          "\'" + message.date + "\'," +
                          "\'" + message.message + "\')";


        rc = sqlite3_exec(db, sqlQuery.c_str(), 0, 0, &err_msg);
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

    Message getMessage(int id,int chatId) {

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

        /// Aici trebuie sa vad daca exista utilizatorul meu. Altfel returnez iar cv ; trb rez ca la userHandler
/*
        string sqlVerif = "SELECT EXISTS(SELECT id,chatId FROM Message WHERE id = Message.id AND chatId=Message.chatId)"; //

        rc = sqlite3_exec(db, sqlVerif.c_str(), 0, 0, &err_msg);
        ///Ar trb in loc de 0 sa bag si functia callback ca sa iau din acel select cv

/// Test : nu prea e oke
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot use existance select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return Message(-2, -2, "Error at SELECT EXISTANCE", "Error", "Error");
        } else {
            int exists = sqlite3_column_int(stmt,
                                            0); ///Atentie ca asta cred ca retureaza mereu 0 si daca pun callnack-ul
            if (exists == 0) {
                fprintf(stderr, "Cannot find the user: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return Message(-3, -3, "Error User Doesn't Exists", "Error", "Error");
            } else  ///Am gasit userul
            {
            */
        string sqlVerif = "SELECT date,message FROM Message WHERE id = Message.id AND chatId=Message.chatId";
        rc = sqlite3_exec(db, sqlVerif.c_str(), 0, 0, &err_msg);
        if (rc != SQLITE_OK) {

            fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return Message(-5, -5, "Error using select", "Error");

        } else {
            const unsigned char *dates = sqlite3_column_text(stmt, 0);
            const unsigned char *messages = sqlite3_column_text(stmt, 1);
            string date;
            string message;
            /*
                   std::string date  = dates;
                   std::string message = messages;
           */

            cout << "Message Getted!" << '\n';
            return Message(id,chatId,date,message);
        }
    }

    int updateMessage(Message message){
        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); //aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on update Message: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        /// Aici trebuie sa vad daca exista utilizatorul meu. Altfel returnez iar cv
        /*
            string sqlVerif="SELECT EXISTS(SELECT id,authorId FROM Message WHERE id = message.id AND chatId=message.chatId)"; //

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
        string sqlVerif = "UPDATE Message SET date = message.date , message = message.message  WHERE message.id = Message.id AND message.chatId=Message.chatId";
        rc = sqlite3_exec(db, sqlVerif.c_str(), 0, 0, &err_msg); ///Callback
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Set comand doesn t work on message: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;

        } else {
            cout << "Message Updated" << '\n';
            return 1;
        }
    }

    int deleteMessage( int id,int chatId){
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

        string sqlVerif="SELECT EXISTS(SELECT id FROM Message WHERE Message.id = id)";

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
        sqlVerif = "DELETE FROM Message WHERE id = Message.id AND chatId=Message.chatId";   ///Atentie trebuia users (corrected)
        rc = sqlite3_exec(db,sqlVerif.c_str(),0,0,&err_msg);
        if(rc!=SQLITE_OK)
        {
            fprintf(stderr, "Delete comand doesn t work: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;

        }
        else
        {
            cout<<"Message deleted"<<'\n';
            return 1;

        }

    }

};

#endif //SOCIALMEDIA_HANDLERMESSAGEDB_H
