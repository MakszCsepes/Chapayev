
#ifndef CHAPAEV_CMENUITEM_H
#define CHAPAEV_CMENUITEM_H

#include "CGame.h"
#include <cstring>

class CWorld;

extern const int MENU_WIDTH;
extern const int MENU_HEIGHT;
extern const sf::Color MENU_OUTLINE_COLOR;

extern const int MENU_POSITION_X;
extern const int MENU_POSITION_Y;

const sf::Color MENU_CURRENT_ITEM_COLOR(0, 200, 0);
const sf::Color MENU_ITEM_TEXT_COLOR(0, 0, 0);

const int MENU_ITEM_TEXT_SIZE = 15;
const int MENU_ITEM_OUTLINE_THICKNESS = 2;

const int MENU_ITEM_WIDTH = (MENU_WIDTH)/2;
const int MENU_ITEM_HEIGHT = 50;

const int MENU_ITEM_POSITION_X = MENU_POSITION_X + (MENU_WIDTH - MENU_ITEM_WIDTH)/2;

static int MENU_ITEM_GAP;
static int MENU_ITEM_OFFSET;

const int NEW_GAME_ITEM = 1;
const int SAVE_GAME_ITEM = 2;
const int LOAD_GAME_ITEM = 3;
const int SETTINGS_ITEM = 4;
const int QUIT_ITEM = 5;
const int CONTINUE_ITEM = 6;

class CMenuItem: public IDrawable {
    char const* label;

    int value;
    bool selected;

    double position_x;
    double position_y;
    sf::Text menu_item_text;

    sf::Font menu_item_text_font;
public:
    CMenuItem() {
        label = nullptr;
    }
    CMenuItem(const char* item_name, int value1, int pos_x, int pos_y) {
        label = item_name;

        value = value1;
        selected = false;

        position_x = pos_x;
        position_y = pos_y;

        init_text();
    }

    void draw() override;

    void set_font(char const*);
    void init_text();
    void change_selected();
    void action(CWorld* game);
    void set_position(double, double);

    bool get_selected();

    int get_value();
};


#endif //CHAPAEV_CMENUITEM_H
