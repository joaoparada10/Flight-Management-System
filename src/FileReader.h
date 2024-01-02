//
// Created by Asus on 25/12/2023.
//

/**
 * @file Filereader.h
 * @brief Header file for the Airline class which is respomsible
 * for the input of information about the airports, airlines and its connections
 */

#ifndef AEDPROJ2_FILEREADER_H
#define AEDPROJ2_FILEREADER_H

#include "Airline.h"
#include "Airport.h"
#include "FMSGraph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class FileReader
{
public:
    static void airlineMap(const std::string &filename, FMSGraph &OurGraph);
    static void addAirports(const std::string &filename, FMSGraph &OurGraph);
    static void addFlights(const std::string &filename, FMSGraph &OurGraph);
};

#endif //AEDPROJ2_FILEREADER_H
