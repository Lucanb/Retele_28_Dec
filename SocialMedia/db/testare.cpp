//
// Created by lolluckestar on 29.12.2022.
//
//
// Salut
//
#include <iostream>
#include"handler/GlobalFunction.h"
#include "handler/HandlerUserDB.h"
#include "handler//HandlerPasswordsDB.h"

#include "handler/HandlerChatDB.h"
#include "handler/HandlerFriendDB.h"
#include "handler/HandlerFriendRequest.h"
#include "handler/HandlerMessageDB.h"
#include "handler/HandlerNewsDB.h"
using namespace std;

int main() {
    /*

    User user;

   // user.userName = "test username 2";
   //  user.firstname = "test firstname 2";
   //  user.lastname = "test lastname 2";

//      User(user.toJson());

    HandlerUserDB handler;
//    handler.createUser(user);


    User userGet = handler.getUser(1);
    cout << userGet.userName<<'\n';
    cout << userGet.lastname<<'\n';


   // user.userName = "updated username";
   // handler.updateUser(userGet);
  //  userGet = handler.getUser(1);
    //cout << user.userName<<'\n';



  //       handler.deleteUser(1);
    //     userGet = handler.getUser(1);
   //       cout<<userGet.id;

/*
   News news;
   news.type="avs";
   news.content="asd";
   news.title="ion";
   news.authorId=2;
   news.id=1;

   HandlerNewsDB handler;

//    handler.createNews(news);
   // News getNews=handler.getNews(1,0);

   // getNews.title="Try";
   // handler.updateNews(getNews);

    //News test = handler.getNews(1,0);
   // cout<<test.title<<'\n';

    //handler.deleteNews(test.id,test.authorId);
   // handler.getNews(1,2);
   handler.getNewsByTitle("ion");


    Message message;
    message.chatId=0;
    HandlerMessageDB handler;
    handler.createMessage(message);
    handler.getMessage(1,0);
    handler.updateMessage(message);
    handler.deleteMessage(1,0);
    handler.getMessage(1,0);
/*
*/
    FriendRequest friendRequest;
    friendRequest.id1=0;
    friendRequest.id2=1;
    HandlerFriendRequestDB handler;
  //  handler.createFriendRequest(friendRequest);

  //  handler.getFriendRequest(friendRequest.id1,friendRequest.id2);
  //  handler.deleteFriendRequest(friendRequest.id1,friendRequest.id2);
  //  handler.updateFriendRequest(friendRequest);
  //  handler.deleteFriendRequest(friendRequest.id1,friendRequest.id2);
  //  handler.GetRequestNames("m");
  /*
  handler.GetRequestNames("test username 2");

    vector<int> v1,v2;
    v1.push_back(2);
    v2.push_back(3);
    v1.push_back(1);
    v2.push_back(4);
    Chat chat(1,v1,v2,"titlu");

      HandlerChatDB handler;
      handler.CreateChat(chat);
      handler.getChat(chat.idChat);
      handler.updateChat(chat);
      handler.deleteChat(1);
/*
Friend friendd;
HandlerFriendDB handler;
friendd.id1=0;
friendd.id2=1;
//handler.createFriend(friendd);
//handler.GetNames("test username 2");
//handler.updateFriend(friendd);
//handler.deleteFriend(friendd.id2,friendd.id1);
//handler.getFriend(friendd.id1,friendd.id2);


    Passwords passwords;
    HandlerPasswordsDB handler;
    passwords.userName="Luckya";
    passwords.password="asada";

    handler.createPassword(passwords);
    handler.getPassword("Luckya");

     Passwords getPass = handler.getPassword("Luckya");
  //  handler.updatePassword(getPass);
   // handler.deletePasswords(1);
   // handler.getPassword(1);

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