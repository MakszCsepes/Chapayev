#ifndef CHAPAEV_CMENU_H
#define CHAPAEV_CMENU_H

#include "CMenuItem.h"
#include <list>

static float OUTLINE_THICKNESS = 2.0;

const int MENU_TEXT_SIZE = 15;
const sf::Color MENU_TEXT_COLOR = sf::Color::Black;

class CMenu: public IDrawable {
    int current_item;

    list<CMenuItem> menu_items;

    sf::Font menu_text_font;
    sf::Text menu_text;

    void draw_items();
public:
    CMenu() {
        set_text_font("STIX-Bold.otf");
        create_initial_list_of_items();

        current_item = NEW_GAME_ITEM;
        determine_current_item();
    }
    ~CMenu() {
        menu_items.clear();
    }

    void draw() override;

    void handle_keyboard(CWorld&);
    void set_text_font(char const*);

    void increase_current_item();
    void decrease_current_item();

    void create_initial_list_of_items();
    void add_new_items();

    void determine_current_item();
    void current_item_act_on(CWorld& game);
    void set_current_item(int);

    void define_offsets();
    void define_menu_items_position();

    bool check_item_on_presence(CMenuItem&);
};

#endif //CHAPAEV_CMENU_H
