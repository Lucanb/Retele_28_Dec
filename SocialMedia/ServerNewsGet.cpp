//
// Created by lolluckestar on 09.01.2023.
//

#include <iostream>
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

#define PORT_SEARCHNEWS 2027


int main() {
    struct sockaddr_in server;
    struct sockaddr_in form;
    char msg[BUFSIZ];
    char msgrasp[BUFSIZ];
    int sd = -1;
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error on register server \n");
        return -1;
    }

    bzero(&server, sizeof(server));
    bzero(&form, sizeof(form));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    server.sin_port = htons(PORT_SEARCHNEWS);

    if (bind(sd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1) {
        perror("Error on bind on NewsSearch server \n");
        return -2;
    }

    if (listen(sd, 1000) == -1) {
        perror("Error on listen on NewsSearch server \n");
        return -3;
    }
////

    while (1) {
        vector<string> v1;
        int client;
        socklen_t length = sizeof(form);
        printf("Register server waits on %d\n", PORT_SEARCHNEWS);
        fflush(stdout);
        client = accept(sd, (struct sockaddr *) &form, &length);
        // client = accept(sd, reinterpret_cast<sockaddr *>(&form), reinterpret_cast<socklen_t *>(&length)); /// careful
        if (client < 0) {
            perror("Error on client acces on Search News server \n");
            continue;
        }

        int pid;
        if ((pid = fork()) == -1) {
            perror("Error on fork acces on get Search News server \n");
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
            string NewsDetails = json;
            HandlerNewsDB handler;
            ///Acum trbuie in baza de date sa aplicam functia ce ne returneaza dupa userName.
            v1 = handler.getNewsByTitle(NewsDetails); ///Merge!   (vect de content uri)
            // cout<<"a ajuns";

            ////
            if (v1[0] != "fail")  ///
            {
                ///Vectorul este oke deci pun in stringul final toate elementele gasite.
                string json2;
                for (int i = 0; i < v1.size(); i++)
                    json2 = json2 + v1[i] + string("\n");

                cout << json2;

                if (write(client, json2.c_str(), BUFSIZ) <= 0) {
                    perror("Server Search News Could Not Respond To Client!");
                    close(client);
                    exit(0);
                } else {
                    cout << "News Getted \n";    ///Aici am scris mesajul final;
                }
                close(client);
                exit(0);
            } else {
                string json2 = "fail";  ///POSIBILA EROARE
                if (write(client, json2.c_str(), BUFSIZ) <= 0) {
                    perror("Server GetUser Could Not Respond To Client!");
                    close(client);
                    exit(0);
                } else {
                    cout << "Fail To  respond getUser in for user \n";
                }
                cout << "Didn't found any user \n";
                close(client);
                exit(0);
            }
        }
    }
}