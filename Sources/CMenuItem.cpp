#include <CWorld.h>
#include "CMenuItem.h"


void CMenuItem::draw() {
    sf::RectangleShape new_item(sf::Vector2f(MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT));
    new_item.setPosition(position_x, position_y);
    new_item.setOutlineThickness(MENU_ITEM_OUTLINE_THICKNESS);

    if (selected) {
        new_item.setOutlineColor(MENU_CURRENT_ITEM_COLOR);
    } else {
        new_item.setOutlineColor(MENU_OUTLINE_COLOR);
    }

    window.draw(new_item);
    window.draw(menu_item_text);
}

void CMenuItem::set_font(char const* font) {
    if (!menu_item_text_font.loadFromFile(font)) {
        std::cout << "error\n"; // todo what exactly error
    }
}
void CMenuItem::init_text() {
    set_font("STIX-Bold.otf");

    menu_item_text.setFont(menu_item_text_font);
    menu_item_text.setCharacterSize(MENU_ITEM_TEXT_SIZE);
    menu_item_text.setFillColor(MENU_ITEM_TEXT_COLOR);

    menu_item_text.setPosition(position_x + 40,
                               position_y + 15);

    menu_item_text.setString(label);
}
void CMenuItem::change_selected() {
    selected = !selected;
}
void CMenuItem::action(CWorld* game) {
    switch (value) {
        case CONTINUE_ITEM:
            game->continue_game();
            break;
        case SAVE_GAME_ITEM:
            game->save_game();

            game->game_menu.set_current_item(CONTINUE_ITEM);
            break;
        case NEW_GAME_ITEM:
            game->create_new_game();

            game->game_menu.set_current_item(CONTINUE_ITEM);
            break;
        case LOAD_GAME_ITEM:
            game->load_game();

            game->game_menu.set_current_item(CONTINUE_ITEM);
        case SETTINGS_ITEM:
            game->quit_game(); // todo settings
            break;
        case QUIT_ITEM:
            game->quit_game();
            break;
        default:
            break;
    }
}
void CMenuItem::set_position(double x, double y) {
    position_x = x;
    position_y = y;

    menu_item_text.setPosition(position_x + 40,
                               position_y + 15);
}

bool CMenuItem::get_selected() {
    return selected;
}

int CMenuItem::get_value() {
    return value;
}



