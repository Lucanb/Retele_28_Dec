//
// Created by lolluckestar on 06.01.2023.
//
#include<iostream>
#include "models/User.h"

using namespace std;

void CreeateUser() {

    cout<<"You are going to creeate your account \n";

    User userCreeateAccount;

    cout<<"Please input your username \n";

    cin>>userCreeateAccount.userName;

    cout<<"Please input your firstname \n";

    cin>>userCreeateAccount.firstname;

    cout<<"Please input your lastname \n";

    cin>>userCreeateAccount.lastname;

    cout<<"Please input your profile description \n";

    cin>>userCreeateAccount.profileDescription;

    cout<<"Please input your birthday \n";

    cin>>userCreeateAccount.birthday;
                                                  /// a ramas id ul care e autoincrement , data si cu isAdmin.
}

int main() {
    cout << "Welcome to VirtualSoc!" << '\n';

    cout << "Chose your command  \n";
    cout << "1 - login \n";
    cout << "2 - register \n";
    cout << "3 - search \n";
    cout << "4 - exit \n";

    int comanda;
    cin >> comanda;

    if (comanda == 1) {

    } else if (comanda == 2) {

    } else if (comanda == 3) {

    } else if (comanda == 4) {

    } else
        cout << "Comanda gresita!";
    return 0;
}