#ifndef CHAPAEV_CBOARD_H
#define CHAPAEV_CBOARD_H

#include "IInterface.h"
#include <iostream>

const int BOARD_HEIGHT = 8;
const int BOARD_WIDTH = 8;

const sf::Color EVEN_CELL_FILL_COLOR(198, 132, 69);
const sf::Color ODD_CELL_FILL_COLOR(108, 52, 0);
const sf::Color CELL_OUTLINE_COLOR(250, 250, 250);

const int CELL_SIZE = 50.f;

const int CELL_THICKNESS = 2;

const int BOARD_POSITION_X = 350;
const int BOARD_POSITION_Y = 150;

//using namespace std;

class CBoard : public IDrawable {

public:
    CBoard() {

    }
    ~CBoard(){

    }

    void draw_cell(int&, int&);
    void draw() override;
};


#endif //CHAPAEV_CBOARD_H
