#ifndef CHAPAEV_CGAME_H
#define CHAPAEV_CGAME_H

#include "CPlayer.h"

using namespace sf;

const int TMP_TEXT_SIZE = 15;
const sf::Color TMP_TEXT_COLOR(250, 250, 250);

class CGame: public IDrawable, public IObjectState {
    CPlayer* AI;

    CBoard board;

    sf::Font tmp_text_font;
    sf::Text tmp_text;
public:
    Vector2f cur_pos;
    CPlayer* user;

    CGame() {
        user = nullptr;
        AI = nullptr;
    }
    CGame(char const* user_name) {
        user = new CPlayer(user_name, USER_OWNERSHIP);
        AI = new CPlayer("AI", AI_OWNERSHIP);

        init_text();
    }
    ~CGame() {
        delete user;
        user = nullptr;

        delete AI;
        AI = nullptr;
    }

    void draw() override;
    void update_state(const int&) override;
    void keyboard_handler(sf::Event&);
    void set_font(char const*);
    void init_text();
    void update_cur_pos();
    void check_collision();
    dot get_cursor_position();
};


#endif //CHAPAEV_CGAME_H
