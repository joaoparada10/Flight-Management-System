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

Airport FMSGraph::getAirport(std::string code)
{
    for(auto airport : getAirports())
    {
        if(airport->getInfo().getCode() == code)
            return airport->getInfo();
    }
}

std::string cityTransformer(std::string city)
{
    std::string city2 = city;
    std::transform(city2.begin(), city2.end(), city2.begin(), ::tolower);

    std::istringstream iss(city2);
    std::string word;
    std::ostringstream result;

    while (iss >> word) {
        word[0] = std::toupper(word[0]);
        result << word;

        if (!(iss >> word)) {
            break;
        }

        result << ' ';
    }

    return result.str();
}



double tooRadians(double degree) // funçao auxiliar para a funçao de cima
{
    return degree * (M_PI / 180.0);
}

double Distance(const double latitude,const double longitude, const double latitude2, const double longitude2 )
{
    constexpr double earthRadius = 6371.0;

    double lat1 = tooRadians(latitude);
    double lon1 = tooRadians(longitude);
    double lat2 = tooRadians(latitude2);
    double lon2 = tooRadians(longitude2);

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = std::sin(dlat / 2) * std::sin(dlat / 2) +
               std::cos(lat1) * std::cos(lat2) *
               std::sin(dlon / 2) * std::sin(dlon / 2);

    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    // Distance in kilometers
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
     * @return Returns the number of diferent departures occur in a city ( it can have different airports)
     *
     * @param city the name of the city we want to know how many fights has
     *
     * @complexity o(n)
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
void FMSGraph::articulationDfs(Vertex<Airport>* v, set<Airport> & articulationAirports,stack<Airport> &s,int index){
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


int FMSGraph::lowestNumberOfStops(Vertex<Airport>* source, Vertex<Airport>* destination) {
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
                    // Continue exploring the path
                    e.setVisited(true);
                    q.push(newPath);
                }
            }
        }
    }

    return allPaths;
}



void FMSGraph::bestFlightOption()
{
    Vertex<Airport>* source;
    Vertex<Airport>* destination;
    set<vector<Vertex<Airport>*>> possiblePaths;
    int choice;
    int choice2;
    int count = 1;

    std::cout << "Where from do you want to depart?" << std::endl;

    std::cout << "Search by:" << std::endl << "City - 1" << std::endl <<
                                              "Airport (code/name) - 2 " << std::endl <<
                                              "Coordinates - 3 " << std::endl;

    std::cout << "Option selected:";
    std::cin >> choice; // fazer switch case

    switch(choice){
        case 1: source = cityOption();
            break;
        case 2: source = airportOption();
            break;
        case 3: source = coordinatesOption();
            break;
        default: break;
    }

    std::cout << "Where to do you want to go?" << std::endl;

    std::cout << "Search by:" << std::endl << "City - 1" << std::endl <<
                 "Airport (code/name) - 2 " << std::endl <<
                 "Coordinates - 3 " << std::endl;

    std::cin >> choice2; // fazer switch case

    switch(choice2){
        case 1: destination = cityOption();
        break;
        case 2: destination = airportOption();
        break;
        case 3: destination = coordinatesOption();
        break;
        default: break;
    }

    possiblePaths = findAllShortestPathsBetweenAirports(source,destination);

    std::cout << "Your possible path(s) to your destination is/are (ordered by total travel distance): " << std::endl;

    for(auto path : possiblePaths)
    {
        std::cout << count << " - (total distance: " << calculateFullDistance(path) << "KM) ";

        for(auto airport : path)
        {
            std::cout << airport->getInfo().getName() <<  "(" << airport->getInfo().getCode() << ") " << " -> ";
        }
        std::cout << std::endl;
        count++;
    }
}

Vertex<Airport>* FMSGraph::cityOption()
{
    std::string city;
    int choice;
    vector<Airport> cityAir;
    int count = 1;


    std::cout << "What city will you be chosing?" << std::endl;
    std::cin >> city;

    std::string city2 = cityTransformer(city);
    cityAir = cityAirports(city2);

    if(cityAir.size() == 0)
    {
        std::cout << "City was not found or does not have any airports. " << std::endl;
        return nullptr;
    }
    else
    {
        std::cout << "What airport do you want to chose? (enter airport number) " << std::endl;

        for(auto airport : cityAir)
        {
            std::cout << count << " - " << airport.getName() << " (" << airport.getCode() << ")" << std::endl;
            count++;
        }

        std::cout << "Option number: ";
        std::cin >> choice;

        Airport chosenAirport = cityAir[choice - 1];

        return findVertex(chosenAirport); // returns  the airport u want
    }
}

Vertex<Airport>* FMSGraph::airportOption()
{
    std::string airportname;
    vector<Airport> Air;

    std::cout << "What airport will you be chosing?" << std::endl;
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
    double longitude;
    double latitude;
    auto distancee = DBL_MAX;
    vector<Airport> chosen;
    int count = 1;
    int choice;

    std::cout << "What are the coordenates where you are trying to find an airport " << std::endl;
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

    std::cout << "Chose the desired airport (select the airport number): ";
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

