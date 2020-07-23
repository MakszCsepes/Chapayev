#include "CWorld.h"

sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chapaev");

void CWorld::draw_fps() {
    std::string text("FPS = " + std::to_string(float(fps)));
//    string text("FPS = " + to_string(frames));

    fps_text.setString(text);
    window.draw(fps_text);
}

void CWorld::draw_results() {

}

void CWorld::draw() {
    draw_fps();

    switch (game_state) {
        case MENU:
            game_menu.draw();
            break;
        case GAME:
            if (game != nullptr) {
                game->draw();
            }
            break;
        case RESULT:
            draw_results();
            break;
        default:
            break;
    }

}

void CWorld::update_state(const int &frame_number) {
    count_fps();

    if (game != nullptr) {
        game->update_state(frame_number);
    }
}
void CWorld::set_text_font(char const*font) {
    if (!text_font.loadFromFile(font)) {
        std::cout << "error\n"; // todo what exactly error
    }
}

void CWorld::count_fps() {
    frames_count++;

    frames = frames_count - old_frames_count;
    if (frames >= 100) {
        timestamps = clock.getElapsedTime() - old_timestamps;

        fps = (frames * 1000.0) / timestamps.asMilliseconds();
        old_frames_count = frames_count;

        old_timestamps = clock.getElapsedTime();
    }
}

void CWorld::change_game_state() {
    if (game_state == MENU) {
        game_state = previous_state;
    } else {
        previous_state = game_state;
        game_state = MENU;
    }
}

void CWorld::continue_game() {
    game_state = GAME;
}
void CWorld::save_game(){
}
void CWorld::create_new_game() {
    if (game != nullptr) {
        delete game;
        game = nullptr;
    }
    game = new CGame("user");

    change_game_state();

    game_menu.add_new_items();
}
void CWorld::load_game() {

}
void CWorld::quit_game() {
    game_state = QUIT;
}

int CWorld::get_state() {
    return game_state;
}


int CWorld::get_current_frame() {
    return frames_count;
}