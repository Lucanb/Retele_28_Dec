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
#include "db/handler/HandlerMessageDB.h"

#define PORT_GETMESSAGE 2034

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

    server.sin_port = htons(PORT_GETMESSAGE);

    if (bind(sd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1) {
        perror("Error on bind on GetMessage server \n");
        return -2;
    }

    if (listen(sd, 1000) == -1) {
        perror("Error on listen on GetMessage server \n");
        return -3;
    }

    while (1) {
        int client;
        socklen_t length = sizeof(form);
        printf("GetMessage server waits on %d\n", PORT_GETMESSAGE);
        fflush(stdout);
        client = accept(sd, (struct sockaddr *) &form, &length);
        // client = accept(sd, reinterpret_cast<sockaddr *>(&form), reinterpret_cast<socklen_t *>(&length)); /// careful

        if (client < 0) {
            perror("Error on client acces on get GetMessage server \n");
            continue;
        }

        int pid;
        if ((pid = fork()) == -1) {
            perror("Error on fork acces on Get Message server \n");
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

            HandlerUserDB handlerGetID;

            string title;
            for (int i = 0; i < strlen(json); i++) {
                title.push_back(json[i]);
            }
            string response;
            HandlerMessageDB handlerMess;
            vector<string> vec = handlerMess.getMessageAfterName(title);



                    string succes;
            if (vec.size() != 0) {
                if (vec[0] != "fail") {
                    succes = "1";
                    for(int i= 0 ;i<vec.size();i++)
                        response += vec[i] + "\n";
                } else {
                    succes = "0";
                    response = "No Messages \n";
                }
            } else {
                succes = "0";
                response = "No Messages \n";
            }

            if (write(client, response.c_str(), BUFSIZ) <= 0) {
                perror("Server Register Could Not Respond To Client!");
                close(client);
                exit(0);
            } else {
                cout << " Message sent";
                close(client);
                exit(0);
            }

        }
    }
}
