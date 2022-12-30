//
// Created by lolluckestar on 29.12.2022.
//
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
/*
    HandlerUserDB handler;
    handler.createUser(user);


    User userGet = handler.getUser(1);
    cout << userGet.userName<<'\n';
    cout << userGet.lastname<<'\n';


    user.userName = "updated username";
    handler.updateUser(userGet);
    userGet = handler.getUser(1);
    cout << user.userName<<'\n';


/*
    handler.deleteUser(1);
    userGet = handler.getUser(1);
    cout<<userGet.id;

News news;
news.type="avs";
news.content="asd";
news.title="ion";
news.authorId=0;

HandlerNewsDB handler;
handler.createNews(news);
News getNews=handler.getNews(1,0);

getNews.title="Try";
handler.updateNews(getNews);
News test = handler.getNews(1,0);
cout<<test.title<<'\n';
//handler.deleteNews(1,2);

Message message;
message.chatId=0;
HandlerMessageDB handler;

handler.createMessage(message);
handler.getMessage(1,0);
handler.updateMessage(message);
//handler.deleteMessage(1,0);
*/

FriendRequest friendRequest;
friendRequest.id1=0;
friendRequest.id2=1;
HandlerFriendRequestDB handler;
handler.createFriendRequest(friendRequest);

handler.getFriendRequest(1,0);
handler.updateFriendRequest(friendRequest);
/*
Chat chat;
chat.idChat=0;
HandlerChatDB handler;
handler.CreateChat(chat);
handler.getChat(1);
handler.updateChat(chat);
handler.deleteChat(1);
 */
/*
Friend friendd;
HandlerFriendDB handler;
handler.createFriend(friendd);
handler.getFriend(1,0);
handler.updateFriend(friendd);
//handler.deleteFriend(1,0);
 */
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