//
// Created by lolluckestar on 06.01.2023.
//
#include<iostream>
#include<chrono>
#include<iomanip>
#include "models/User.h"
#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include<csignal>
#include <string.h>
#include <sys/wait.h>
#include <jsoncpp/json/json.h>
#include<unistd.h>

#define PORT_REGISTER 2023

using namespace std;

string currentISO8601TimeUTC() {      ///stack overflow
    auto now = std::chrono::system_clock::now();
    auto itt = std::chrono::system_clock::to_time_t(now);
    std::ostringstream ss;
    ss << std::put_time(gmtime(&itt), "%FT%TZ");
    return ss.str();
}

void CreeateUser() {

    cout << "You are going to creeate your account \n";

    User userCreeateAccount;

    cout << "Please input your username \n";

    cin >> userCreeateAccount.userName;

    cout << "Please input your firstname \n";

    cin >> userCreeateAccount.firstname;

    cout << "Please input your lastname \n";

    cin >> userCreeateAccount.lastname;

    cout << "Please input your profile description \n";

    cin >> userCreeateAccount.profileDescription;

    cout << "Please input your birthday \n";

    cin >> userCreeateAccount.birthday;

    userCreeateAccount.accountCreationDate = currentISO8601TimeUTC();  /// a ramas id ul care e autoincrement , data si cu isAdmin.

    cout << "Input 1 if you are an admin else input 0 \n";

    cin >> userCreeateAccount.isAdmin;

    int sd;
    struct sockaddr_in server;
    int raspuns;

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error at socket client at register \n");
        exit(-1);
    }

    bzero(&server, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT_REGISTER);

    if (connect(sd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1) {
        perror("Wrong connect to register \n");
        exit(-2);
    }

    string json = userCreeateAccount.toJson();
    char towrite[BUFSIZ];
    for(int j=0;j<BUFSIZ;j++)
        towrite[j]=0;

    for(int j=0;j<json.size();j++)
        towrite[j]=json[j];

    int bytesWritten = write(sd, &towrite, BUFSIZ);
    if (bytesWritten <= 0) {
        perror("Error at bytes Written Client");
        exit(-3);
    }
}

int main() {
    cout << "Welcome to VirtualSoc!" << '\n';

    cout << "Chose your command  \n";
    cout << "1 - login \n";
    cout << "2 - register \n";
    cout << "3 - search \n";
    cout << "4 - exit \n";

    int comanda;
    cin >> comanda;

    if (comanda == 1) {

    } else if (comanda == 2) {
        CreeateUser();
    } else if (comanda == 3) {

    } else if (comanda == 4) {

    } else
        cout << "Comanda gresita!";
    return 0;
}