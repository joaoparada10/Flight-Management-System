//
// Created by António Cunha on 26/12/2023.
//


/**
 * @file Flight.h
 * @brief Header file for the Flight class
 */

#ifndef PROJETO2_MENU_H
#define PROJETO2_MENU_H
#include "FMSGraph.h"

class Menu {
private:
    FMSGraph globalGraph;
    FMSGraph filteredGraph;
    vector<Airline> airlines;
public:
    Menu(FMSGraph globalGraph);
    void getMainMenu(FMSGraph graph);
    void getFlightMenu(FMSGraph graph);
    void getStatMenu(FMSGraph graph);
    void getFilterMenu(FMSGraph graph);
    FMSGraph getGlobalGraph();
    FMSGraph getFilteredGraph();
    void setFilteredGraph(FMSGraph filteredGraph);
    void resetAirlineFilter() {
        airlines.clear();
    }

};


#endif //PROJETO2_MENU_H
