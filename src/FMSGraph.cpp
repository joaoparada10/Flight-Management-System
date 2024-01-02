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
#include <sstream>
#include <stack>
#include <complex>
#include <cfloat>
#include <map>
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
    addEdge(flight.getSource(),flight.getTarget(),flight);
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
    return Airport("","","","",0,0);
}


Airline FMSGraph::getAirline(std::string code)
{
    auto it = airlinesMap.find(code);
    if (it != airlinesMap.end()) {
        return it->second;
    }
    else return Airline("","","","");
}

void FMSGraph::airportFlightCount() {                //i.

    /**
     * @return Function that returns the global number of airports and the global number of flights
     *
     * Time Complexity O(N)
     */

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

    /**
     * @return Function that returns the global number of flights an airport has.
     *
     * @param code It takes the code of an airport
     *
     * Time Complexity O(N)
     */

    Airport airport = findAirport(code);
    set<Airline> airlines;
    auto v = findVertex(airport);
    int flightCount = v->getAdj().size();
    for (auto e : v->getAdj()){
        airlines.insert(e.getWeight().getAirline());
    }
    int airLineCount = airlines.size();
    std::cout << airport.getName() << " has " << flightCount << " outgoing flights from " << airLineCount
    << " different airlines." << std::endl;
}


vector<Vertex<Airport> * > FMSGraph::getAirports() const
{
    return getVertexSet();
}

Airport FMSGraph::getAirport(std::string code)
{
    for(auto airport : getAirports())
    {
        if(airport->getInfo().getCode() == code)
            return airport->getInfo();
    }
    return Airport("","","","",0,0);
}

string cityTransformer(string city)
{
    std::string city2 = city;
    std::transform(city2.begin(), city2.end(), city2.begin(), ::tolower);

    std::istringstream iss(city2);
    std::string word;
    string result;

    while (iss >> word) {
        word[0] = std::toupper(word[0]);
        if (!result.empty()) {
            result.append(" ");
        }
        result.append(word);
    }

    return result;
}



double toRadians(double degree)
{
    return degree * (M_PI / 180.0);
}

double Distance(const double latitude,const double longitude, const double latitude2, const double longitude2 )
{
    constexpr double earthRadius = 6371.0;

    double lat1 = toRadians(latitude);
    double lon1 = toRadians(longitude);
    double lat2 = toRadians(latitude2);
    double lon2 = toRadians(longitude2);

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = std::sin(dlat / 2) * std::sin(dlat / 2) +
               std::cos(lat1) * std::cos(lat2) *
               std::sin(dlon / 2) * std::sin(dlon / 2);

    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    double distance = earthRadius * c;

    return distance;
}

double calculateFullDistance(vector<Vertex<Airport>*> trip)
{
    double dist = 0;

    for (auto it = trip.begin(); it != std::prev(trip.end()); ++it) {

        Vertex<Airport>* currentAirport = *it;
        Vertex<Airport>* nextAirport = *(it + 1);

        dist = dist + Distance(currentAirport->getInfo().getLatitude(),currentAirport->getInfo().getLongitude(),nextAirport->getInfo().getLatitude(),nextAirport->getInfo().getLongitude());
    }
    return dist;
}

bool compareTrips(const vector<Vertex<Airport>*>& trip1, const vector<Vertex<Airport>*>& trip2) {
    return calculateFullDistance(trip1) < calculateFullDistance(trip2);
}


