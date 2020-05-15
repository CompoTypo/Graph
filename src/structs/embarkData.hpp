#ifndef EMBARKDATA_HPP
#define EMBARKDATA_HPP

#include <string>

struct embarkData {
    std::string origin, dest, weightType;

    embarkData() {
        origin = "";
        dest = "";
        weightType = "";
    }

    embarkData(std::string i1, std::string i2, std::string i3) {
        origin = i1;
        dest = i2;
        weightType = i3;
    }
};


#endif