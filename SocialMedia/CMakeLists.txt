cmake_minimum_required(VERSION 3.24)
project(SocialMedia)

set(CMAKE_CXX_STANDARD 17)

add_executable(SocialMedia main.cpp db/InitializeDB.cpp models/Chat.h db/handler/HandlerNewsDB.h db/handler/HandlerMessageDB.h db/handler/HandlerFriendDB.h models/Message.h db/handler/HandlerFriendRequest.h models/Friend.h models/FriendRequest.h db/handler/GlobalFunction.h db/testare.cpp Client.cpp ServerRegister.cpp models/Passwords.h db/handler/HandlerPasswordsDB.h db/handler/HandlerUserDB.h ServerLogin.cpp ServerGetUser.cpp ServerGetFriendRequests.cpp ServerNewsGet.cpp ServerCreeateNews.cpp ServerSearchNewsLogged.cpp)
