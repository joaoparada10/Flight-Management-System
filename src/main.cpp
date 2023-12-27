//
// Created by jonas on 26/12/2023.
//
#include "FileReader.h"
#include <iostream>
#include <filesystem>
#include "Menu.h"

int main(){
    std::cout << "Hello World" << std::endl;
    FMSGraph testGraph;
    FileReader::airlineMap("data/airlines.csv",testGraph);
    FileReader::addAirports("data/airports.csv", testGraph);
    FileReader::addFlights("data/flights.csv",testGraph);
    Airline testAirline = testGraph.getAirline("RYR");
    std::cout << testAirline.getCode() << " " << testAirline.getName() << " " << testAirline.getCallsign() << " "
    << testAirline.getCountry() << std::endl;
    testGraph.airportFlightCount();
    testGraph.flightsPerAirport("OPO");
    testGraph.flightsPerCity("lisbon");
    testGraph.flighsPerAirline("IBE");
    testGraph.numOfDestinationsCity("lisbo");
    testGraph.numOfDestinationsAirport("orp");
    Menu menu;
    menu.getMainMenu(testGraph);
    
    return 0;
}