#include <iostream>
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
#include <openssl/aes.h>
#include <openssl//evp.h>

#define PORT_LOGIN 2024

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

    server.sin_port = htons(PORT_LOGIN);

    if (bind(sd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1) {
        perror("Error on bind on login server \n");
        return -2;
    }

    if (listen(sd, 1000) == -1) {
        perror("Error on listen on login server \n");
        return -3;
    }

    int i;
    while (1) {
        int client;
        socklen_t length = sizeof(form);
        printf("Register server waits on %d\n", PORT_LOGIN);
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
            int readbyte = read(client, json, BUFSIZ);
            if (readbyte < 0) {
                perror("Eroare");
                close(client);
                continue;
            }

            // std::cout << json;

            Passwords loginDetails = Passwords(json);

            std::cout << loginDetails.userName << '\n';
            std::cout << loginDetails.password << '\n';

            //-----------AICI M_AM OPRIT DIN LUCRU

            HandlerPasswordsDB handlerPasswords;

            Passwords verifyPassword = handlerPasswords.getPassword(loginDetails.userName);


            int loginSuccessfull;
            if (loginDetails.password == verifyPassword.password) ///ciudat
            {
                loginSuccessfull = 1;
            } else {
                loginSuccessfull = 0;
            }

            if (write(client, to_string(loginSuccessfull).c_str(), BUFSIZ) <= 0) {
                perror("Server Login Could Not Respond To Client!");
                close(client);
                exit(0);
            }
            if (loginSuccessfull) {
                cout << "User " << loginDetails.userName << " Successfully Logged In!";
            } else {
                cout << "Fail To log in for user " << loginDetails.userName << "\n";
            }
            close(client);
            exit(0);
        }
    }

    std::cout << "qbc";
    return 0;
}
