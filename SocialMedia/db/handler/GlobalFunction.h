//
// Created by lolluckestar on 25.12.2022.
//


#ifndef SOCIALMEDIA_GLOBALFUNCTION_H
#define SOCIALMEDIA_GLOBALFUNCTION_H


#include<iostream>
#include<string>
#include<vector>
#include"../../db/mydb/sqlite3.h"
using namespace std;

string returningStr;

void parsing(string s, vector<string> &result) {
    string copy = "";
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '=') {
            copy = "";
        }
        if (s[i] != '=' && s[i] != '\n')
            copy += s[i];

        if (s[i] == '\n') {
            result.push_back(copy);
            copy = "";
        }
    }

}

static int callback(void *data, int argc, char **argv, char **azColName) {
    returningStr = ""; //Aici initializez global ul;
    int i;

    for (i = 0; i < argc; i++) {
        returningStr += azColName[i];
        returningStr += "=";
        returningStr += argv[i] ? argv[i] : "NULL";
        returningStr += "\n";
    }
    return 0;
}
#endif //SOCIALMEDIA_GLOBALFUNCTION_H