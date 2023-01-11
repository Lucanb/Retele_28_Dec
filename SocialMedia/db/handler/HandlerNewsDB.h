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

        int rc = sqlite3_open("db/mydb.db", &db);

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

   vector<string> getNewsLoggedByTitle(string title,string id1)
   {
       vector<string> collect;
       sqlite3 *db;
       sqlite3_stmt *stmt;

       char *err_msg = 0;
       sqlite3_stmt *res;

       int rc = sqlite3_open("db/mydb.db", &db);

       if (rc != SQLITE_OK) {

           fprintf(stderr, "Cannot open database on get news: %s\n", sqlite3_errmsg(db));
           sqlite3_close(db);
           collect.push_back("fail");
           return collect;
       }

       vector<int> verif;

       string sqlVerif1="SELECT authorId from News WHERE title LIKE" + string("\'")+"%"+ title + "%" +string("\'");
       string sqlAlltypes = "SELECT type from News WHERE title LIKE" + string("\'")+"%"+ title + "%" +string("\'");
       rc = sqlite3_exec(db, sqlVerif1.c_str(), callback, 0, &err_msg);
       if(rc != SQLITE_OK)
       {
           fprintf(stderr, "Cannot Verify authorID: %s\n", sqlite3_errmsg(db));
           sqlite3_close(db);
           collect.push_back("fail");
           return collect;
       }
       int rc2 = sqlite3_exec(db, sqlAlltypes.c_str(), callback2, 0, &err_msg);
       if(rc2 != SQLITE_OK)
       {
           fprintf(stderr, "Cannot Verify author type: %s\n", sqlite3_errmsg(db));
           sqlite3_close(db);
           collect.push_back("fail");
           return collect;
       }

       vector<string> allId;
       parsing(returningStr,allId);

       vector<string>allTypes;
       parsing(returningStr2,allTypes);
///Asta daca e private;
       for(int i=0;i<allId.size();i++) {
           string sqlVerif2 = "SELECT type from Friend WHERE id1=" + id1
                   + " AND" + "id2=" + allId[i] ;
           rc= sqlite3_exec(db,sqlVerif2.c_str(), callback2,0,&err_msg);
           if(rc!=SQLITE_OK)
           {
               fprintf(stderr, "Error in or finding if those 2 are friends: %s\n", sqlite3_errmsg(db));
               sqlite3_close(db);
               collect.push_back("fail");
               return collect;
           }
           else
           {
                  vector<string> stype;
                  parsing(returningStr2,stype);
                  if(stype.size() == 1) {
                      if (stype[0] == "private") {
                          verif.push_back(1);
                      } else {
                          verif.push_back(1);
                      }
                  }
                  else
                  { //daca e publica stirea acum;
                      if(allTypes[i] == "public")
                      {
                          verif.push_back(1);
                      }
                      else
                      {
                          verif.push_back(0);
                      }
                  }
           }
       }

        ///Verificarea daca s prieteni ; daca nu s; nu avem acces;

               string sqlQuery =
               "SELECT content FROM News WHERE title LIKE" +string("\'")+"%"+ title + "%" +string("\'");  //

       rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);

       if (rc != SQLITE_OK) {
           fprintf(stderr, "Cannot use existance of title: %s\n", sqlite3_errmsg(db));
           sqlite3_close(db);
           collect.push_back("fail");
           return collect;
       } else {
           vector<string> s;
           cout<<returningStr;
           parsing(returningStr, s);
           if(s.size() != 0) {
               for (int i = 0; i < s.size(); i++) {
                   if(verif[i] == 1) {
                       string copy = title + "\n" + s[i] + "\n";
                       collect.push_back(copy);
                   }
               }
               return collect;
           }
           else {
               cout << "Doesn t exist a refference \n";
               collect.push_back("fail");
           }
       }
   }

    vector<string>
    getNewsByTitle(string title) //In asta pun la inceput de text Numele autorului din Users si dupa descriere + data
    {                                           //Si astea vor fi pe o pozitie din vectorul meu.
        vector<string> collect;
        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("db/mydb.db", &db);

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on get news: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            collect.push_back("fail");
            return collect;
        }

        string sqlQuery =
                "SELECT content FROM News WHERE title LIKE" +string("\'")+"%"+ title + "%" +string("\'") + " AND " +
                "type =" + string("\'") + "public" + string("\'");  //

        rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot use existance of title: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            collect.push_back("fail");
            return collect;
        } else {
                  vector<string> s;
                  cout<<returningStr;
                  parsing(returningStr, s);
                  if(s.size() != 0) {
                      for (int i = 0; i < s.size(); i++) {
                          string copy = title + "\n" + s[i] + "\n";
                          collect.push_back(copy);
                      }
                      return collect;
                  }
                  else {
                      cout << "Doesn t exist a refference \n";
                      collect.push_back("fail");
                  }
                }
    }

    News getNews(int id, int authorId) {

        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("db/mydb.db", &db);

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
            } else /// Am gasit userul
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

        int rc = sqlite3_open("db/mydb.db", &db);

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
                              " , content = " + string("\'") + news.content + string("\'") + " , type = " +
                              string("\'") + news.type + string("\'") + " WHERE id = " + to_string(news.id) +
                              " AND authorId = " + to_string(news.authorId);
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

        int rc = sqlite3_open("db/mydb.db", &db);

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on delete news: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        string sqlVerif = "SELECT id , authorId FROM News WHERE id =" + to_string(id) + " AND authorId =" +
                          to_string(authorId);

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
                sqlVerif = "DELETE FROM News WHERE id =" + to_string(id) + " AND authorId = " +
                           to_string(authorId); /// Atentie trebuia users (corrected)
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
