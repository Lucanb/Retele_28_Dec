//
// Created by lolluckestar on 15.12.2022.
//

#ifndef SOCIALMEDIA_HANDLERCHATDB_H
#define SOCIALMEDIA_HANDLERCHATDB_H

#include"../../models/Chat.h"
#include<iostream>
#include<string>
#include <sstream>
//#include"GlobalFunction.h"

using namespace std;


struct HandlerChatDB {

    HandlerChatDB()=default;


    int CreateChat(Chat chat) {
        sqlite3 *db;
        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); //aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot open database on insert Chat: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

///chatId nu sunt sigur daca trb inserat.
          ///Aici trebuie conversie din vector<int> in string:
           string strMessages;
           string strId;

        for(auto it =chat.idMessages.begin();it!=chat.idMessages.end();it++)
        {
            if(it != chat.idMessages.begin())
            {
               strMessages+="";
            }
            strMessages+= to_string(*it);
        }

        for(auto it =chat.idList.begin();it!=chat.idList.end();it++)
        { if(it != chat.idList.begin())
            {
              strId+="";
            }
            strId+=to_string(*it);
        }

     ///GATA Conversia si acum pot insera linistit.

        string sqlQuery = "INSERT INTO Chat (idList,idMessages,title) VALUES(" + strMessages + "," +
                          "\'" + strId + "\'," +
                          "\'" + chat.title + "\')";


        rc = sqlite3_exec(db, sqlQuery.c_str(), 0, 0, &err_msg);
        if (rc != SQLITE_OK) {

            fprintf(stderr, "SQL error on create Chat: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            return 0;
        } else {
            sqlite3_close(db);
            cout << "Chat Inserted" << '\n';
            return 1;
        }

    }

    Chat getChat(int idChat)
    {
        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); //aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on get Chat: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            vector<int>v1,v2;
            string s="Error";
            return Chat(-1,v1,v2,s);
        }

        /// Aici trebuie sa vad daca exista utilizatorul meu. Altfel returnez iar cv ; trb rez ca la userHandler
/*
        string sqlVerif = "SELECT EXISTS(SELECT idChat FROM Chat WHERE idChat = Chat.idChat)";

        rc = sqlite3_exec(db, sqlVerif.c_str(), 0, 0, &err_msg);
        ///Ar trb in loc de 0 sa bag si functia callback ca sa iau din acel select cv

/// Test : nu prea e oke
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot use existance select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            vector<int v1,v2>
            return Chat(-2, v1, v2, "Error at selection existance");
        } else {
            int exists = sqlite3_column_int(stmt,
                                            0); ///Atentie ca asta cred ca retureaza mereu 0 si daca pun callnack-ul
            if (exists == 0) {
                fprintf(stderr, "Cannot find the user: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return Chat(-3, v1, v2, "Error at existance");
            } else
            {
            */
        string sqlVerif = "SELECT idList,idMessages,title FROM Chat WHERE idChat = Chat.idChat";
        rc = sqlite3_exec(db, sqlVerif.c_str(), 0, 0, &err_msg);
        if (rc != SQLITE_OK) {

            fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            vector<int>v1,v2;
            string s="Error";
            return Chat(-3,v1,v2,s);

        } else {
            vector<int>v1,v2;
            const unsigned char *idLists = sqlite3_column_text(stmt, 0);
            const unsigned char *idMess  = sqlite3_column_text(stmt, 1);
            const unsigned char *titles  = sqlite3_column_text(stmt, 2);

            std::string idList;
            std::string idMessages;
            std::string title;

            /*
                   idList = idLists;    /// REINTERPRET_CAST TRB SA-I DAU
                   idMessages = idMess;
                   title = titles;

                   ///Start Coversion from string to vector<int> :

                            std::stringstream iss( idList );
                            std::stringstream iss2(idMessages);
                            int number;
                            while ( iss >> number )
                            v1.push_back( number );

                            while ( iss2 >> number )
                            v2.push_back( number );
                */
                   return Chat(idChat,v1,v2,title);

            cout << "Chat getted!" << '\n';
        }

    }

    int updateChat(Chat chat) {
        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); //aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on update Chat: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        /// Aici trebuie sa vad daca exista utilizatorul meu. Altfel returnez iar cv
        /*
            string sqlVerif="SELECT EXISTS(SELECT idChat FROM Chat WHERE idChat = Chat.idChat)"; //

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

        ///Problem : Sa fac conversia din vector<int> in string
        string strMessages;
        string strId;

        for(auto it =chat.idMessages.begin();it!=chat.idMessages.end();it++)
        {
            if(it != chat.idMessages.begin())
            {
                strMessages+="";
            }
            strMessages+= to_string(*it);
        }

        for(auto it =chat.idList.begin();it!=chat.idList.end();it++)
        { if(it != chat.idList.begin())
            {
                strId+="";
            }
            strId+=to_string(*it);
        }

///Aici ar trb alea convertite dar cred ca e alta pb(mai jos merge ca face chat ca fiind tabela nu oiectul meu)

        string sqlVerif = "UPDATE Chat SET idList = chat.idList , idMessages = chat.idMessages , title = chat.title WHERE chat.idChat = Chat.idChat";
        rc = sqlite3_exec(db, sqlVerif.c_str(), 0, 0, &err_msg); ///Callback
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Set comand doesn t work on Chat: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;

        } else {
            cout << "Chat Updated" << '\n';
            return 1;
        }
    }

    int deleteChat(int idChat)
    {
        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); //aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK)
        {

            fprintf(stderr, "Cannot open database on Chat : %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        /// Aici trebuie sa vad daca exista utilizatorul meu. Altfel returnez iar cv

        string sqlVerif="SELECT EXISTS(SELECT idChat FROM Chat WHERE Chat.idChat = idChat )";

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
        sqlVerif = "DELETE FROM Chat WHERE idChat = Chat.idChat";   ///Atentie trebuia users (corrected)
        rc = sqlite3_exec(db,sqlVerif.c_str(),0,0,&err_msg);
        if(rc!=SQLITE_OK)
        {
            fprintf(stderr, "Delete comand doesn t work: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }
        else
        {
            cout<<"Chat deleted"<<'\n';
            return 1;

        }
    }

};


#endif //SOCIALMEDIA_HANDLERCHATDB_H
