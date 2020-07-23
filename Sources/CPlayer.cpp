#include "CPlayer.h"
#include <CWorld.h>

extern CWorld* game;

bool is_in_list(const int checker_number, list<int> list) {
    for (auto iter = list.begin(); iter != list.end(); iter++) {
        /*if (iter->get_itself()->number == checker->number) {
            return true;
        }*/
        if (*iter == checker_number) {
            return true;
        }
    }

    return false;
}
void CPlayer::check_collision(CPlayer* enemy, list<int>* already_checked) {

    for (auto iter = checkers.begin(); iter != checkers.end(); iter++) {
        if (iter->moving) {
            // checking with player`s own checkers
            for (auto iter1 = checkers.begin(); iter1 != checkers.end(); iter1++) {
                if (iter1->get_itself() != iter->get_itself()) {
                    if (!is_in_list(iter1->number, *already_checked)) {
                        iter->check_collision_with(iter1->get_itself());
                    }
                }
            }
            // checking with enemy`s checkers
            for (auto iter2 = enemy->checkers.begin(); iter2 != enemy->checkers.end(); iter2++) {
                if (!is_in_list(iter2->number, *already_checked)) {
                    iter->check_collision_with(iter2->get_itself());
                }
            }

            already_checked->push_back(iter->get_itself()->number);
        }
    }
}
void CPlayer::update_state(const int& frame_number) {
    for(auto iter1 = checkers.begin(); iter1 != checkers.end() ; iter1++) {
        iter1->update_state(frame_number - iter1->start_frame);
    }
}
void CPlayer::draw_checkers() {
    for(auto & checker : checkers) {
        if (checker.get_itself() != current_checker) {
            checker.draw();
        }
    }

    current_checker->draw();
}

void CPlayer::create_checkers() {
    for (int i = 0; i < CHECKERS_QUANTITY; ++i) {
        checkers.emplace_back(i, ownership);
    }
}

CChecker& CPlayer::get_theleftest_checker(){
    CChecker* the_lefttest_checker = &checkers.front();

    for(auto iter = checkers.begin(); iter != checkers.end() ; iter++) {
        if (iter->get_itself() != the_lefttest_checker) {
            if (iter->center.x <= the_lefttest_checker->center.x) {

                the_lefttest_checker = iter->get_itself();
            }
        }
    }

    return *the_lefttest_checker;
}
CChecker& CPlayer::get_therightest_checker() {
    CChecker* the_rightest_checker = &checkers.back();

    for(auto iter = checkers.end(); iter != checkers.begin() ; iter--) {
        if (iter->get_itself() != the_rightest_checker) {
            if (iter->center.x >= the_rightest_checker->center.x) {

                the_rightest_checker = iter->get_itself();
            }
        }
    }

    return *the_rightest_checker;
}

CChecker& CPlayer::get_left_checker(CChecker& checker) {
    CChecker* the_nearest_left_checker = current_checker;

    double min_distance = 0;

    for(auto iter = checkers.begin(); iter != checkers.end() ; iter++) {
        if (iter->get_itself() == current_checker) {
            continue;
        }

        if(iter->center.x < current_checker->center.x) {
            if (the_nearest_left_checker != current_checker) {
                if (current_checker->center.x - iter->center.x <= min_distance) {
                    the_nearest_left_checker = iter->get_itself();
                    min_distance = current_checker->center.x - the_nearest_left_checker->center.x;
                }
            } else {
                the_nearest_left_checker = iter->get_itself();
                min_distance = current_checker->center.x - the_nearest_left_checker->center.x;
            }

        }
    }
    if (the_nearest_left_checker == current_checker) {
        the_nearest_left_checker = &get_therightest_checker();
    }

    return *the_nearest_left_checker;
}
CChecker& CPlayer::get_right_checker(CChecker& checker) {
    CChecker* the_nearest_right_checker = current_checker;

    double min_distance = 0;

    for(auto iter = checkers.begin(); iter != checkers.end() ; iter++) {
        if (iter->get_itself() == current_checker) {
            continue;
        }

        if(iter->get_itself()->center.x > current_checker->center.x) {
            if (the_nearest_right_checker != current_checker) {
                if (iter->center.x - current_checker->center.x <= min_distance) {
                    the_nearest_right_checker = iter->get_itself();
                    min_distance = the_nearest_right_checker->center.x - current_checker->center.x;
                }
            } else {
                the_nearest_right_checker = iter->get_itself();
                min_distance = the_nearest_right_checker->center.x - current_checker->center.x;
            }

        }
    }
    if (the_nearest_right_checker == current_checker) {
        the_nearest_right_checker = &get_theleftest_checker();
    }

    return *the_nearest_right_checker;
}

void CPlayer::select_checker(CChecker& checker) {
    current_checker->set_clicked(false);
    current_checker->change_select();

    current_checker = &checker;

    current_checker->change_select();
    current_checker->set_clicked(false);
}

void CPlayer::select_current_checker(){
    if (current_checker->is_on_board()) {

        if (step == LEFT) {
            select_checker(get_left_checker(*current_checker));
        } else if (step == RIGHT) {
            select_checker(get_right_checker(*current_checker));
        }
    } else {

        remove_from_checkers_list(*current_checker);
        select_random_checker();
    }
}
void CPlayer::select_random_checker() {
    int i = 1;
    int random_number = i + rand() % checkers.size();

    for(auto iter = checkers.begin(); iter != checkers.end() ; iter++, i++) {
        if(i == random_number) {
            select_checker(*iter->get_itself());
            return;
        }
    }
}

void CPlayer::remove_from_checkers_list(CChecker& checker) {
    for(auto iter = checkers.begin(); iter != checkers.end() ; iter++) {
        if(iter->get_itself() == &checker) {
            checkers.erase(iter);
            return;
        }
    }
}
void CPlayer::update_clicked_position_of_current_checker(const dot& new_pos) {
    current_checker->update_clicked_position(new_pos);
}

void CPlayer::move_checker() {
    current_checker->move();
}
