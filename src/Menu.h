//
// Created by António Cunha on 26/12/2023.
//

#ifndef PROJETO2_MENU_H
#define PROJETO2_MENU_H


class Menu {
private:
    int menuState;
public:
    Menu();
    void getFlightMenu(FMSGraph graph);
    void getStatMenu(FMSGraph graph);
    void getMainMenu(FMSGraph graph);
    void getExtrasMenu(FMSGraph graph);
    void menuPush(int i);
};


#endif //PROJETO2_MENU_H
