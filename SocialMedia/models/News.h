//
// Created by lolluckestar on 27.11.2022.
//

#ifndef PROIECT_NEWS_H
#define PROIECT_NEWS_H

#include <iostream>
#include <string>

struct News {
    int id;
    int authorId;

    std::string title;
    std::string content;
    std::string type;


    News()=default;

    News(
            int id,
            int authorId,
            std::string title,
            std::string content,
            std::string type
    ){
        this->id=id;
        this->authorId=authorId;
        this->title=title;
        this->content=content;
        this->type=type;
    }
};


#endif //PROIECT_NEWS_H
