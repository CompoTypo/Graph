#ifndef VERT_HPP
#define VERT_HPP

#include <string>
#include "./../linkedList.hpp"

struct vert {
    std::string name;
    LinkedList edges;
    vert *next;

    vert() {
        name = "";
        next = NULL;
    }

    vert(std::string i1) {
        name = i1;
        next = NULL;
    }
};
#endif