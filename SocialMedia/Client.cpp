//
// Created by lolluckestar on 06.01.2023.
//
#include <iostream>
#include <chrono>
#include <iomanip>
#include "models/User.h"
#include "models/Passwords.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <csignal>
#include <string.h>
#include <sys/wait.h>
#include <jsoncpp/json/json.h>
#include <unistd.h>

#define PORT_REGISTER 2023
#define PORT_LOGIN 2024
#define PORT_GETUSER 2025
#define PORT_GetFriendRequest 2026
#define PORT_SEARCHNEWS 2027

using namespace std;

User loggedInUser;

string currentISO8601TimeUTC() { /// stack overflow
    auto now = std::chrono::system_clock::now();
    auto itt = std::chrono::system_clock::to_time_t(now);
    std::ostringstream ss;
    ss << std::put_time(gmtime(&itt), "%FT%TZ");
    return ss.str();
}


void getUserData(string username,string &UserGetted) {

    // functia asta apeleaza serverul ServerGetUser
    // daca am luat datele la user, atunci apelam LoggedInMenu()
    int sd;
    struct sockaddr_in server;
    int raspuns;

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error at socket client at getUser\n");
        exit(-1); // placeholder, nu ne trebuie exit
        /*
        cout<<"Failed to create user. Please try again!\n";
        Login();
        //SAU
        //MainMenu();
        */
    }
    bzero(&server, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT_GETUSER);

    if (connect(sd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1) {
        perror("Wrong connect to GetUser \n");
        exit(-2);
    }

    string jsonGetUser = username;

    char towrite[BUFSIZ];
    for (int j = 0; j < BUFSIZ; j++)
        towrite[j] = 0;

    for (int j = 0; j < jsonGetUser.size(); j++)
        towrite[j] = jsonGetUser[j];

    int bytesWritten = write(sd, &towrite, BUFSIZ);
    if (bytesWritten <= 0) {
        perror("Error at bytes Written Client");
        exit(-3);
    }

    char response[BUFSIZ];
    if (read(sd, response, BUFSIZ) < 0) {
        perror("Client could not read server userget response");
        exit(-4);
    }

    if (strcmp(response, "fail") != 0) {
        cout << "User data getted!\n";
        UserGetted = response; //afiseaza json-ul.
     //   cout<<UserGetted;
    } else {
        cout << "FAILED TO LOG IN. PLEASE TRY AGAIN!\n";
        UserGetted = "";
    }
}

void LoggedInMenu();

void Login() {
    cout << "Please input your login details:\n";

    string username;
    cout << "username:\n";
    cin >> username;

    string password;
    cout << "password:\n";
    cin >> password;

    Passwords passwords;
    passwords.userName = username;
    passwords.password = password;

    int sd;
    struct sockaddr_in server;
    int raspuns;

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error at socket client at login\n");
        exit(-1); // placeholder, nu ne trebuie exit
        /*
        cout<<"Failed to create user. Please try again!\n";
        Login();
        //SAU
        //MainMenu();
        */
    }

    bzero(&server, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT_LOGIN);

    if (connect(sd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1) {
        perror("Wrong connect to register \n");
        exit(-2);
    }

    string jsonLogin = passwords.toJson();

    char towrite[BUFSIZ];
    for (int j = 0; j < BUFSIZ; j++)
        towrite[j] = 0;

    for (int j = 0; j < jsonLogin.size(); j++)
        towrite[j] = jsonLogin[j];

    int bytesWritten = write(sd, &towrite, BUFSIZ);
    if (bytesWritten <= 0) {
        perror("Error at bytes Written Client");
        exit(-3);
    }

    char response[BUFSIZ];
    if (read(sd, response, BUFSIZ) < 0) {
        perror("Client could not read server login response");
        exit(-4);
    }

    string actualUser;

    // DACA A MERS LOGIN_UL PRIMIM 1, DACA NU, 0
    if (strcmp(response, "0") != 0) {
        cout << "YOU ARE LOGGED IN!\n";
        getUserData(username,actualUser);
        cout<<actualUser;
        loggedInUser = User(actualUser); ///aici nu l face;
   //     cout<< loggedInUser.userName<<" "<<loggedInUser.accountCreationDate<<" "<<loggedInUser.firstname<<'\n'; //nu il face;
        LoggedInMenu();
    } else {
        cout << "FAILED TO LOG IN. PLEASE TRY AGAIN!\n";
        Login();
    }
}

