//
// Created by jonas on 17/12/2023.
//

/**
 * @file FMSGraph.cpp
 * @brief Implementation of the FMSGraph class methods
 */

#include <iostream>
#include <algorithm>
#include <cctype>
#include <vector>
#include "FMSGraph.h"


void FMSGraph::addAirline(Airline& airline)
{
    std::string code = airline.getCode();
    this->airlinesMap.insert(std::make_pair(code,airline));

}

void FMSGraph::removeAirline(Airline& airline)
{
    auto it = airlinesMap.find(airline.getCode());

    if (it != airlinesMap.end())
    {
        airlinesMap.erase(it);
    }
}

void FMSGraph::addAirport(Airport& airport)
{
    addVertex(airport);
}
void FMSGraph::removeAirport(const Airport& airport)
{
    removeVertex(airport);
}



void FMSGraph::addFlight(Flight& flight)
{
    addEdge(flight.getSource(),flight.getTarget(),flight.getAirline().getCode());
}


void FMSGraph::removeFlight(Flight& flight)
{
    removeEdge(flight.getSource(),flight.getTarget());
}

Airport FMSGraph::findAirport(std::string code)
{
    vector<Vertex<Airport> * > airports = getVertexSet();

    for (auto v : airports)
    {
        if (v->getInfo().getCode() == code)
        {
            return v->getInfo();
        }
    }
}


Airline FMSGraph::getAirline(std::string code)
{
    auto it = airlinesMap.find(code);
    if (it != airlinesMap.end()) {
        return it->second;
    }
}

/**
 * Function that shows the global number of airports and the global number of flights
 * Time Complexity: O(N)
 */

void FMSGraph::airportFlightCount() {                //i.
    int airportCount = 0;
    int flightCount = 0;
    for (auto v : getVertexSet()){
        airportCount++;
        flightCount += v->getAdj().size();
    }
    std::cout << "Global number of airports: " << airportCount << std::endl;
    std::cout << "Global number of flights: " << flightCount << std::endl;
}

void FMSGraph::flightsPerAirport(std::string code) {            //ii.
    Airport airport = findAirport(code);
    set<Airline> airlines;
    auto v = findVertex(airport);
    int flightCount = v->getAdj().size();
    for (auto e : v->getAdj()){
        airlines.insert(getAirline(e.getWeight()));
    }
    int airLineCount = airlines.size();
    std::cout << airport.getName() << " has " << flightCount << " outgoing flights from " << airLineCount
    << " different airlines." << std::endl;
}


vector<Vertex<Airport> * > FMSGraph::getAirports() const
{
    return getVertexSet();
}

void FMSGraph::flightsPerCity(std::string city)             //iii.
{
    /**
     * @return Returns the number of diferent departures occur in a city ( it can have different airports)
     *
     * @param city the name of the city we want to know how many fights has
     *
     * @complexity o(n)
     */

    std::string city2 = city;
    std::transform(city2.begin(), city2.end(), city2.begin(), ::tolower);
    city2[0] = std::toupper(city2[0]);

    int numOfFlights = 0;


    for(auto airport : getAirports())
    {
        if(airport->getInfo().getCity() == city2)
        {
            numOfFlights += airport->getAdj().size();
        }
    }

    std::cout << "There are " << numOfFlights << " out of the city of " << city2 << std::endl;
}

void FMSGraph::flighsPerAirline(std::string airline)                //iii.
{
    /**
     * @return Returns the number of flights that each airline can do
     *
     * @param airline the code of the airline that we want to know how many fights does
     *
     * @complexity o(n * m)
     */

    int numOfFlights = 0;

    for( auto airports : getAirports())
    {
        for(auto flight : airports->getAdj())
        {
            if(flight.getWeight() == airline)
            {
                numOfFlights += 1;
            }
        }
    }

    std::cout << "There are " << numOfFlights << " from " << airlinesMap.find(airline)->second.getName() << std::endl;
}

