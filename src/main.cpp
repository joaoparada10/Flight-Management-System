//
// Created by jonas on 26/12/2023.
//
#include "FileReader.h"
#include <iostream>
#include <filesystem>
#include "Menu.h"
#include "FMSGraph.h"

int main(){
    FMSGraph testGraph;
    FileReader::airlineMap("data/airlines.csv",testGraph);
    FileReader::addAirports("data/airports.csv", testGraph);
    FileReader::addFlights("data/flights.csv",testGraph);
    Menu menu;
    menu.getMainMenu(testGraph);
    return 0;
}