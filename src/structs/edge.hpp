#ifndef EDGE_HPP
#define EDGE_HPP

#include <string>

struct edge {
    std::string name;
    float t, c;
    edge *next;

    edge() {
        name = "";
        t = c = 0;
        next = NULL;
    }

    edge(std::string i1, float i2, float i3) {
        name = i1;
        c = i2;
        t = i3;
        next = NULL;
    }
};
#endif