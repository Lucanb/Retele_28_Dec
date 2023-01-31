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
#include "db/handler/HandlerFriendRequest.h"

#define PORT_DOFRIENDREQUEST 2033

int main() {
    struct sockaddr_in server;
    struct sockaddr_in form;
    char msg[BUFSIZ];
    char msgrasp[BUFSIZ];
    int sd = -1;
    std::string getUser;
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error on Creeate Friend server \n");
        return -1;
    }

    bzero(&server, sizeof(server));
    bzero(&form, sizeof(form));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    server.sin_port = htons(PORT_DOFRIENDREQUEST);

    if (bind(sd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1) {
        perror("Error on bind on Creeate Friend Request server \n");
        return -2;
    }

    if (listen(sd, 1000) == -1) {
        perror("Error on listen on AddFriend Server server \n");
        return -3;
    }

    while (1) {
        int client;
        socklen_t length = sizeof(form);
        printf("Register server waits on %d\n", PORT_DOFRIENDREQUEST);
        fflush(stdout);
        client = accept(sd, (struct sockaddr *) &form, &length);
        // client = accept(sd, reinterpret_cast<sockaddr *>(&form), reinterpret_cast<socklen_t *>(&length)); /// careful

        if (client < 0) {
            perror("Error on client acces on get Creeate Friend Request server \n");
            continue;
        }

        int pid;
        if ((pid = fork()) == -1) {
            perror("Error on fork acces on get Add Friend Request server \n");
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

            bool accepted = false;

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

            HandlerUserDB handlerUser;

            int Vf;

            int ids1 = handlerUser.GetUserId(userActual);
            int ids2 = handlerUser.GetUserId(userDetails);
            if (ids1 != 0 && ids2 != 0) {
                FriendRequest friendRequestObj = FriendRequest(0, ids1, ids2, type, accepted);
                HandlerFriendRequestDB handlerAdd;
                Vf = handlerAdd.createFriendRequest(friendRequestObj);
                if (Vf != 0) {
                    succes = "1";
                } else {
                    succes = "0";
                }
            } else {
                cout << "A user doesn't exist \n";
                succes = "0";
            }

            if (write(client, succes.c_str(), BUFSIZ) <= 0) {
                perror("Server Add Friend Request Could Not Respond To Client!");
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