void CreeateUser();

void SearchNews()
{
    string name;
    string NewsGetted;
    cout<<"Pleas Input a Name : \n";
    cin>>name;

    int sd;
    struct sockaddr_in server;
    int raspuns;

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error at socket client at Search News\n");
        exit(-1); // placeholder, nu ne trebuie exit
        /*
        cout<<"Failed to create user. Please try again!\n";
        SearchNews();
        //SAU
        //MainMenu();
        */
    }
    bzero(&server, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT_SEARCHNEWS);

    if (connect(sd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1) {
        perror("Wrong connect to SearchNews \n");
        exit(-2);
    }

    string jsonGetUser = name; ///Trimitem la server acest mesaj.

    char towrite[BUFSIZ];
    for (int j = 0; j < BUFSIZ; j++)
        towrite[j] = 0;

    for (int j = 0; j < jsonGetUser.size(); j++)
        towrite[j] = jsonGetUser[j];

    int bytesWritten = write(sd, &towrite, BUFSIZ);
    if (bytesWritten <= 0) {
        perror("Error at bytes Written SearchNews");
        exit(-3);
    }
    char response[BUFSIZ];
    if (read(sd, response, BUFSIZ) < 0) {
        perror("Client could not read server SearchNews response");
        exit(-4);
    }


    if (strcmp(response, "fail") != 0) {
        cout << "News data getted!\n";
        NewsGetted = response; //afiseaza json-ul.
        cout<<NewsGetted;
    } else {
        cout << "FAILED Search News . PLEASE TRY AGAIN!\n";
        NewsGetted = "";
        SearchNews();
    }

    cout<<NewsGetted;
}

void MainMenu() {
    cout << "Welcome to VirtualSoc!" << '\n';

    cout << "Chose your command  \n";
    cout << "1 - login \n";
    cout << "2 - register \n";
    cout << "3 - search \n";
    cout << "4 - exit \n";

    int comanda;
    cin >> comanda;

    if (comanda == 1) {
        Login();
    } else if (comanda == 2) {
        CreeateUser();
    } else if (comanda == 3) {
         SearchNews();
    } else if (comanda == 4) {
        exit(0);
    } else {
        cout << "Comanda gresita!";
    }
}

void CreeateUser() {

    cout << "You are going to creeate your account \n";

    User userCreeateAccount;
///AICI DE FCT mai tz.
    cout << "Please input your username \n";

    cin >> userCreeateAccount.userName;

    cout << "Please input your firstname \n";

    cin >> userCreeateAccount.firstname;

    cout << "Please input your lastname \n";

    cin >> userCreeateAccount.lastname;

    cout << "Please input your profile description \n";

    // CIN PERMITE CITIREA PANA LA SPACE SAU ENTER
    cin >> userCreeateAccount.profileDescription;

    cout << "Please input your birthday \n";

    cin >> userCreeateAccount.birthday;

    userCreeateAccount.accountCreationDate = currentISO8601TimeUTC(); /// a ramas id ul care e autoincrement , data si cu isAdmin.

    cout << "Input 1 if you are an admin else input 0 \n";

    cin >> userCreeateAccount.isAdmin;

    string password;

    cout << "Choose your password:\n";

    cin >> password;

    int sd;
    struct sockaddr_in server;
    int raspuns;

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error at socket client at register \n");
        exit(-1); // placeholder, nu ne trebuie exit
        /*
        cout<<"Failed to create user. Please try again!\n";
        CreeateUser();
        //SAU
        //MainMenu();
        */
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
    for (int j = 0; j < BUFSIZ; j++)
        towrite[j] = 0;

    for (int j = 0; j < json.size(); j++)
        towrite[j] = json[j];

    int bytesWritten = write(sd, &towrite, BUFSIZ);
    if (bytesWritten <= 0) {
        perror("Error at bytes Written Client");
        exit(-3);
    }
    char response[BUFSIZ];
    if (read(sd, response, BUFSIZ) < 0) {
        perror("Client could not read server register response");
        exit(-4);
    }

    if (strcmp(response, "1") == 0) {
        Passwords passwordObj;
        passwordObj.userName = userCreeateAccount.userName;
        passwordObj.password = password;
        string jsonPassword = passwordObj.toJson();
        for (int j = 0; j < BUFSIZ; j++) {
            towrite[j] = 0;
        }

        for (int j = 0; j < jsonPassword.size(); j++) {
            towrite[j] = jsonPassword[j];
        }

        bytesWritten = write(sd, &towrite, BUFSIZ);

        if (bytesWritten <= 0) {
            perror("Error bytes writen password Client");
            exit(-5);
        }

        if (read(sd, response, BUFSIZ) < 0) {
            perror("Client could not read server register response");
            exit(-4);
        }
        if (strcmp(response, "1") == 0) {
            cout << "User Created Successfully!\n";
            cout << "Password Created Successfully!\n";
            MainMenu();
        } else {
            cout << "Fail to create password";
        }
    } else {
        perror("Fail to create user try again");
    }
}

