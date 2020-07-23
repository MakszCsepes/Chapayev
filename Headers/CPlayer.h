#ifndef CHAPAEV_CPLAYER_H
#define CHAPAEV_CPLAYER_H

#include "CChecker.h"
#include <list>
#include <ctime>

const int CHECKERS_QUANTITY = 8;
const int LEFT = 1;
const int RIGHT = 2;

using std::list;
class CPlayer: public IObjectState {
    char const* name;

    int points;
    int ownership;

public:
    std::list<CChecker> checkers;
    CChecker* current_checker;
    int step;

    CPlayer() {
        name = nullptr;
        current_checker = nullptr;
    }
    CPlayer(char const* player_name, int own) {
        name = player_name;
        ownership = own;

        create_checkers();
        current_checker = &checkers.front();
        current_checker->change_select();
    }

    void update_state(const int&) override;
    void create_checkers();
    void draw_checkers();
    void move_checker();
    void remove_from_checkers_list(CChecker&);
    void select_checker(CChecker&);
    void select_current_checker();
    void select_random_checker();
    void update_clicked_position_of_current_checker(const dot& new_pos);
    void check_collision(CPlayer*, list<int>*);

    CChecker& get_left_checker(CChecker&);
    CChecker& get_right_checker(CChecker&);
    CChecker& get_therightest_checker();
    CChecker& get_theleftest_checker();
};

#endif //CHAPAEV_CPLAYER_H
