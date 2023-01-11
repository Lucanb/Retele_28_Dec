//
// Created by lolluckestar on 09.01.2023.
//
#include <iostream>
#include "models/User.h"
#include "db/handler/HandlerUserDB.h"
#include "db/handler/HandlerFriendRequest.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <csignal>
#include <string.h>
#include <sys/wait.h>
#include <jsoncpp/json/json.h>
#include <unistd.h>

#define PORT_GetFriendRequest 2026

int main() {
    struct sockaddr_in server;
    struct sockaddr_in form;
    char msg[BUFSIZ];
    char msgrasp[BUFSIZ];
    int sd = -1;
    string getUser;
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error on GetFriend server \n");
        return -1;
    }

    bzero(&server, sizeof(server));
    bzero(&form, sizeof(form));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    server.sin_port = htons(PORT_GetFriendRequest);

    if (bind(sd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1) {
        perror("Error on bind on login server \n");
        return -2;
    }

    if (listen(sd, 1000) == -1) {
        perror("Error on listen on Get Friend Server server \n");
        return -3;
    }

    /////
    int i;
    while (1) {
        int client;
        socklen_t length = sizeof(form);
        printf("Register server waits on %d\n", PORT_GetFriendRequest);
        fflush(stdout);
        client = accept(sd, (struct sockaddr *) &form, &length);
        // client = accept(sd, reinterpret_cast<sockaddr *>(&form), reinterpret_cast<socklen_t *>(&length)); /// careful

        if (client < 0) {
            perror("Error on client acces on get FriendRequest server \n");
            continue;
        }

        int pid;
        if ((pid = fork()) == -1) {
            perror("Error on fork acces on get FriendRequest server \n");
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
            string userActual;
            for (int i = 0; i < strlen(json); i++) {
                int sw = 0;
                if (json[i] != '\n' && sw == 0)
                    userDetails[i] = json[i];
                else {
                    sw = 1;
                    i++;
                }
                if (sw == 1) {
                    userActual[i] = json[i];
                }
            }
            HandlerFriendRequestDB handler;
            ///Acum trbuie in baza de date sa aplicam functia ce ne returneaza dupa userName.
            // getUser
            vector<string> usersGet;
            usersGet = handler.GetRequestNames(userDetails, userActual);
            for (int i = 0; i < usersGet.size(); i++)
                getUser += usersGet[i] + "\n";


            int success;
            if (getUser.size() >= 0)
                success = 1;
            else
                success = 0;

            if (success) {
                string json2 = getUser;  ///POSIBILA EROARE
                if (write(client, json2.c_str(), BUFSIZ) <= 0) {
                    perror("Server GetUser Could Not Respond To Client!");
                    close(client);
                    exit(0);
                } else {
                    cout << "UserFriendReq Getted \n";
                }
                close(client);
                exit(0);
            } else {
                ///POSIBILA EROARE
                string json2 = "";
                if (write(client, json2.c_str(), BUFSIZ) <= 0) {
                    perror("Server GetUser Could Not Respond To Client!");
                    close(client);
                    exit(0);
                } else {
                    cout << "That user Request doesn't Match \n";
                }
                //  cout << "Fail To getUser in for user \n";
                close(client);
                exit(0);
            }
            /////
        }
    }
}