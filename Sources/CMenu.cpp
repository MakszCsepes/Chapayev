#include <CWorld.h>
#include "CMenu.h"

extern const int MENU_WIDTH = WINDOW_WIDTH/4;
extern const int MENU_HEIGHT = WINDOW_HEIGHT/1.5;

extern const int MENU_POSITION_X = (WINDOW_WIDTH - MENU_WIDTH)/2;
extern const int MENU_POSITION_Y = (WINDOW_HEIGHT - MENU_HEIGHT)/2;

extern const sf::Color MENU_OUTLINE_COLOR = sf::Color(200, 0, 0);

void CMenu::draw() {
    sf::RectangleShape menu_window(sf::Vector2f(MENU_WIDTH, MENU_HEIGHT));
    menu_window.setPosition(MENU_POSITION_X, MENU_POSITION_Y);

    menu_window.setOutlineThickness(OUTLINE_THICKNESS);
    menu_window.setOutlineColor(MENU_OUTLINE_COLOR);

    window.draw(menu_window);

    draw_items();
}

void CMenu::draw_items() {
    for(list<CMenuItem>::iterator iter = menu_items.begin(); iter != menu_items.end() ; iter++) {
        iter->draw();
    }
}

bool CMenu::check_item_on_presence(CMenuItem& new_item) {

    for(list<CMenuItem>::iterator iter = menu_items.begin(); iter != menu_items.end() ; iter++) {
        if (new_item.get_value() == iter->get_value()) {
            return false;
        }
    }

    return true;
}

void CMenu::decrease_current_item() {
    current_item--;

    if (current_item < 1) {
        current_item = menu_items.size();
    }
}
void CMenu::increase_current_item() {
    current_item++;

    if (current_item > menu_items.size()) {
        current_item = 1;
    }
}

void CMenu::handle_keyboard(CWorld& game) {
    switch(game.game_event.key.code) {
        case sf::Keyboard::Up:
            decrease_current_item();
            determine_current_item();
            break;
        case sf::Keyboard::Down:
            increase_current_item();
            determine_current_item();
            break;
        case sf::Keyboard::Return:
            current_item_act_on(game);
            break;
        default:
            break;
    }
}
void CMenu::set_text_font(char const* font) {
    if (!menu_text_font.loadFromFile(font)) {
        std::cout << "error\n"; // todo what exactly error
    }
}

void CMenu::create_initial_list_of_items() {
    menu_items.emplace_back("new game", NEW_GAME_ITEM, 0, 0);
    menu_items.emplace_back("load game", LOAD_GAME_ITEM, 0, 0);
    menu_items.emplace_back("settings", SETTINGS_ITEM, 0, 0);
    menu_items.emplace_back("quit game", QUIT_ITEM, 0, 0);

    define_offsets();
    define_menu_items_position();
}
void CMenu::add_new_items() {
    CMenuItem* new_item = new CMenuItem("continue", CONTINUE_ITEM, 0, -50);

    if (check_item_on_presence(*new_item)) {
        menu_items.emplace_front(*new_item);
    }

    define_offsets();
    define_menu_items_position();
}
void CMenu::determine_current_item() {
    int i = 1;

    for(auto iter = menu_items.begin(); iter != menu_items.end() ; iter++, i++) {
        if (iter->get_selected()) {
            iter->change_selected();
        }

        if (i == current_item) {
            iter->change_selected();
        }
    }
}

void CMenu::current_item_act_on(CWorld& game) {
    for(list<CMenuItem>::iterator iter = menu_items.begin(); iter != menu_items.end() ; iter++) {
        if (iter->get_selected()) {
            iter->action(&game);
        }
    }
}

void CMenu::define_offsets() {
    // todo самый нижний отступ не равен верхнему
    double menu_space = MENU_HEIGHT;
    int item_quantity = menu_items.size();
    double occupied_space = item_quantity * MENU_ITEM_HEIGHT;
    double free_space = menu_space - occupied_space;

    int offsets = 2;
    int gap_quantity = item_quantity - 1;

    MENU_ITEM_GAP = free_space/(gap_quantity + offsets);
    MENU_ITEM_OFFSET = MENU_ITEM_GAP/(gap_quantity/offsets);
}
void CMenu::define_menu_items_position() {
    int i = 1;

    for(auto iter = menu_items.begin(); iter != menu_items.end() ; iter++, i++) {
        if (i == 1) {
            iter->set_position(MENU_ITEM_POSITION_X, MENU_POSITION_Y + MENU_ITEM_OFFSET);

        } else {
            iter->set_position(MENU_ITEM_POSITION_X, MENU_POSITION_Y + MENU_ITEM_OFFSET +
                               (i - 1)*MENU_ITEM_GAP + (i - 1)*MENU_ITEM_HEIGHT);
        }
    }
}

void CMenu::set_current_item(int cur_item) {
    if (cur_item >= CONTINUE_ITEM && cur_item <= QUIT_ITEM) {
        current_item = cur_item;
    }

    determine_current_item();
}