cmake_minimum_required(VERSION 3.24)
project(models)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(models
        Chat.h
        Friend.h
        FriendRequest.h
        Message.h
        News.h
        User.h)
