#include "CBoard.h"

extern sf::RenderWindow window;

void CBoard::draw_cell(int& y, int& x) {
    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));

    cell.setPosition(x*CELL_SIZE + BOARD_POSITION_X, y*CELL_SIZE + BOARD_POSITION_Y);
    cell.setOutlineThickness(CELL_THICKNESS);

    if ((y + x) % 2 == 0) {
        cell.setFillColor(EVEN_CELL_FILL_COLOR);
    } else {
        cell.setFillColor(ODD_CELL_FILL_COLOR);
    }
    cell.setOutlineColor(CELL_OUTLINE_COLOR);

    window.draw(cell);
}
void CBoard::draw() {
    for(int i = 0; i < BOARD_HEIGHT ; i++) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            draw_cell(i, j);
        }
    }
}
