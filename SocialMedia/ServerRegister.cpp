#include <iostream>
#include "models/User.h"
#include "db/handler/HandlerUserDB.h"
#include "models/Passwords.h"
#include "db/handler/HandlerPasswordsDB.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <csignal>
#include <string.h>
#include <sys/wait.h>
#include <jsoncpp/json/json.h>
#include <unistd.h>

#define PORT_REGISTER 2023


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

    server.sin_port = htons(PORT_REGISTER);

    if (bind(sd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1) {
        perror("Error on bind on register server \n");
        return -2;
    }

    if (listen(sd, 1000) == -1) {
        perror("Error on listen on register server \n");
        return -3;
    }

    int i;
    while (1) {
        int client;
        socklen_t length = sizeof(form);
        printf("Register server waits on %d\n", PORT_REGISTER);
        fflush(stdout);
        client = accept(sd, (struct sockaddr *) &form, &length);
        // client = accept(sd, reinterpret_cast<sockaddr *>(&form), reinterpret_cast<socklen_t *>(&length)); /// careful
        if (client < 0) {
            perror("Error on client acces on register server \n");
            continue;
        }

        int pid;
        if ((pid = fork()) == -1) {
            perror("Error on fork acces on register server \n");
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

            // std::cout << json;

            User user = User(json);;
            std::cout << user.userName << '\n';
            std::cout << user.lastname << '\n';
            std::cout << user.firstname << '\n';
            std::cout << user.isAdmin << '\n';
            std::cout << user.accountCreationDate << '\n';
            std::cout << user.birthday << '\n';
            std::cout << user.profileDescription << '\n';
            HandlerUserDB handlerUser;

            int succes = handlerUser.createUser(user);
            if (write(client, to_string(succes).c_str(), BUFSIZ) <= 0) {
                perror("Server Register Could Not Respond To Client!");
                close(client);
                exit(0);
            }
            if (succes) {
                cout << "User Successfully Created!";
                char jsonPassword[BUFSIZ];
                if (read(client, jsonPassword, BUFSIZ) < 0) {
                    perror("Password access!");
                    close(client);
                    exit(0);
                }
                Passwords password = Passwords(jsonPassword);
                cout << password.toJson() << '\n';
                HandlerPasswordsDB handlerPasswordsDB;
                int responsePassword = handlerPasswordsDB.createPassword(password);
                if (write(client, to_string(succes).c_str(), BUFSIZ) <= 0) {
                    perror("Server Register Could Not Respond To Client!");
                    close(client);
                    exit(0);
                }
                if (responsePassword == 1) {
                    cout << "Password Successfullly Created!";
                } else {
                    cout << "Couldn't Creeate Password";
                }

            } else {
                cout << "Fail Create User";
            }
            close(client);
            exit(0);
        }
    }

    std::cout << "qbc";
    return 0;
}
