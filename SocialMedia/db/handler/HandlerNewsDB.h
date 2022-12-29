//
// Created by lolluckestar on 15.12.2022.
//
#pragma once
#ifndef SOCIALMEDIA_HANDLERNEWSDB_H
#define SOCIALMEDIA_HANDLERNEWSDB_H

#include "GlobalFunction.h"
#include "../../models/News.h"
#include <iostream>
#include <string>


using namespace std;

struct HandlerNewsDB {

    HandlerNewsDB() = default;

    int createNews(
            struct News news) {
        sqlite3 *db;
        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot open database on insert news: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        string sqlQuery = "INSERT INTO News (authorId,title,content,type) VALUES(" + to_string(news.authorId) + "," +
                          "\'" + news.title + "\'," +
                          "\'" + news.content + "\'," +
                          "\'" + news.type + "\')";


        rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
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

    News getNews(int id, int authorId) {

        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db);

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on get news: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return News(-1, -1, "Error Open Data Base", "Error", "Error");
        }


        string sqlVerif =
                "SELECT id,authorId FROM News WHERE id =" + to_string(id) + " AND authorId=" + to_string(authorId); //

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot use existance select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return News(-2, -2, "Error at SELECT EXISTANCE", "Error", "Error");
        } else {
            vector<string> s;
            parsing(returningStr, s);
            cout << s.size();
            if (s.size() == 0) {
                fprintf(stderr, "Cannot find the user: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return News(-3, -3, "Error User Doesn't Exists", "Error", "Error");
            } else  ///Am gasit userul
            {

                string sqlQuery = "SELECT title,content,type FROM News WHERE id =" + to_string(id) + " AND authorId=" +
                                  to_string(authorId);
                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                vector<string> s;
                parsing(returningStr, s);
                if (rc != SQLITE_OK) {

                    fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return News(-5, -5, "Error using select", "Error", "Error");
                } else {
                    std::string title = s[0];
                    std::string content = s[1];
                    std::string type = s[2];

                    cout << "News Getted!" << '\n';
                    return News(id, authorId, title, content, type);
                }
            }
        }
    }

    int updateNews(News news) {
        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db);

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on update news: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }


        string sqlVerif = "SELECT id,authorId FROM News WHERE id =" + to_string(news.id) + " AND authorId=" +
                          to_string(news.authorId);

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

            }
            string sqlQuery = "UPDATE News SET title = " + string("\'") + news.title + string("\'") +
                              " , content = " + string("\'") + news.content + string("\'") + " , type = " + string("\'")
                              + news.type + string("\'") + " WHERE id = " + to_string(news.id) + " AND authorId = "
                              + to_string(news.authorId);
            rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
            if (rc != SQLITE_OK) {
                fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return 0;
            } else {
                cout << "News Updated!" << '\n';
                return 1;
            }
        }

    }

    int deleteNews(int id, int authorId) {

        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db);

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on delete news: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        string sqlVerif = "SELECT id , authorId FROM News WHERE id =" + to_string(id) + " AND News.authorId =" +
                          to_string(authorId);

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot check id existance select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        } else {
                vector<string> s;
                parsing(returningStr,s);
                if (s.size() == 0) {
                fprintf(stderr, "Cannot find the id: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return 0;
            } else
            {
                    sqlVerif = "DELETE FROM News WHERE id =" + to_string(id) + " AND authorId = " + to_string(authorId); /// Atentie trebuia users (corrected)
                rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);
                if (rc != SQLITE_OK) {
                    fprintf(stderr, "Delete comand doesn t work: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;
                } else {
                    cout << "News Deleted!" << '\n';
                    return 1;
                }
            }
        }
    }
};

#endif // SOCIALMEDIA_HANDLERNEWSDB_H
