//
// Salut
//
#include <iostream>
// #include"handler/GlobalFunction.h"
#include "handler/HandlerUserDB.h"
#include "handler/HandlerChatDB.h"
#include "handler/HandlerFriendDB.h"
#include "handler/HandlerFriendRequest.h"
#include "handler/HandlerMessageDB.h"
#include "handler/HandlerNewsDB.h"
using namespace std;

int main()
{
    User user;
    user.userName = "test username";
    user.firstname = "test firstname";
    user.lastname = "test lastname";
    user.userName = "test username";
    user.userName = "test username";
    // create the rest of the user

    HandlerUserDB handler;
    handler.createUser(user);

    User userGet = handler.getUser(1);
    cout << userGet.userName;
    cout << userGet.lastname;

    userGet.userName = "updated username";
    handler.updateUser(userGet);
    userGet = handler.getUser(1);
    cout << userGet.userName;

    handler.deleteUser(1);
    User userGet = handler.getUser(1);
}

/*
int main()
{
    string userName = "";
    string firstName = "";
    string lastName = "ioana";
    string birthday = "";
    string profileDescription = "";

    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {1, 4, 5};
    bool accept = 0;
    int id1 = 4;
    int id2 = 4;
    User user(id1, accept, userName, firstName, lastName, lastName, birthday, profileDescription);
    News news(id1, id2, lastName, userName, firstName);
    Message message(id1, id2, lastName, userName);
    FriendRequest friendRequest(id1, id2, lastName, accept);
    Friend friendd(id1, id2, firstName);
    Chat chat(id1, v1, v2, lastName);

    HandlerUserDB a;
    HandlerChatDB b;
    HandlerFriendDB c;
    HandlerFriendRequestDB d;
    HandlerMessageDB e;
    HandlerNewsDB f;

    a.createUser(user);
    a.getUser(id1);
    a.deleteUser(id2);
    a.updateUser(user);
    std::cout << "It works!" << '\n';
    b.CreateChat(chat);
    // b.getChat(id2);   ///Am aici un segmentation faul si nu pot sa l rezolv.
    b.deleteChat(id1);
    b.updateChat(chat);
    std::cout << "It works!" << '\n';
    c.createFriend(friendd);
    c.getFriend(id1, id2);
    c.deleteFriend(id1, id2);
    c.updateFriend(friendd);
    std::cout << "It works!" << '\n';

    d.createFriendRequest(friendRequest);
    d.getFriendRequest(id1, id2);
    d.deleteFriendRequest(id1, id2);
    d.updateFriendRequest(friendRequest);
    std::cout << "It works!" << '\n';
    e.createMessage(message);
    e.getMessage(id1, id2);
    e.deleteMessage(id1, id2);
    e.updateMessage(message);
    std::cout << "It works!" << '\n';
    f.createNews(news);
    f.getNews(id1, id2);
    f.deleteNews(id1, id2);
    f.updateNews(news);
    // std::cout<<"It works!"<<'\n';
}
*/