//
// Created by jonas on 26/12/2023.
//
#include "FileReader.h"
#include <iostream>
#include "Menu.h"
#include "FMSGraph.h"

int main(){
    std::cout << "Hello World :D" << std::endl;
    FMSGraph globalGraph;
    FileReader::airlineMap("data/airlines.csv",globalGraph);
    FileReader::addAirports("data/airports.csv", globalGraph);
    FileReader::addFlights("data/flights.csv",globalGraph);
    Menu menu(globalGraph);
    menu.getMainMenu(globalGraph);
    return 0;
}