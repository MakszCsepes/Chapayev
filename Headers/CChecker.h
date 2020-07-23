
#ifndef CHAPAEV_CCHECKER_H
#define CHAPAEV_CCHECKER_H

#include "CBoard.h"
#include "IObjectState.h"
extern sf::RenderWindow window;

static float CHECKER_OUTLINE_THICKNESS = 1.0;

const sf::Color CHECKER_FILL_COLOR = sf::Color::Black;
const sf::Color CHECKER_OUTLINE_COLOR = sf::Color::White;
const sf::Color SELECTED_CHECKER_OUTLINE_COLOR = sf::Color::Red;

const int USER_OWNERSHIP = 1;
const int USER_POSITION_Y = 7*CELL_SIZE;

const int AI_OWNERSHIP = 2;
const int AI_POSITION_Y = 0;

class CChecker: public IDrawable, public IObjectState {
    int ownership;

    bool clicked;
    bool selected;

public:
    double velocity_x;
    double velocity_y;

    double acceleration_x;
    double acceleration_y;

    bool moving;

    int number;
    int time_v;
    int start_frame;

    dot clicked_dot;
    dot old_center;
    dot center;
    dot destination_dot;

    CChecker() {
    }
    CChecker(int n, int own) {
        number = n;
        ownership = own;

        clicked = false;

        center.x = BOARD_POSITION_X + (CELL_SIZE) / 2 + number * CELL_SIZE;
        if (ownership == USER_OWNERSHIP) {
            center.y = BOARD_POSITION_Y + (CELL_SIZE) / 2 + USER_POSITION_Y;
        } else {
            center.y = BOARD_POSITION_Y + (CELL_SIZE) / 2 + AI_POSITION_Y;
        }

        destination_dot = clicked_dot = old_center = center;
        acceleration_x = acceleration_y = velocity_x = velocity_y = 0;

        time_v = start_frame = 0;

        moving = selected = false;
    }
    ~CChecker() {

    }

    void move_to(const dot&);
    void move();
    void check_collision_with(CChecker*);

    void modify_x_position();
    void modify_y_position();

    void modify_x_velocity();
    void modify_y_velocity();

    void determine_acceleration();
    void determine_velocity();

    void draw() override;
    void update_state(const int&) override;

    void change_select();
    void change_clicked();
    void set_clicked(bool);
    void update_clicked_position(const dot&);

    bool is_selected();
    bool is_clicked();
    bool dot_belongs(const dot&);
    bool is_on_board();

    CChecker* get_itself();
};


#endif //CHAPAEV_CCHECKER_H
