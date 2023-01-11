//
// Created by lolluckestar on 15.12.2022.
//

#ifndef SOCIALMEDIA_HANDLERMESSAGEDB_H
#define SOCIALMEDIA_HANDLERMESSAGEDB_H

#include "../../models/Message.h"
#include<iostream>
#include<string>
#include"GlobalFunction.h"
#include "../../models/Chat.h"
#include "HandlerChatDB.h"

using namespace std;

struct HandlerMessageDB {

    HandlerMessageDB() = default;

    int createMessage(
            Message message
    ) {
        sqlite3 *db;
        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("db/mydb.db", &db);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot open database on insert message: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        string sqlVerif = "Select id from Message WHERE id=" + to_string(message.id);

        string sqlQuery = "INSERT INTO Message (chatId,date,message) VALUES(" + to_string(message.chatId) + "," +
                          "\'" + message.date + "\'," +
                          "\'" + message.message + "\')";
        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Can't verify if the id exists on message: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            return 0;
        } else {
            vector<string> s;
            parsing(returningStr, s);
            if (s.size() != 0) {
                fprintf(stderr, "This Message doesn't Creeate because the id exists: %s\n", err_msg);
                sqlite3_free(err_msg);
                sqlite3_close(db);
                return 0;
            } else {
                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
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
        }
    }

    vector<string> getMessageAfterName(string name)
    {
        sqlite3 *db;
        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("db/mydb.db", &db);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot open database on insert message: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            vector<string> s;
            s.push_back("fail");
            return s;
        }

        int idd;

        string sqlVerif1="SELECT idChat FROM Chat WHERE title = " + string("\'") + name +string("\'");
        rc = sqlite3_exec(db, sqlVerif1.c_str(), callback, 0, &err_msg);
        if(rc!=SQLITE_OK)
        {
            fprintf(stderr, "Cannot use first select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            vector<string> s;
            s.push_back("fail");
            return s;
        }
        vector<string>sp;
        parsing(returningStr,sp);

       if(sp.size() != 0) {
           idd = stoi(sp[0]);
           string sqlVerif = "SELECT message FROM MESSAGE WHERE chatId=" + to_string(idd);
           rc = sqlite3_exec(db, sqlVerif1.c_str(), callback, 0, &err_msg);
           if(rc!=SQLITE_OK)
           {
               fprintf(stderr, "Cannot use first select: %s\n", sqlite3_errmsg(db));
               sqlite3_close(db);
               vector<string> s;
               s.push_back("fail");
               return s;
           }
           vector<string>sp;
           parsing(returningStr,sp);
           return sp;
       }
       else
       {
           fprintf(stderr, "My title doesn't exists %s\n", sqlite3_errmsg(db));
           sqlite3_close(db);
           vector<string> s;
           s.push_back("fail");
           return s;
       }
    }

