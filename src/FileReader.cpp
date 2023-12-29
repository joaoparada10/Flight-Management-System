#include "FileReader.h"
#include "Flight.h"

void FileReader::airlineMap(const std::string &filename,FMSGraph &ourGraph)
{
    std::ifstream inputFile(filename);

    if (inputFile.is_open())
    {
        std::string line;
        std::getline(inputFile, line);

        while(std::getline(inputFile,line))
        {
            std::istringstream iss(line);
            std::string Code,Name,Callsign,Country;

            if(std::getline(iss, Code,',') &&
               std::getline(iss, Name ,',') &&
               std::getline(iss, Callsign,',') &&
               std::getline(iss, Country,'\r'))
            {
                Airline newAirline = Airline(Code,Name,Callsign,Country);
                ourGraph.addAirline(newAirline);
            }
        }
    }

    inputFile.close();
}

void FileReader::addAirports(const std::string &filename, FMSGraph &OurGraph)
{
    std::ifstream inputFile(filename);

    if(inputFile.is_open())
    {
        std::string line;
        std::getline(inputFile, line);

        while(std::getline(inputFile,line))
        {
            std::istringstream iss(line);
            std::string Code,Name,City,Country,Latitude,Longitude;

            if( std::getline(iss, Code,',') &&
                std::getline(iss, Name,',') &&
                std::getline(iss, City,',') &&
                std::getline(iss, Country,',') &&
                std::getline(iss, Latitude,',') &&
                std::getline(iss, Longitude,'\r'))
            {
                Airport newAirport = Airport(Code,Name,City,Country,std::stol(Latitude),std::stol(Longitude));
                OurGraph.addAirport(newAirport);
            }
        }
    }

    inputFile.close();
}

void FileReader::addFlights(const std::string &filename, FMSGraph &ourGraph)
{
    std::ifstream inputFile(filename);

    if(inputFile.is_open())
    {
        std::string line;
        std::getline(inputFile, line);

        while(std::getline(inputFile,line))
        {
            std::istringstream iss(line);
            std::string Source,Target,AirlineCode;

            if(std::getline(iss, Source,',') &&
               std::getline(iss, Target,',') &&
               std::getline(iss, AirlineCode,'\r'))
            {
                Airport sourceAirport = ourGraph.findAirport(Source);
                Airport targetAirport = ourGraph.findAirport(Target);
                Airline airline = ourGraph.getAirline(AirlineCode);

                Flight newFlight = Flight(sourceAirport,targetAirport,airline);
                ourGraph.addFlight(newFlight);
            }
        }

    }








}