//
// Created by lolluckestar on 10.01.2023.
//
#include <iostream>
#include "models/User.h"
#include "db/handler/HandlerUserDB.h"
#include "models/Passwords.h"
#include "db/handler/HandlerPasswordsDB.h"
#include "models/News.h"
#include "db/handler/HandlerNewsDB.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <csignal>
#include <string.h>
#include <sys/wait.h>
#include <jsoncpp/json/json.h>
#include <unistd.h>

#define PORT_CREATENEWS 2028

int main() {

    struct sockaddr_in server;
    struct sockaddr_in form;
    char msg[BUFSIZ];
    char msgrasp[BUFSIZ];
    int sd = -1;

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error on Creeate News server \n");
        return -1;
    }
    bzero(&server, sizeof(server));
    bzero(&form, sizeof(form));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    server.sin_port = htons(PORT_CREATENEWS);

    if (bind(sd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1) {
        perror("Error on bind on Creeate News Server \n");
        return -2;
    }

    if (listen(sd, 1000) == -1) {
        perror("Error on listen on Creeate News server \n");
        return -3;
    }

    while (1) {
        int client;
        socklen_t length = sizeof(form);
        printf("Creeate News waits on %d\n", PORT_CREATENEWS);
        fflush(stdout);
        client = accept(sd, (struct sockaddr *) &form, &length);
        // client = accept(sd, reinterpret_cast<sockaddr *>(&form), reinterpret_cast<socklen_t *>(&length)); /// careful
        if (client < 0) {
            perror("Error on client acces on CreeateNews Server \n");
            continue;
        }

        int pid;
        if ((pid = fork()) == -1) {
            perror("Error on fork acces on Create News server \n");
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
            int readbyte = read(client, json, BUFSIZ); //&?
            if (readbyte < 0) {
                perror("Eroare");
                close(client);
                continue;
            }

            News newsObj = News(json);
            //Testeaza daca vrei.
            HandlerNewsDB handler;

            cout<<newsObj.authorId<<" "<<newsObj.id<<" "<<newsObj.title<<" "<<newsObj.type << " " <<newsObj.content;
            int succes = handler.createNews(newsObj);
            if (write(client, to_string(succes).c_str(), BUFSIZ) <= 0) {
                perror("Server Create News Could Not Respond To Client!");
                close(client);
                exit(0);
            }
            if (succes) {
                cout<<json<<'\n';
                cout << "News Successfully Created!";
            } else {
                cout << "Couldn't Creeate Password";
            }
            close(client);
            exit(0);
        }
    }
}