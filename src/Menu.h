//
// Created by António Cunha on 26/12/2023.
//

#ifndef PROJETO2_MENU_H
#define PROJETO2_MENU_H

#include <stack>

class Menu {
private:
    int menuState;
public:
    Menu();
    void menuSwitch();
    void getFlightMenu();
    void getStatMenu();
    void getMainMenu();
    void getExtrasMenu();
    void menuPush(int i);
};


#endif //PROJETO2_MENU_H
