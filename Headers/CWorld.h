#ifndef CHAPAEV_CWORLD_H
#define CHAPAEV_CWORLD_H

#include "CMenu.h"
#include "CGame.h"

#define MENU 0
#define GAME 1
#define RESULT 2
#define QUIT 3
static const sf::Color BACKGROUND_COLOR(50, 50, 50);

class CWorld: public IDrawable, public IObjectState {
    int frames_count;
    int old_frames_count;
    int frames;
    int game_state;
    int previous_state;

    double fps;
//  ------------------
    sf::Clock clock;

    sf::Font text_font;
    sf::Text fps_text;

    sf::Time old_timestamps;
    sf::Time timestamps;
public:
    CGame* game;
    CMenu game_menu;
    sf::Event game_event;

    CWorld() {
        game_state = MENU;
        previous_state = GAME;
        game = nullptr;

        set_text_font("STIX-Bold.otf");

        frames_count = 0;
        old_frames_count = 0;
        fps = 0;

        fps_text.setCharacterSize(14);
        fps_text.setFillColor(sf::Color::White);
        fps_text.setPosition(0, 0);

        fps_text.setFont(text_font);
    }
    ~CWorld() {
        delete game;
        game = nullptr;
    }

    int get_state();

    void draw() override;
    void update_state(const int&) override;
    void set_text_font(char const* font);
    void draw_fps();
    void draw_results();
    void count_fps();
    void change_game_state();

    void continue_game();
    void create_new_game();
    void save_game();
    void load_game();
    void quit_game();

    int get_current_frame();
};

#endif //CHAPAEV_CWORLD_H
