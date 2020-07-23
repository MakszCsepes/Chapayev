#ifndef CHAPAEV_CCELL_H
#define CHAPAEV_CCELL_H

#include "IInterface.h"
#include <iostream>

const sf::Color EVEN_CELL_FILL_COLOR(10, 150, 50);
const sf::Color ODD_CELL_FILL_COLOR(160, 150, 50);
const sf::Color CELL_OUTLINE_COLOR(250, 250, 250);

const int CELL_SIZE = 50.f;

const int CELL_THICKNESS = 2;

const int BOARD_POSITION_X = 350;
const int BOARD_POSITION_Y = 150;

extern sf::RenderWindow window;

class CCell: public IDrawable {
    int logic_x;
    int logic_y;

    int virtual_x;
    int virtual_y;
public:
    CCell(){

    }
    CCell(int x, int y) {
        logic_x = x;
        logic_y = y;
    }
    void draw() override;
    void set_coordinates(int&, int&);
};


#endif //CHAPAEV_CCELL_H
