cmake_minimum_required(VERSION 3.24)
project(SocialMedia)

set(CMAKE_CXX_STANDARD 17)

add_executable(SocialMedia main.cpp db/InitializeDB.cpp db/handler/HandlerUserDB.h models/Chat.h db/handler/HandlerNewsDB.h db/handler/HandlerMessageDB.h db/handler/HandlerFriendDB.h models/Message.h db/handler/HandlerFriendRequest.h models/Friend.h models/FriendRequest.h db/handler/GlobalFunction.h db/testare.cpp)
