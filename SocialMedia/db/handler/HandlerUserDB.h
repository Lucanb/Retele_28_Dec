//
// Created by lolluckestar on 11.12.2022.
//

#ifndef SOCIALMEDIA_HANDLERUSERDB_H
#define SOCIALMEDIA_HANDLERUSERDB_H

#include "../../models/User.h"
#include "../../db/mydb/sqlite3.h"
#include <iostream>
#include <string>
using namespace std;

struct HandlerUserDB
{

    HandlerUserDB() = default;

    static string callback(void *data, int argc, char **argv, char **azColName)
    {
        int i;
        fprintf(stderr, "%s: ", (const char *)data);
        string returningStr = "";
        for (i = 0; i < argc; i++)
        {
            returningStr += azColName[i];
            returningStr += "=";
            returningStr += argv[i] ? argv[i] : "NULL";
            returningStr += "\n";

            // printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        }
        return returningStr;

        printf("\n");
        return "";
    }

    int createUser(
        struct User user)
    {
        // Incercare_nu stiu daca asa trebuie sau e cv asemanator

        sqlite3 *db;
        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); // aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK)
        {

            fprintf(stderr, "Cannot open database on insert user: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);

            return 0;
        }

        // TODO: VERIFICA DACA USERNAME-ul nu e luat
        // HINT: faci un select pt username-ul ales si daca count-ul pe select e mai mare de 0, atunci e luat

        string sqlVerif = "SELECT count(*) WHERE EXISTS(SELECT userName FROM Users WHERE userName = users.userName)"; // aici trebuia doar val de user. nu users

        string sqlQuery = "INSERT INTO Users (isAdmin,userName,firstname,lastname,birthday,accountCreationDate,profileDescription) VALUES(" + to_string(user.isAdmin) + "," +
                          "\'" + user.userName + "\'," +
                          "\'" + user.firstname + "\'," +
                          "\'" + user.lastname + "\'," +
                          "\'" + user.birthday + "\'," +
                          "\'" + user.accountCreationDate + "\'," +
                          "\'" + user.profileDescription + "\')";

        rc = sqlite3_exec(db, sqlVerif.c_str(), 0, 0, &err_msg); // ar trbui sa pun acel callback
        // Cam asa ar trb   rc =sqlite3_exec(db,sqlVerif.c_str(),callback,0,&err_msg);

        if (rc != SQLITE_OK) // Ca practice la userName nu stiu daca e oke aici.
        {
            fprintf(stderr, "Select doesn't work %s\n", err_msg);
            return 0;
        }
        else
        {
            int selectUser;
            selectUser = sqlite3_column_int(res, 0);
            if (selectUser == 0)
            {

                rc = sqlite3_exec(db, sqlQuery.c_str(), 0, 0, &err_msg);
                if (rc != SQLITE_OK)
                {

                    fprintf(stderr, "SQL error on insert user: %s\n", err_msg);

                    sqlite3_free(err_msg);
                    sqlite3_close(db);
                    return 0;
                }
                else
                {
                    cout << "User Created!" << '\n';
                    return 1;
                }
            }
            else
            {
                fprintf(stderr, "SQL error on user already exists: %s\n");
                sqlite3_close(db);
                return 0;
            }
        }
        sqlite3_close(db);
        cout << "User Created" << '\n';
        return 1;
    }
    /*
        functia primeste ca parametru un id
        faci select in Users table unde id=id
        rezultatul il parsezi si il pui intr-un User struct si il returnezi
        daca da fail, returnezi un user empty
    */

    User getUser(int id)
    {

        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); // aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK)
        {

            fprintf(stderr, "Cannot open database on get user: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return User(-1, -1, "Error Open Data Base", "Error", "Error", "Error", "Error", "Error");
        }

        /// Aici trebuie sa vad daca exista utilizatorul meu. Altfel returnez iar cv

        string sqlVerif = "SELECT EXISTS(SELECT id FROM Users WHERE id=" + to_string(id) + ")"; /// cauta dupa id.(eu cautam dupa userName)

        rc = sqlite3_exec(db, sqlVerif.c_str(), 0, 0, &err_msg);
        /// Ar trb in loc de 0 sa bag si functia callback ca sa iau din acel select cv

        /// Test : nu prea e oke
        /*
                if(rc!=SQLITE_OK)
                {
                    fprintf(stderr, "Cannot use existance select: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return User(-2,-2,"Error at SELECT EXISTANCE","Error","Error","Error","Error","Error");
                }
                else
                {
                    int exists=sqlite3_column_int(stmt,0); ///Atentie ca asta cred ca retureaza mereu 0 si daca pun callnack-ul
                   if(exists == 0) {
                       fprintf(stderr, "Cannot find the user: %s\n", sqlite3_errmsg(db));
                       sqlite3_close(db);
                       return User(-3, -3, "Error User Doesn't Exists", "Error", "Error", "Error", "Error", "Error");
                   }
                   else  ///Am gasit userul
                   {
                   */
        sqlVerif = "SELECT * FROM Users WHERE id=" + id;
        // sqlVerif = "SELECT * FROM Users WHERE id = Users.id"; /// cauta dupa id in loc de userName.
        //  era int rc
        rc = sqlite3_exec(db, sqlVerif.c_str(), 0, 0, &err_msg); /// Callback
        if (rc != SQLITE_OK)
        {
            ///!!!!!AICI SE BLOCHEAZA PRIMA FUNCTIE
            fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return User(-5, -5, "Error using select", "Error", "Error", "Error", "Error", "Error");
        }
        else
        {
            int admin = sqlite3_column_int(stmt, 0);
            const unsigned char *userN = sqlite3_column_text(stmt, 1);
            const unsigned char *firstN = sqlite3_column_text(stmt, 2);
            const unsigned char *lastN = sqlite3_column_text(stmt, 3);
            const unsigned char *birth = sqlite3_column_text(stmt, 4);
            const unsigned char *accountDate = sqlite3_column_text(stmt, 5);
            const unsigned char *profileDesc = sqlite3_column_text(stmt, 6);
            bool isAdmin;
            std::string userName;
            std::string firstname;
            std::string lastname;
            std::string birthday;
            std::string accountCreationDate;
            std::string profileDescription;
            /*
             isAdmin = bool(admin);    /// REINTERPRET_CAST TRB SA-I DAU
             userName  = userN;
             firstname = firstN;
             lastname  = lasrN;
             birthday  = birth;
             accountCreationDate = accountDate;
             profileDescription = profileDesc;
          */
            cout << "User Getted!" << '\n';
            return User(id, isAdmin, userName, firstname, lastname, birthday, accountCreationDate, profileDescription);
        }
    }
    //   }

    // }
    /*
           functia primeste ca si parametru un User object
           faci update in Users table unde id din parametru = id din tabel
           daca reuseste, returneaza 1, daca da fail, returneaza 0
  */
    int updateUser(User users)
    {
        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); // aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK)
        {

            fprintf(stderr, "Cannot open database on update users: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        /// Aici trebuie sa vad daca exista utilizatorul meu. Altfel returnez iar cv
        /*
            string sqlVerif="SELECT EXISTS(SELECT id FROM Users WHERE id = users.id)"; //

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
        /// AICI FAC SET-UL   ; l comment i am pus strig sqlVerif si la rc am scus int rc.
        string sqlVerif = "UPDATE Users SET isAdmin = " + to_string(users.isAdmin) + ", userName = " + users.userName + ", firstname = users.firstname , lastname = users.lastname , birthday = users.birthday , accountCreationDate = users.accountCreationDate , profileDescription = users.profileDescription WHERE id = users.id";
        rc = sqlite3_exec(db, sqlVerif.c_str(), 0, 0, &err_msg); /// Callback
        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "Select comand doesn t work: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }
        else
        {
            cout << "User Updated!" << '\n';
            return 1;
        }
    }
    // }
    // }
    /*
         functia primeste ca si parametru un id
         stergi din tabel user-ul cu id-ul ala
         daca reuseste, returneaza 1, daca da fail, returneaza 0
     */
    int deleteUser(int id)
    {

        sqlite3 *db;
        sqlite3_stmt *stmt;

        char *err_msg = 0;
        sqlite3_stmt *res;

        int rc = sqlite3_open("mydb.db", &db); // aici am schimbat din database.db in mydb.db

        if (rc != SQLITE_OK)
        {

            fprintf(stderr, "Cannot open database on delete user: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }

        /// Aici trebuie sa vad daca exista utilizatorul meu. Altfel returnez iar cv

        string sqlVerif = "SELECT EXISTS(SELECT id FROM Users WHERE Users.id = id)"; // Da seg fault

        rc = sqlite3_exec(db, sqlVerif.c_str(), 0, 0, &err_msg);
        /// Ar trb in loc de 0 sa bag si functia callback ca sa iau din acel select cv

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
        sqlVerif = "DELETE FROM Users WHERE Users.id = id";      /// Atentie trebuia users (corrected)
        rc = sqlite3_exec(db, sqlVerif.c_str(), 0, 0, &err_msg); /// Callback
        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "Delete comand doesn t work: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }
        else
        {
            cout << "User Deleted!" << '\n';
            return 1;
        }
        cout << "nici aici nush ce sa i fac" << '\n';
        return 1;
    }
    //          }

    //   }
};

#endif // SOCIALMEDIA_HANDLERUSERDB_H
