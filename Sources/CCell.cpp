#include "CCell.h"

extern sf::RenderWindow window;

void CCell::draw() {
    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));

    cell.setPosition(logic_x*CELL_SIZE + BOARD_POSITION_X, logic_y*CELL_SIZE + BOARD_POSITION_Y);
    cell.setOutlineThickness(CELL_THICKNESS);

    cell.setFillColor(EVEN_CELL_FILL_COLOR);
    cell.setOutlineColor(CELL_OUTLINE_COLOR);

    window.draw(cell);
}

void CCell::set_coordinates(int& y, int& x) {
    logic_y = y;
    logic_x = x;
}