void GetFriendReq(string usernames,string &UserGetted)
{
// functia asta apeleaza serverul ServerGetUser
    // daca am luat datele la user, atunci apelam LoggedInMenu()
    int sd;
    struct sockaddr_in server;
    int raspuns;

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error at socket client at getUser\n");
         // placeholder, nu ne trebuie exit
        cout<<"Failed to create user. Please try again!\n";
        Login();
        //SAU
        //MainMenu();
    }
    bzero(&server, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT_GetFriendRequest);

    if (connect(sd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1) {
        perror("Wrong connect to GetUser \n");
        exit(-2);
    }
    string jsonGetUser = usernames;

    char towrite[BUFSIZ];
    for (int j = 0; j < BUFSIZ; j++)
        towrite[j] = 0;

    for (int j = 0; j < jsonGetUser.size(); j++)
        towrite[j] = jsonGetUser[j];

    int bytesWritten = write(sd, &towrite, BUFSIZ);
    if (bytesWritten <= 0) {
        perror("Error at bytes Written Client");
        exit(-3);
    }

    char response[BUFSIZ];
    if (read(sd, response, BUFSIZ) < 0) {
        perror("Client could not read server user get response");
        exit(-4);
    }

    if (strcmp(response, "fail") != 0) {
       cout << "User data getted!\n";
        UserGetted = response;
    } else {
        cout << "FAILED TO LOG IN. PLEASE TRY AGAIN!\n";
        UserGetted = "";
    }
}

void LoggedInMenu() {
    int command;
    cout << "Welcome to your Account!" << '\n';

    cout << "Chose your command  \n";

    cout << "1 - profile \n";
    cout << "2 - create news \n";
    cout << "3 - search news \n";
    cout << "4 - search friend \n";
    cout << "5 - see friend requests \n";
    cout << "6 - search users with that name \n";
    //...

    int comanda;
    cin >> comanda;
    if(comanda == 1) ///Inca nu merge da seg eror si fail la cautare ...
    {
        string show;
        string profileDetails = "traian";//"loggedInUser.userName"; ///Asta nu afiseaza nimic ; de ce? :)
       // cout<<profileDetails;
        getUserData(profileDetails,show);
        cout<<show<<"\n";
        LoggedInMenu();
    }
    else if(comanda == 2)
    {
        LoggedInMenu();
    }
    else if(comanda == 3)
    {
          ///Search News
        LoggedInMenu();
    }
    else if(comanda == 4 )
    {
          ///Search Friend
        LoggedInMenu();
    }
    else if(comanda == 5)
    {
        string show;
        cout<<"Write the string that u want to match \n";
        string s;
        cin>>s;
        GetFriendReq(s,show);
        cout<<show<<'\n';
        LoggedInMenu();
         ///Search Friend Request
    }
    else
    {
        cout<<"Wrong Command \n";
        LoggedInMenu();
    }
}


int main() {
    MainMenu();
    return 0;
}