//
// Created by António Cunha on 26/12/2023.
//

#include "Menu.h"
#include <iostream>
using namespace std;

Menu::Menu(){
    getMainMenu();
}
void Menu::menuPush(int i){
        menuStack.push(i);
        menuSwitch();
    }

void Menu::getMainMenu() {
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
            menuPush(1);
            break;
        case 2 : 
            menuPush(2);
            break;
        case 3 :
            menuPush(3);
            break;
        case 4 :
            menuPush(4);
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
    }
}

void Menu::menuSwitch(){
    switch(menuStack.top()){
        case 1:
            getStatMenu();
            break;
        case 2:
            getFlightMenu();
            break;
        case 3:
            getExtrasMenu();
            break;
        case 4:
            menuStack.pop();//This isn't right , you should actually end the program
            menuSwitch();
        default:
            cout<< "Something is wrong";
    }
}

    void Menu::getStatMenu(){
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
    }
    void Menu::getFlightMenu(){
        cout<<"----Flight Menu----";
        //WIP
        //CREATE DIFFERENT CIN FOR EVERY CRITERIA
    }
    void Menu::getExtrasMenu(){
        cout<<"----Extras Menu----";
        //WIP
        //MAYBE DESIGN THE FLIGHT FILTERS ACCESS HERE ?
    }