void FMSGraph::numOfDestinationsCity(std::string city)            //iv.
{
    /**
     * @return Returns the number of diferent countries that a city has connections to
     *
     * @param city the name of the departure city
     *
     * @complexity o(n * (m + k))
     */

    std::string city2 = city;
    std::transform(city2.begin(), city2.end(), city2.begin(), ::tolower);
    city2[0] = std::toupper(city2[0]);

    vector<std::string> difCountries;

    for(auto airport : getAirports())
    {
        if(airport->getInfo().getCity() == city2)
        {
            for(auto destinations : airport->getAdj())
            {
                auto it = std::find(difCountries.begin(), difCountries.end(),destinations.getDest()->getInfo().getCountry());

                if( it == difCountries.end())
                {
                    difCountries.push_back(destinations.getDest()->getInfo().getCountry());
                }
            }
        }
    }

    if(!difCountries.empty())
        std::cout << "The city of " << city2 << " has a number of " << difCountries.size() << " possible destinations." << std::endl;

    else
        std::cout << "The city of " << city2 << " was not found or it does not have an airport" << std::endl;
}

void FMSGraph::numOfDestinationsAirport(std::string code)           //iv.
{
    /**
     * @return Returns the number of diferent countries that an airport has connections to
     *
     * @param code The unique code of each airport
     *
     * @complexity o(n * (m + k))
     */
    std::string code2 = code;
    std::transform(code2.begin(), code2.end(), code2.begin(), ::toupper);


    vector<std::string> difCountries;


        for (auto airport: getAirports())
        {
            if (airport->getInfo().getCode() == code2)
            {
                for (auto destinations: airport->getAdj())
                {
                    auto it = std::find(difCountries.begin(), difCountries.end(),destinations.getDest()->getInfo().getCountry());
                    if (it == difCountries.end())
                    {
                        difCountries.push_back(destinations.getDest()->getInfo().getCountry());
                    }
                }
            }
        }


    if (difCountries.size() > 0)
    {
        std::cout << "The airport " << findAirport(code2).getName() << " has a number of " << difCountries.size() << " possible different countries as destination" << std::endl;
    }
    else
    {
        std::cout << "Airport not found" << std::endl;
    }

}
void FMSGraph::airportDestinations(std::string code) {      //v.
    set<std::string> airportCount;
    set<std::string> cityCount;
    set<std::string> countryCount;
    auto v = findVertex(findAirport(code));
    for (auto e : v->getAdj()){
        airportCount.insert(e.getDest()->getInfo().getName());
        cityCount.insert(e.getDest()->getInfo().getCity());
        countryCount.insert(e.getDest()->getInfo().getCountry());
    }
    std::cout << "The airport " << code << " has the following number of destinations: " << std::endl;
    std::cout << "- " << airportCount.size() << " different airports." << std::endl;
    std::cout << "- " << cityCount.size() << " different cities." << std::endl;
    std::cout << "- " << countryCount.size() << " different countries." << std::endl;

}
void FMSGraph::reachableDestinationsInXStops(std::string code, int n) {          //vi.
    set<std::string> airportCount;
    set<std::string> cityCount;
    set<std::string> countryCount;
    auto s = findVertex(findAirport(code));
    if (s == nullptr) {
        std::cout << "The airport with the code " << code << " doesn't exist." << std::endl;
        return;
    }
    queue<Vertex<Airport>*> q;
    for (auto v : getVertexSet())
        v->setVisited(false);
    q.push(s);
    s->setVisited(true);
    int stops = 0;
    while (!q.empty() && stops <= n) {
        int currentLevelSize = q.size();  // Number of nodes at the current level
        for (int i = 0; i < currentLevelSize; ++i) {
            auto v = q.front();
            q.pop();
            for (auto& e : v->getAdj()) {
                auto w = e.getDest();
                airportCount.insert(w->getInfo().getCode());
                cityCount.insert(w->getInfo().getCity());
                countryCount.insert(w->getInfo().getCountry());
                if (!w->isVisited()) {
                    q.push(w);
                    w->setVisited(true);
                }
            }
        }
        stops++;
    }
    std::cout << "The airport " << code << " can reach the following number of destinations in a maximum of " <<
              n << " stops:" << std::endl;
    std::cout << "- " << airportCount.size() << " different airports." << std::endl;
    std::cout << "- " << cityCount.size() << " different cities." << std::endl;
    std::cout << "- " << countryCount.size() << " different countries." << std::endl;
}

