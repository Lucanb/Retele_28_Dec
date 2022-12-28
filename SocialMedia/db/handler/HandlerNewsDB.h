//
// Created by lolluckestar on 15.12.2022.
//

#ifndef SOCIALMEDIA_HANDLERNEWSDB_H
#define SOCIALMEDIA_HANDLERNEWSDB_H

#include "../../models/News.h"
#include<iostream>
#include<string>
//#include"GlobalFunction.h"

using namespace std;


struct HandlerNewsDB {

    HandlerNewsDB() = default;

    int createNews(
            struct News news
    ) {
        sqlite3 *db;
        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); //aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot open database on insert news: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

///Aici authorID nu stiu daca trebuie inserat.

        string sqlQuery = "INSERT INTO News (authorId,title,content,type) VALUES(" + to_string(news.authorId) + "," +
                          "\'" + news.title + "\'," +
                          "\'" + news.content + "\'," +
                          "\'" + news.type + "\')";

///NU SUNT SIGUR DACA TREBUIE SA TESTEZ UNICITATEA ALTUI TITLU DE STIRE PT ACELASI AUTOR

        rc = sqlite3_exec(db, sqlQuery.c_str(), 0, 0, &err_msg);
        if (rc != SQLITE_OK) {

            fprintf(stderr, "SQL error on insert user: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            return 0;
        } else {
            sqlite3_close(db);
            cout << "News Inserted" << '\n';
            return 1;
        }
    }

    News getNews(int id,int authorId) {

        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); //aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on get news: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return News(-1, -1, "Error Open Data Base", "Error", "Error");
        }

        /// Aici trebuie sa vad daca exista utilizatorul meu. Altfel returnez iar cv ; trb rez ca la userHandler
/*
        string sqlVerif = "SELECT EXISTS(SELECT id FROM News WHERE id = news.id)"; //

        rc = sqlite3_exec(db, sqlVerif.c_str(), 0, 0, &err_msg);
        ///Ar trb in loc de 0 sa bag si functia callback ca sa iau din acel select cv

/// Test : nu prea e oke
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot use existance select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return News(-2, -2, "Error at SELECT EXISTANCE", "Error", "Error");
        } else {
            int exists = sqlite3_column_int(stmt,
                                            0); ///Atentie ca asta cred ca retureaza mereu 0 si daca pun callnack-ul
            if (exists == 0) {
                fprintf(stderr, "Cannot find the user: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return News(-3, -3, "Error User Doesn't Exists", "Error", "Error");
            } else  ///Am gasit userul
            {
            */
        string sqlVerif = "SELECT title,content,type FROM News WHERE id = news.id AND authorId=news.authorId";
        rc = sqlite3_exec(db, sqlVerif.c_str(), 0, 0, &err_msg);
        if (rc != SQLITE_OK) {

            fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return News(-5, -5, "Error using select", "Error", "Error");

        } else {
            const unsigned char *titles = sqlite3_column_text(stmt, 0);
            const unsigned char *contents = sqlite3_column_text(stmt, 1);
            const unsigned char *types = sqlite3_column_text(stmt, 2);
            std::string title;
            std::string content;
            std::string type;
            /*
                      /// REINTERPRET_CAST TRB SA-I DAU
                   std::string title  = titles;
                   std::string content = contents;
                   std::string type  = types;


         */
            cout << "News Getted!" << '\n';
            return News(id,authorId,title,content,type);
        }
    }
    //   }
    //}

    int updateNews(News news)
    {
        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); //aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on update news: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        /// Aici trebuie sa vad daca exista utilizatorul meu. Altfel returnez iar cv
        /*
            string sqlVerif="SELECT EXISTS(SELECT id,authorId FROM News WHERE id = a.id AND authorId=a.authorId)"; //

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
                    string sqlVerif = "UPDATE News SET title = news.title , content = news.content , type = news.type WHERE news.id = News.id AND news.authorId=News.authorId";
                    rc = sqlite3_exec(db, sqlVerif.c_str(), 0, 0, &err_msg); ///Callback
                    if (rc != SQLITE_OK) {
                        fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
                        sqlite3_close(db);
                        return 0;

                    } else {
                        cout << "News Updated!" << '\n';
                        return 1;
                    }
    }
    //  }
//}
    int deleteNews(int id,int authorId) {

        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); //aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK)
        {

            fprintf(stderr, "Cannot open database on delete news: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        /// Aici trebuie sa vad daca exista utilizatorul meu. Altfel returnez iar cv

        string sqlVerif="SELECT EXISTS(SELECT id,authorId FROM Users WHERE News.id = id AND News.authorId=authorId)";

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
        sqlVerif = "DELETE FROM News WHERE id = News.id AND authorId=News.authorId";   ///Atentie trebuia users (corrected)
        rc = sqlite3_exec(db,sqlVerif.c_str(),0,0,&err_msg);
        if(rc!=SQLITE_OK)
        {
            fprintf(stderr, "Delete comand doesn t work: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;

        }
        else
        {
            cout<<"News Deleted!"<<'\n';
            return 1;

        }

    }

};

#endif //SOCIALMEDIA_HANDLERNEWSDB_H
