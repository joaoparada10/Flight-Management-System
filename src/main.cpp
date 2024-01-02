/**
* \mainpage Project Documentation

* Welcome to the documentation for our project.

* \section overview Overview


* This project aims to implement a system capable  of facilitating access and understanding of the air
  transport network. The main objective of this project is precisely to develop a
  flight management system for the air travel network of the airlines around the world that provides effective
  assistance to users who wish to explore and plan travel.

  Made by:

    João Parada - up201405280

    Luciano Ferreira - up202208158

    António Cunha - up202208862

**/
#include "FileReader.h"
#include <iostream>
#include <filesystem>
#include "Menu.h"
#include "FMSGraph.h"

int main(){
    std::cout << "Welcome to our Flight Management System." << std::endl;
    std::cout << "If no stats are showing, please make sure you set the working directory to project root." << std::endl;
    std::cout << "Current Working Directory: " << std::filesystem::current_path() << std::endl;
    std::cout << "Parsing files... Please wait." << std::flush;
    FMSGraph globalGraph;
    FileReader::airlineMap("data/airlines.csv",globalGraph);
    FileReader::addAirports("data/airports.csv", globalGraph);
    FileReader::addFlights("data/flights.csv",globalGraph);
    std::cout << '\r';
    Menu menu(globalGraph);
    menu.getMainMenu(globalGraph);
    return 0;
}