void FMSGraph::maxTrip()            //vii.
{
    /**
     * @return Returns the pairs that have the most conections between them
     *
     * @complexity o(n * (v + e))
     */

    vector<vector<Airport>> maxtrips;
    vector<Airport> maxTrip;

    for (auto& airport : getAirports())
    {
        vector<Airport> trip = dfs(airport->getInfo());

        if (trip.size() > maxTrip.size())
        {
            maxTrip = trip;
            maxtrips.clear();
            maxtrips.push_back(maxTrip);
        }
        else if (trip.size() == maxTrip.size())
        {
            maxtrips.push_back(trip);
        }
    }

    if (!maxtrips.empty())
    {
        std::cout << "The maximum trips start at: " << std::endl << std::endl;

        for (auto& trip : maxtrips)
        {
            std::cout << trip[0].getName() << " in " << trip[0].getCountry() << std::endl;
            std::cout << trip[trip.size() - 1].getName() << " in " << trip[trip.size() - 1].getCountry() << std::endl;
            std::cout << "-----" << std::endl;
        }
    }
    else
    {
        std::cout << "No maximum trips found." << std::endl;
    }
}

void FMSGraph::topAirports(int numOfAirports)           //viii.
{
    /**
     * @return Returns the top k airports with more traffic
     *
     * @param numOfAirports the top number of airpots we want to get
     *
     * @complexity O(v + e + v * log(v))
     */

    std::unordered_map<std::string, int> airportFlightsCount;

    for (auto flight : getAirports()) // criar um unordered map de airports com contagem 0
    {
        airportFlightsCount.insert(std::make_pair(flight->getInfo().getCode(),0));
    }

    for(auto airport : getAirports())
    {
        for(auto flights : airport->getAdj())
        {
            airportFlightsCount[airport->getInfo().getCode()] = airportFlightsCount[airport->getInfo().getCode()] + 1;
            airportFlightsCount[flights.getDest()->getInfo().getCode()] = airportFlightsCount[flights.getDest()->getInfo().getCode()] + 1;
        }
    }

    std::vector<std::pair<std::string, int>> vectorAirports(airportFlightsCount.begin(), airportFlightsCount.end());
    std::sort(vectorAirports.begin(), vectorAirports.end(),[](const auto& a, const auto& b)
              {
                  return a.second > b.second;
              });

    std::cout << "The top " << numOfAirports << " are:" << std::endl;

    for(int i = 0; i < numOfAirports; i++)
    {
        std::cout << i + 1 << " - ";
        std::cout << findAirport(vectorAirports[i].first).getName() << "(" << findAirport(vectorAirports[i].first).getCode()  << ")"
                  << " in " << findAirport(vectorAirports[i].first).getCity() << ", " << findAirport(vectorAirports[i].first).getCountry()
                  <<  " with a total of " << vectorAirports[i].second << " total flights." << std::endl;
    }
}

void FMSGraph::essentialAirports()
{
    vector<Airport> essentialAirports;

    for(auto& airport : getAirports())
    {

    }

}

void FMSGraph::connectedComponentsDfsVisit(Vertex<Airport>* v, set<std::string> & airportCount) {
    v->setVisited(true);
    for (auto & e : v->getAdj()) {
        auto w = e.getDest();
        airportCount.insert(w->getInfo().getCode());
        if ( ! w->isVisited())
            connectedComponentsDfsVisit(w, airportCount);
    }
}
int FMSGraph::connectedComponents() {
    int counter = 0;
    set<std::string> airportCount;
    for (auto v : getVertexSet()) v->setVisited(false);
    for (auto v : getVertexSet()){
        if (!v->isVisited()){
            counter++;
            connectedComponentsDfsVisit(v,airportCount);
            std::cout << "Size of " << counter << "th component:" << airportCount.size() << std::endl;
            airportCount.clear();
        }
    }
    return counter;
}


