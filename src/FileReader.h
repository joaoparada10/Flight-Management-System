//
// Created by Asus on 25/12/2023.
//

#ifndef AEDPROJ2_FILEREADER_H
#define AEDPROJ2_FILEREADER_H

#include "Airline.h"
#include "Airport.h"
#include "Flight.h"
#include "FMSGraph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class FileReader
{
public:
    void airlineMap(const std::string &filename, FMSGraph &OurGraph);
    void addAirports(const std::string &filename, FMSGraph &OurGraph);
    void addFlights(const std::string &filename, FMSGraph &OurGraph);
};

#endif //AEDPROJ2_FILEREADER_H