void FMSGraph::flightsPerCity(std::string city)             //iii.
{
    /**
     * @return Returns the number of different departures occur in a city ( it can have different airports)
     *
     * @param city the name of the city we want to know how many fights has
     *
     * Time Complexity O(n)
     */

    std::string city2 = cityTransformer(city);

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
     * Time Complexity O(n * m)
     */

    int numOfFlights = 0;

    for( auto airports : getAirports())
    {
        for(auto flight : airports->getAdj())
        {
            if(flight.getWeight().getAirline().getCode() == airline)
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
     * Time Complexity O(n * (m + k))
     */

    std::string city2 = cityTransformer(city);

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
     * Time Complexity O(n * (m + k))
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

    /**
     * @return Returns the number of destinations an airport has connection to
     *
     * @param code The unique code of each airport
     *
     * Time Complexity O(n * log(n))
     */

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

    /**
     * @return returns the different airports, countries and cities a airport can get to with an n amount of stops
     *
     * @param code, numOfStops The unique code of each airport and the number of stops you want to do
     *
     * Time Complexity O(V + E)
     */

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
void FMSGraph::maxTrip() {
    int maxStops = 0;
    vector<pair<Vertex<Airport>*,Vertex<Airport>*>> maxTripPairs;
    for(auto & v : getVertexSet()){
        v->setVisited(false);
        v->setDistance(0);
    }
    for (auto & v : getVertexSet()){
        queue<Vertex<Airport>*> q;
        q.push(v);
        v->setVisited(true);
        while(!q.empty()){
            auto u = q.front();
            q.pop();
            for (auto& e : u->getAdj()){
                auto  w = e.getDest();
                if (!w->isVisited()){
                    q.push(w);
                    w->setVisited(true);
                    w->setDistance(u->getDistance()+1);
                    if (w->getDistance() > maxStops) {
                        maxStops = w->getDistance();
                        maxTripPairs.clear();
                        maxTripPairs.push_back({w,u});
                    }
                    if (w->getDistance() == maxStops){
                        maxTripPairs.push_back({w,u});
                    }
                }
            }
        }
        for(auto & vertex : getVertexSet()){
            vertex->setDistance(0);
        }
    }

    std::cout << "The greatest number of stops of a trip is " << maxStops << std::endl;

    std::cout << "The trip(s) with the greatest number of stops: " << std::endl;
    for (const auto& p : maxTripPairs) {
        std::cout << "Source: " << p.first->getInfo().getName() << "(" << p.first->getInfo().getCode() <<
        ")" << std::endl;
        std::cout << "Destination: " << p.second->getInfo().getName() << "(" << p.second->getInfo().getCode()
        << ")" << std::endl;
        std::cout << std::endl;
    }
}

void FMSGraph::topAirports(int numOfAirports)           //viii.
{
    /**
     * @return Returns the top k airports with more traffic
     *
     * @param numOfAirports the top number of airpots we want to get
     *
     * Time Complexity O(v + e + v * log(v))
     */

    std::unordered_map<std::string, int> airportFlightsCount;

    for (auto flight : getAirports())
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
void FMSGraph::articulationDfs(Vertex<Airport>* v, set<Airport> & articulationAirports,stack<Airport> &s,int index){        //ix

    // funçao auxiliar para a funçao essential airports

    /**
     * @return Populates a set with the found articulation points
     *
     * @param startVertex, emptySet, emptyStack, index it is the initial point, articulation point storage, pushed to the stack as they are visited, "tracker"
     *
     * Time Complexity O(V + E)
     */

    v->setLow(index);
    v->setNum(index);
    index++;
    s.push(v->getInfo());
    int children = 0;
    for (auto e : v->getAdj()){
        auto w = e.getDest();
        if (w->getNum() == 0){
            children++;
            articulationDfs(w,articulationAirports,s,index);
            v->setLow(min(v->getLow(), w->getLow()));
            if ((v->getNum() == 1 && children > 1) || (v->getNum() > 1 && w->getLow() >= v->getNum()))
                articulationAirports.insert(v->getInfo());
            }
        else {
            stack<Airport> tempStack = s;
            while (!tempStack.empty()) {
                Airport tempVertexInfo = tempStack.top();
                tempStack.pop();
                if (w->getInfo() == tempVertexInfo) {
                    v->setLow(min(v->getLow(), w->getNum()));
                    break;
                }
            }
        }
    }
}

void FMSGraph::essentialAirports()
{

    /**
     * @return Identifies the airports that are essential to the network’s circulation capability
     *
     * Time Complexity O(V + E)
     */

    int index = 1;
    stack<Airport> s;
    set<Airport> articulationAirports;
    for (auto v : getVertexSet()){
        v->setVisited(false);
        v->setNum(0);
        v->setLow(0);
    }
    for (auto v : getVertexSet()){
        if (v->getNum() == 0){
            articulationDfs(v,articulationAirports,s, index);
        }
    }
    std::cout << "The essential " << articulationAirports.size() << " airports are the following: " << std::endl;
    for (auto a : articulationAirports){
        std::cout << a.getCode() << " " << a.getName() << std::endl;
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
int FMSGraph::connectedComponents() {   // not really used by the program. we used it to check
                                        // if some airports were isolated from the main network.
    /**
     * @return returns the size and the number of connected components in the graph
     *
     * Time Complexity O(V + V + E)
     */

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


int FMSGraph::lowestNumberOfStops(Vertex<Airport>* source, Vertex<Airport>* destination) {

    // auxiliar function of findAllShortestPathsBetweenAirports

    /**
     * @return returns the size and the number of connected components in the graph
     *
     * @param source,destination from where you want to start(Vertex<Airport>*) to where you want to go (Vertex<Airport>*)
     *
     * Time Complexity O(V + E)
     */

    queue<Vertex<Airport>*> q;
    Airport destinationAirport = destination->getInfo();
    q.push(source);

    for (auto v : getVertexSet()){
        v->setVisited(false);
        v->setDistance(0);
    }
    source->setVisited(true);
    while(!q.empty()){
        auto u = q.front();
        q.pop();
        for(auto e : u->getAdj()){
            auto w = e.getDest();
            if (!w->isVisited()){
                q.push(w);
                w->setVisited(true);
                w->setDistance(u->getDistance()+1);
                if (w->getInfo() == destination->getInfo()) return w->getDistance();
            }
        }
    }
    return -1;
}

set<vector<Vertex<Airport>*>> FMSGraph::findAllShortestPathsBetweenAirports(Vertex<Airport>* source, Vertex<Airport>* destination) {

    // auxiliar function of bestFlightOption

    /**
     * @return returns a set<vector<Vertex<Airport>*>> that are all the shortest path from a vertex to another
     *
     * @param source,destination from where you want to start(Vertex<Airport>*) to where you want to go (Vertex<Airport>*)
     *
     * Time Complexity O(V + E)
     */

    int d = lowestNumberOfStops(source, destination);
    set<vector<Vertex<Airport>*>> allPaths;
    queue<vector<Vertex<Airport>*>> q;

    for (auto v : getVertexSet()) {
        for (auto e : v->getAdj()) {
            e.setVisited(false);
        }
    }

    vector<Vertex<Airport>*> initialPath = {source};
    q.push(initialPath);

    while (!q.empty()) {
        vector<Vertex<Airport>*> currentPath = q.front();
        q.pop();

        Vertex<Airport>* u = currentPath.back();

        for (auto e : u->getAdj()) {
            Vertex<Airport>* w = e.getDest();

            if (!e.isVisited()) {
                vector<Vertex<Airport>*> newPath = currentPath;
                newPath.push_back(w);

                if (w == destination && newPath.size() == d + 1) {
                    // Found a valid path
                    allPaths.insert(newPath);
                } else if (newPath.size() < d + 1) {
                    e.setVisited(true);
                    q.push(newPath);
                }
            }
        }
    }
    return allPaths;
}

struct PathComparator {
    bool operator()(const std::vector<Vertex<Airport>*>& path1, const std::vector<Vertex<Airport>*>& path2) const {
        double distance1 = calculateFullDistance(path1);
        double distance2 = calculateFullDistance(path2);
        return distance1 < distance2;
    }
};

vector<vector<Flight>> FMSGraph::allPossibleFlightsPerTravel(vector<Vertex<Airport> *> path) {     //4
    vector<vector<Flight>> allPossibleFlights;
    set<Airline> airlines;
    for (int i = 0; i < path.size(); i++){
        vector<Flight> possibleFlights;
        if (i+1 == path.size()) {
            return allPossibleFlights;
        }
        for (auto e : path[i]->getAdj()){
            if (e.getDest() == path[i+1]){
                possibleFlights.push_back(e.getWeight());
            }
        }
        allPossibleFlights.push_back(possibleFlights);
    }
    return allPossibleFlights;
}

int FMSGraph::filterPerMinNumberOfAirlines(vector<vector<Flight>>& allPossibleFlights) {
    int maxCount = 0;
    int factor = 0;
    vector<pair<Airline, int>> airlineCounts;

    for (auto& flights : allPossibleFlights) {
        for (auto& flight : flights) {
            auto it = find_if(airlineCounts.begin(), airlineCounts.end(),
                              [&flight](const pair<Airline, int>& entry) {
                                  return entry.first == flight.getAirline();
                              });

            if (it != airlineCounts.end()) {
                it->second++;
            } else {
                airlineCounts.emplace_back(flight.getAirline(), 1);
            }
        }
    }
    for (const auto& entry : airlineCounts) {
        if (entry.second > maxCount) {
            maxCount = entry.second;
        }
        factor += entry.second - 1;
    }

    return factor;
}

void FMSGraph::bestFlightOptionsWithFilter(Vertex<Airport>* source , Vertex<Airport>* destination) {
    set<vector<Vertex<Airport> *>> possiblePaths;
    vector<vector<Flight>> allFlightsPath;
    vector<Airline> airlines;
    vector<vector<Flight>> optimizedPaths;
    int maxFactor = 0;
    int count = 1;
    possiblePaths = findAllShortestPathsBetweenAirports(source, destination);
    set<vector<Vertex<Airport> *>, PathComparator> sortedPaths;
    for (auto path: possiblePaths) {
        allFlightsPath = allPossibleFlightsPerTravel(path);
        if (maxFactor <= filterPerMinNumberOfAirlines(allFlightsPath)) {
            maxFactor = filterPerMinNumberOfAirlines(allFlightsPath);
        }
    }
    std::cout << "Your possible path(s) to your destination with the minimum number of different airlines are: "
              << std::endl;
    for (auto path: possiblePaths) {
        allFlightsPath = allPossibleFlightsPerTravel(path);
        if (maxFactor == filterPerMinNumberOfAirlines(allFlightsPath)) {
            std::cout << "Path " << count << " - (total distance: " << calculateFullDistance(path) << "KM) "
                      << std::endl;
            for (int i = 0; i < allFlightsPath.size(); i++) {
                std::cout << allFlightsPath[i][0].getSource().getName() << ", "
                          << allFlightsPath[i][0].getSource().getCountry() << "("
                          << allFlightsPath[i][0].getSource().getCode() << ") -> "
                          << allFlightsPath[i][0].getTarget().getName() << ", " <<
                          allFlightsPath[i][0].getTarget().getCountry() << "("
                          << allFlightsPath[i][0].getTarget().getCode() << ")" << std::endl;

                vector<Flight> availableFlights;
                for (int j = 0; j < allFlightsPath[i].size(); j++) availableFlights.push_back(allFlightsPath[i][j]);
                std::cout << "Available Airlines for this flight: ";
                for (int k = 0; k < availableFlights.size(); k++) {
                    Airline airline = availableFlights[k].getAirline();
                    if (k == availableFlights.size() - 1)
                        std::cout << airline.getName() << "(" << airline.getCode() << ")";
                    else std::cout << airline.getName() << "(" << airline.getCode() << "), ";
                }
                std::cout << std::endl;
                std::cout << std::endl;
            }
            std::cout << std::endl;
            count++;
            }
        }
}
void FMSGraph::bestFlightOptions(Vertex<Airport>* source , Vertex<Airport>* destination)
{
    set<vector<Vertex<Airport>*>> possiblePaths = findAllShortestPathsBetweenAirports(source,destination);
    int count = 1;
    set<vector<Vertex<Airport>*>,PathComparator> sortedPaths;
    for (auto p : possiblePaths){
        sortedPaths.insert(p);
    }

    std::cout << "Your possible path(s) to your destination is/are (ordered by total travel distance): " << std::endl;

    for(auto path : sortedPaths)
    {
        std::cout << "Path " << count << " - (total distance: " << calculateFullDistance(path) << "KM) " << std::endl;

        for(int i = 0; i < path.size()-1; i++)
        {
            std::cout << path[i]->getInfo().getName() << ", " << path[i]->getInfo().getCountry() << "("
                      << path[i]->getInfo().getCode() << ") -> " << path[i+1]->getInfo().getName() << ", " <<
                      path[i+1]->getInfo().getCountry() << "(" << path[i+1]->getInfo().getCode() << ")" << std::endl;

            vector<Flight> availableFlights;
            for ( auto e : path[i]->getAdj()){
                if (e.getDest() == path[i+1]) availableFlights.push_back(e.getWeight());
            }
            std::cout << "Available Airlines for this flight: ";
            for (int j = 0; j < availableFlights.size();j++){
                Airline airline = availableFlights[j].getAirline();
                if (j == availableFlights.size()-1) std::cout << airline.getName() << "(" << airline.getCode() << ")";
                else std::cout << airline.getName() << "(" << airline.getCode() << "), ";
            }
            std::cout << std::endl;
            std::cout << std::endl;
        }
        std::cout << std::endl;
        count++;
    }
}


Vertex<Airport>* FMSGraph::cityOption()
{

    /**
     * @return the chosen vertex
     *
     * Time Complexity O(V * E)
     */

    std::string city;
    int choice;
    vector<Airport> cityAir;
    int count = 1;


    std::cout << "What city will you be choosing?" << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, city);

    std::string city2 = cityTransformer(city);
    cityAir = cityAirports(city2);

    if(cityAir.empty())
    {
        std::cout << "City was not found or does not have any airports. " << std::endl;
        return nullptr;
    }
    else
    {
        std::cout << "What airport do you want to choose? (enter airport number) " << std::endl;

        for(auto airport : cityAir)
        {
            std::cout << count << " - " << airport.getName() << " (" << airport.getCode() << ")" << std::endl;
            count++;
        }

        std::cout << "Option number: ";
        std::cin >> choice;

        Airport chosenAirport = cityAir[choice - 1];

        return findVertex(chosenAirport);
    }
}

Vertex<Airport>* FMSGraph::airportOption()
{

    /**
     * @return the chosen vertex
     *
     * Time Complexity O(V * E)
     */

    std::string airportname;
    vector<Airport> Air;

    std::cout << "What airport will you be choosing?" << std::endl;
    std::cin >> airportname;
    std::string airportname2 = airportname;

    if(airportname.size() == 3)
    {
        std::transform(airportname2.begin(), airportname2.end(), airportname2.begin(), ::toupper);

        for(auto air : getAirports())
        {
            if(air->getInfo().getCode() == airportname2)
            {
                Air.push_back(air->getInfo());
            }
        }

        if(Air.empty())
        {
            std::cout << "Airport with code " << airportname2 << " was  not found. " << std::endl;
            return nullptr;
        }
        else
        {
            return findVertex(Air[0]);
        }

    }
    else
    {
        airportname2 = cityTransformer(airportname);

        for(auto air : getAirports())
        {
            if(air->getInfo().getName() == airportname2)
            {
                Air.push_back(air->getInfo());
            }
        }

        if(Air.size() == 0)
        {
            std::cout << "The airport " << airportname2 << " was not found. " << std::endl;
            return nullptr;
        }
        else
        {
            return findVertex(Air[0]);
        }
    }
}

Vertex<Airport>* FMSGraph::coordinatesOption()
{

    /**
     * @return the chosen vertex
     *
     * Time Complexity O(V * E)
     */


    double longitude;
    double latitude;
    auto distancee = DBL_MAX;
    vector<Airport> chosen;
    int count = 1;
    int choice;

    std::cout << "What are the coordinates where you are trying to find an airport " << std::endl;
    std::cout << "Latitude:";
    std::cin >> latitude;
    std::cout << "Longitude:";
    std::cin >> longitude;
    std::cout << std::endl;

    for(auto aiport : getAirports()){
        double d = Distance(latitude,longitude,aiport->getInfo().getLatitude(),aiport->getInfo().getLongitude());

        if(d < distancee)
        {
            distancee = d;
            chosen.clear();
            chosen.push_back(aiport->getInfo());
        }

        else if(d == distancee)
        {
            chosen.push_back(aiport->getInfo());
        }
    }

    std::cout<< "The closest airport/s is/are: " << std::endl;

    for(auto a : chosen)
    {
        std::cout << count << " - " << a.getName() << " (" << a.getCode() << ")" << std::endl;
        count++;
    }

    std::cout << "Choose the desired airport (select the airport number): ";
    std::cin >> choice;
    std::cout << std::endl;

    return findVertex(chosen[choice - 1]);
}

vector<Airport> FMSGraph::cityAirports(std::string city)
{
    vector<Airport> cityAir;

    for(auto airport : getAirports())
    {
        if(airport->getInfo().getCity() == city)
        {
            cityAir.push_back(airport->getInfo());
        }
    }

    return cityAir;
}

void FMSGraph::addAirlinesToFilter(vector<Airline>& airlines) {

    /**
     * @return prints messages to the console indicating the status of each operation
     *
     * @param airlines function adds new airlines to this vector based on user input.
     *
     * Time Complexity O(A⋅L+V⋅E)
     */

    vector<string> airlineCodes;
    string codes;
    cout << "Which airlines do you wish to add to your filter? Enter one or more airline codes (comma separated):" << endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, codes);
    stringstream ss(codes);
    string code;
    while (getline(ss, code, ',')) {
        code.erase(remove_if(code.begin(), code.end(), ::isspace), code.end());
        transform(code.begin(), code.end(), code.begin(), ::toupper);

        if (!code.empty())
            airlineCodes.push_back(code);
    }
    for (const string& airlineCode : airlineCodes) {
        Airline airline = getAirline(airlineCode);
        if (std::find(airlines.begin(), airlines.end(),airline) != airlines.end())
            cout << "Airline with code " << airline.getCode() << " is already in filter." << endl;
        else if (!airline.getCode().empty()) {
            airlines.push_back(airline);
            cout << airline.getCode() << " - " << airline.getName() << " (" << airline.getCountry() << ") was found and added to your filter." << endl;
        }
        else {
            cout << "Airline with code " << airlineCode << " is not a valid airline." << endl;
        }
    }
}

void FMSGraph::removeAirlinesFromFilter(vector<Airline>& airlines) {

    /**
     * @return The function removes airlines from this vector based on user input.
     *
     * @param airlines function removes airlines to this vector based on user input.
     *
     * Time Complexity O(A * F)
     */

    vector<string> airlineCodes;
    string codes;

    cout << "Which airlines do you want to remove from your filter? Enter one or more airline codes (comma separated):" << endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, codes);
    stringstream ss(codes);
    string code;

    while (getline(ss, code, ',')) {
        code.erase(remove_if(code.begin(), code.end(), ::isspace), code.end());
        transform(code.begin(), code.end(), code.begin(), ::toupper);

        if (!code.empty())
            airlineCodes.push_back(code);
    }
    for (const string& airlineCode : airlineCodes) {
        Airline airline = getAirline(airlineCode);
        auto it = std::find(airlines.begin(), airlines.end(),airline);
        if (it != airlines.end()) {
            airlines.erase(it);
            cout << airline.getCode() << " - " << airline.getName() << " (" << airline.getCountry() << ") was erased from your filter." << endl;
        } else if (airline.getCode().empty())
            cout << "Airline with code " << airlineCode << " is not a valid airline." << endl;
        else {
            cout << "Airline with code " << airline.getCode() << " is not in filter." << endl;
        }
    }
}

FMSGraph FMSGraph::applyAirlineFilter(vector<Airline> selectedAirlines) {

     /**
     * @return returns the filtered graph with or without the selected airlines
     *
     * @param airlines  selected airlines to be included in the filtered graph.
     *
     * Time Complexity O(A * (V + E))
     */

    FMSGraph filteredGraph;
    vector<string> airlineCodes;
    for (Airline a : selectedAirlines){
        airlineCodes.push_back(a.getCode());
        filteredGraph.addAirline(a);
    }
    for (auto v : getVertexSet()){
        for(auto e : v->getAdj()){
            auto it = std::find(airlineCodes.begin(), airlineCodes.end(),e.getWeight().getAirline().getCode());
            if (it != airlineCodes.end()){
                Airport source = v->getInfo();
                Airport destination = e.getDest()->getInfo();
                Flight flight = e.getWeight();
                filteredGraph.addAirport(source);
                filteredGraph.addAirport(destination);
                filteredGraph.addFlight(flight);
            }
        }
    }
    return filteredGraph;
}





