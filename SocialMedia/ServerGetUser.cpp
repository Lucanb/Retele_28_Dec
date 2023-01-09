//
// Created by lolluckestar on 09.01.2023.
//
#include <iostream>
#include "models/User.h"
#include "db/handler/HandlerUserDB.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <csignal>
#include <string.h>
#include <sys/wait.h>
#include <jsoncpp/json/json.h>
#include <unistd.h>

#define PORT_GETUSER 2025

int main() {
    struct sockaddr_in server;
    struct sockaddr_in form;
    char msg[BUFSIZ];
    char msgrasp[BUFSIZ];
    int sd = -1;
    User getUser;
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error on register server \n");
        return -1;
    }

    bzero(&server, sizeof(server));
    bzero(&form, sizeof(form));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    server.sin_port = htons(PORT_GETUSER);

    if (bind(sd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1) {
        perror("Error on bind on login server \n");
        return -2;
    }

    if (listen(sd, 1000) == -1) {
        perror("Error on listen on login server \n");
        return -3;
    }

    /////
    int i;
    while (1) {
        int client;
        socklen_t length = sizeof(form);
        printf("Register server waits on %d\n", PORT_GETUSER);
        fflush(stdout);
        client = accept(sd, (struct sockaddr *) &form, &length);
        // client = accept(sd, reinterpret_cast<sockaddr *>(&form), reinterpret_cast<socklen_t *>(&length)); /// careful
        if (client < 0) {
            perror("Error on client acces on get user server \n");
            continue;
        }

        int pid;
        if ((pid = fork()) == -1) {
            perror("Error on fork acces on get user server \n");
            continue;
        } else if (pid > 0) {
            /// parinte
            close(client);
            while (waitpid(-1, NULL, WNOHANG));
            continue;
        } else if (pid == 0) {
            /// copil
            close(sd);

            char json[BUFSIZ];
            int readbyte = read(client, json, BUFSIZ);
            if (readbyte < 0) {
                perror("Eroare");
                close(client);
                continue;
            }
            ////
            string userDetails = json;
            HandlerUserDB handler;
            ///Acum trbuie in baza de date sa aplicam functia ce ne returneaza dupa userName.
            getUser = handler.getUserByUsername(userDetails); ///Merge!
        }
        /*
        std::cout << getUser.userName << '\n';
        std::cout << getUser.profileDescription << '\n';
        std::cout << getUser.birthday << '\n';
        std::cout << getUser.firstname << '\n';
        std::cout << getUser.lastname << '\n';
        std::cout << getUser.isAdmin << '\n';
        std::cout << getUser.accountCreationDate << '\n';
        */
        int success;
        if (getUser.id >= 0)
            success = 1;
        else
            success = 0;

        if (success) {
            string json2 = getUser.toJson();  ///POSIBILA EROARE
            if (write(client, json2.c_str(), BUFSIZ) <= 0) {
                perror("Server GetUser Could Not Respond To Client!");
                close(client);
                exit(0);
            } else {
                cout << "User Getted \n";
            }
            close(client);
            exit(0);
        }
        else
        {
            string json2 = "fail";  ///POSIBILA EROARE
            if (write(client, json2.c_str(), BUFSIZ) <= 0) {
                perror("Server GetUser Could Not Respond To Client!");
                close(client);
                exit(0);
            } else {
                cout << "Fail To  respond getUser in for user \n";
            }
            cout << "Fail To getUser in for user \n";
            close(client);
            exit(0);
        }


        /////
    }
}