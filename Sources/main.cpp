#include "CWorld.h"

void handle_keyword(CWorld& game) {
    while (window.pollEvent(game.game_event)) {
        switch (game.game_event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseMoved:
                if (game.get_state() == GAME) {
                    game.game->keyboard_handler(game.game_event);
                }
                break;
            case sf::Event::MouseButtonPressed:
                if (game.get_state() == GAME) {
                    game.game->keyboard_handler(game.game_event);
                }
                break;
            case sf::Event::MouseButtonReleased:
                if (game.get_state() == GAME) {
                    game.game->keyboard_handler(game.game_event);
                }
                break;
            case sf::Event::KeyPressed:
                if (game.get_state() == MENU) {
                    game.game_menu.handle_keyboard(game);
                    break;
                }
                if (game.get_state() == GAME) {
                    game.game->keyboard_handler(game.game_event);
                }
                switch(game.game_event.key.code) {
                    case sf::Keyboard::Escape:
                        game.change_game_state();
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}

CWorld* game;

int main() {
    game = new CWorld();

    window.setFramerateLimit(60);
    while(window.isOpen()) {
        window.clear(BACKGROUND_COLOR);
        game->update_state(game->get_current_frame());

        handle_keyword(*game);
        if (game->get_state() == QUIT) {
            window.close();
        }

        game->draw();

        window.display();
    }

    delete game;
    game = nullptr;

    return 0;
}