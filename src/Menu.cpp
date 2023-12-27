//
// Created by António Cunha on 26/12/2023.
//

#include "Menu.h"
#include <iostream>
#include "FMSGraph.h"
using namespace std;

//Menu::Menu(){
//    getMainMenu();
//}

void Menu::getMainMenu(FMSGraph graph) {
    cout<<"------FSM------";
    cout<<"1. Network Statistics";
    cout<<"2. Search Flight Options";
    cout<<"3. Extras";
    cout<<"4. Quit";
    cout<< "Select:";
    int selected;
    cin >> selected;
    switch (selected){
        case 1 :
            getStatMenu(graph);
            break;
        case 2 : 
            getFlightMenu(graph);
            break;
        case 3 :
            getExtrasMenu(graph);
            break;
        case 4 :
            exit(0);
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
}

void Menu::getStatMenu(FMSGraph graph){
    cout<<"----Stat Menu----";
    cout<<"1. Number of airports and available flights;";
    cout<<"2. Number of flights out of an airport and different airlines";
    cout<<"3. Number of flights per city/airline";
    cout<<"4. Number of different countries that a given airport/city flies to";
    cout<<"5. Number of destinations available for a given airport";
    cout<<"6. Number of reachable destinations from a given airport in a maximum number of X stops ";
    cout<<"7. Maximum trip and corresponding pair of source-destination airports";
    cout<<"8. Airport with the greatest air traffic capacity / with the greatest number of flights";
    cout<<"9. Essential airports to the networks circulation capability ";
    cout<<"10. Go back";
    cout<< "Select:";
    int selected;
    cin >> selected;
    int choice3, choice4, stops6, numAirports8;
    string city3, airline3, city4, airport4, code2, code5, airport6;
    switch(selected){
        case 1:
            graph.airportFlightCount();
            break;
        case 2:
            cout<<"Insert the airport code";
            cin>>code2;
            graph.flighsPerAirline(code2);
            break;
        case 3:
            cout << "Do you wish to search for :";
            cout << "1. City";
            cout << "2. Airline";
            cout << "Select:";
            switch(choice3){
                case 1:
                    cout<<"Input the city name";
                    cin >> city3;
                    graph.flightsPerCity(city3);
                    break;
                case 2:
                    cout<<"Input the airline name";
                    cin >> airline3;
                    graph.flighsPerAirline(airline3);
                    break;
                default:
                    cout <<"Please select a valid choice.";
            }
            break;

        case 4:
            cout << "Do you wish to search for :";
            cout << "1. City";
            cout << "2. Airport";
            cout << "Select:";
            cin >> choice4;

            switch(choice4){
                case 1:
                    cout<<"Input the city name";
                    cin >> city4;
                    graph.numOfDestinationsCity(city4);
                    break;
                case 2:
                    cout<<"Input the airport name";
                    cin >> airport4;
                    graph.numOfDestinationsAirport(airport4);
                    break;
                default:
                    cout <<"Please select a valid choice.";
            }
            break;

        case 5:

            cout << "Insert the airport code";
            cin >> code5;
            graph.airportDestinations(code5);
            break;

        case 6:

            cout << "Insert the airport code";
            cin >> airport6;
            cout << "Insert the number of stops";
            cin >> stops6;
            graph.reachableDestinationsInXStops(airport6, stops6);
            break;
        case 7:
            graph.maxTrip();
            break;
        case 8:

            cout << "Insert the number of airports on the list";
            cin >> numAirports8;
            graph.topAirports(numAirports8);
            break;
        case 9:
            break;
        case 10:
            getMainMenu(graph);
        default :
            cout << "Invalid choice. Please try again." << endl;
    }
}
void Menu::getFlightMenu(FMSGraph graph){
    cout<<"----Flight Menu----";
    //WIP
    //CREATE DIFFERENT CIN FOR EVERY CRITERIA
}
void Menu::getExtrasMenu(FMSGraph graph){
    cout<<"----Extras Menu----";
    //WIP
    //MAYBE DESIGN THE FLIGHT FILTERS ACCESS HERE ?
}