    Message getMessage(int id, int chatId) {

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


        string sqlVerif =
                "SELECT id,chatId FROM Message WHERE id =" + to_string(id) + " AND chatId =" + to_string(chatId);

        rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);


        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot use existance select: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return Message(-2, -2, "Error at SELECT EXISTANCE", "Error");
        } else {
            vector<string> s;
            parsing(returningStr, s);
            if (s.size() == 0) {
                fprintf(stderr, "Cannot find the user: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return Message(-3, -3, "Error User Doesn't Exists", "Error");
            } else {

                string sqlQuery = "SELECT date,message FROM Message WHERE id =" + to_string(id) + " AND chatId =" +
                                  to_string(chatId);
                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                if (rc != SQLITE_OK) {

                    fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return Message(-5, -5, "Error using select", "Error");

                } else {
                    vector<string> s;
                    parsing(returningStr, s);

                    std::string date = s[0];
                    std::string message = s[1];

                    cout << "Message Getted!" << '\n';
                    return Message(id, chatId, date, message);
                }
            }
        }
    }

    int updateMessage(Message message) {
        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("db/mydb.db", &db);

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on update Message: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }


        string sqlVerif = "SELECT id,chatId FROM Message WHERE id =" + to_string(message.id) + " AND chatId = " +
                          to_string(message.chatId); //

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

                string sqlQuery = "UPDATE Message SET date = " + string("\'") + message.date + string("\'") +
                                  " , message = " + string("\'") + message.message + string("\'") + "WHERE id = "
                                  + to_string(message.id) + " AND chatId= " + to_string(message.chatId);
                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                if (rc != SQLITE_OK) {
                    fprintf(stderr, "Set comand doesn t work on message: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;

                } else {
                    cout << "Message Updated" << '\n';
                    return 1;
                }
            }
        }
    }

    int SentMessage(Message message, string title, vector<string> UserNames, string loggedId) {
        sqlite3 *db;
        sqlite3_stmt *stmt;
        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("db/mydb.db", &db);

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on Send Message: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        Chat chat;
        ///Prima data Creez Mesajul cu chatId default ; Utilizatorul meu nu are voie sa fie pe chaturi cu acelasi titlu.
        int a = createMessage(message);
        if (a == 0) {
            fprintf(stderr, "Could not Creeate our Message \n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        } else {
            vector<int> SaveId;
            vector<int> SaveMessage;
            ///Iau id-ul mesajului

            string sqlIdQuerry = "SELECT id FROM Message WHERE message=" + string("\'") + message.message + string("\'")
                                 + " AND" " date =" + message.date;
            rc = sqlite3_exec(db, sqlIdQuerry.c_str(), callback, 0, &err_msg);
            if (rc != SQLITE_OK) {
                fprintf(stderr, "Select id from message \n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return 0;
            }
            vector<string> str;
            parsing(returningStr, str);

            int myid = stoi(loggedId);
            chat.idList.push_back(myid);


            string MyID = "";
            int myMessageId;
            if (str.size() != 0) {
                myMessageId = stoi(str[0]);
            } else {
                fprintf(stderr, "Select id from message doesn t exist\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return 0;
            }
            string MYMESS = "";

            chat.idMessages.push_back(myMessageId);
            SaveMessage = chat.idMessages;

            ///Sub FOR :
            for (int i = 1; i < UserNames.size(); i++) {
                string sqlVerif = "Select id FROM Users WHERE userName=" + string("\'") + UserNames[i] + string("\'");
                rc = sqlite3_exec(db, sqlVerif.c_str(), callback, 0, &err_msg);

                if (rc != SQLITE_OK) {
                    fprintf(stderr, "Cannot find a user with that userName %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;
                }
                vector<string> sub;//scot myid
                parsing(returningStr, sub);
                if (sub.size() != 0) {
                    myid = stoi(sub[0]);
                } else {
                    fprintf(stderr, " A user with that userName doesn't exist%s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;
                }

                chat.idList.push_back(myid);
                SaveId.push_back(myid);
            }
            chat.title = title;

            for (auto it = SaveMessage.begin(); it != SaveMessage.end(); it++) {
                if (it != SaveMessage.begin()) {
                    MyID += "";
                }
                MyID += to_string(*it);
            }
            //cout<<strMessages<<'\n';

            for (auto it = MyID.begin(); it != MyID.end(); it++) {
                if (it != MyID.begin()) {
                    MyID += "";
                }
                MyID += to_string(*it);
            }

            string sqlQueue = "SELECT id FROM Chat Where idList=" + string("\'") + MyID + string("\'") + " AND"
                              + " title =" + string("\'") + title + string("\'"); //Am scos id ul chatului;

            rc = sqlite3_exec(db, sqlQueue.c_str(), callback, 0, &err_msg);
            if (rc != SQLITE_OK) {
                fprintf(stderr, " Can't acces that Chat %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return 0;
            }
            vector<string> parsare;
            parsing(returningStr, parsare);
            if (parsare.size() == 0) {
                HandlerChatDB handler;
                handler.CreateChat(chat); /// acum am creeat chat ul

                string sqlQueue = "SELECT id FROM Chat Where idList=" + string("\'") + MyID + string("\'") + " AND"
                                  + " idMessages=" + string("\'") + MYMESS + string("\'"); //Am scos id ul chatului;

                rc = sqlite3_exec(db, sqlQueue.c_str(), callback, 0, &err_msg);
                if (rc != SQLITE_OK) {
                    fprintf(stderr, " Can't acces that Chat %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;
                }

                vector<string> parsare2;
                parsing(returningStr, parsare2);

                int idChat = stoi(parsare2[0]);

                message.chatId = idChat;
                int b = updateMessage(message);
                if (b == 1) {
                    cout << "Succsesful added Message and Chat ! \n";
                    return 1;
                } else {
                    fprintf(stderr, "Could not Update our Message \n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;
                }
            } else {
                HandlerChatDB handler;
                handler.updateChat(chat);
                int idChat = stoi(parsare[0]);

                message.chatId = idChat;
                int b = updateMessage(message);
                if (b == 1) {
                    cout << "Succsesful added Message and Chat ! \n";
                    return 1;
                } else {
                    fprintf(stderr, "Could not Update our Message \n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;
                }
            }

        }
    }

    int deleteMessage(int id, int chatId) {
        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("db/mydb.db", &db);

        if (rc != SQLITE_OK) {

            fprintf(stderr, "Cannot open database on delete message: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        string sqlVerif =
                "SELECT id,chatId FROM Message WHERE id =" + to_string(id) + " AND chatId =" + to_string(chatId);

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

                string sqlQuery =
                        "DELETE FROM Message WHERE id = " + to_string(id) + " AND chatId = " + to_string(chatId);
                rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &err_msg);
                if (rc != SQLITE_OK) {
                    fprintf(stderr, "Delete comand doesn t work: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 0;

                } else {
                    cout << "Message deleted" << '\n';
                    return 1;

                }
            }
        }
    }

};

#endif //SOCIALMEDIA_HANDLERMESSAGEDB_H
