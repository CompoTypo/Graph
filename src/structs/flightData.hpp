#ifndef FLIGHTDATA_HPP
#define FLIGHTDATA_HPP

#include <string>

struct flightData {
    std::string origin, dest;
    float t, c;

    flightData() {
        origin = dest = "";
        t = c = 0;
    }

    flightData(std::string i1, std::string i2, float i3, float i4) {
        origin = i1;
        dest = i2;
        c = i3;
        t = i4;
    }
};
#endif