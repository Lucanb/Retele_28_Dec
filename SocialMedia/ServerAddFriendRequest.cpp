//
// Created by lolluckestar on 11.01.2023.
//
#include <sys/socket.h>
#include <netinet/in.h>
#include <csignal>
#include <string.h>
#include <sys/wait.h>
#include <jsoncpp/json/json.h>
#include <unistd.h>
#include "db/handler/HandlerFriendDB.h"
#include "db/handler/HandlerUserDB.h"

#define ADD_FRIENDREQUEST 2032


int main() {
    struct sockaddr_in server;
    struct sockaddr_in form;
    char msg[BUFSIZ];
    char msgrasp[BUFSIZ];
    int sd = -1;
    std::string getUser;
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error on GetFriend server \n");
        return -1;
    }

    bzero(&server, sizeof(server));
    bzero(&form, sizeof(form));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    server.sin_port = htons(ADD_FRIENDREQUEST);

    if (bind(sd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1) {
        perror("Error on bind on ServerAddFriendRequest server \n");
        return -2;
    }

    if (listen(sd, 1000) == -1) {
        perror("Error on listen on AddFriend Server server \n");
        return -3;
    }

    while (1) {
        int client;
        socklen_t length = sizeof(form);
        printf("Register server waits on %d\n", ADD_FRIENDREQUEST);
        fflush(stdout);
        client = accept(sd, (struct sockaddr *) &form, &length);
        // client = accept(sd, reinterpret_cast<sockaddr *>(&form), reinterpret_cast<socklen_t *>(&length)); /// careful

        if (client < 0) {
            perror("Error on client acces on get Add Friend server \n");
            continue;
        }

        int pid;
        if ((pid = fork()) == -1) {
            perror("Error on fork acces on get Add Friend server \n");
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

            std::string userDetails;
            std::string type;
            std::string userActual;
            string succes;
            int sw = 0;
            for (int i = 0; i < strlen(json); i++) {
                if (sw == 0) {
                    userDetails.push_back(json[i]);
                }

                if (json[i] == '\n') {
                    sw++;
                    i++;
                }
                if (sw == 1) {
                    userActual.push_back(json[i]);
                }
                if (sw == 2) {
                    type.push_back(json[i]);
                }
            }

            HandlerFriendDB handler;
            HandlerUserDB handlerUser;

            int ids1 = handlerUser.GetUserId(userActual);
            int ids2 = handlerUser.GetUserId(userDetails);
            if (ids1 != 0 && ids2 != 0) {
                Friend friendObj;
                friendObj.id1 = ids1;
                friendObj.id2 = ids2;
                friendObj.type = type;

                int verif = handler.createFriend(friendObj);
                if (verif != 0) {
                    succes = "1";
                } else {
                    succes = "0";
                }
            } else {
                succes = "0";
            }

            if (write(client, succes.c_str(), BUFSIZ) <= 0) {
                perror("Server Add Friend Could Not Respond To Client!");
                close(client);
                exit(0);
            } else {
                cout << "Server Responded \n";
            }
            close(client);
            exit(0);
        }
    }
}