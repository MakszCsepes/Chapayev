#include "CGame.h"

void CGame::check_collision() {
    list<int> already_checked;
    user->check_collision(AI, &already_checked);
    AI->check_collision(user, &already_checked);
}
void CGame::update_state(const int &frame_number) {
    user->update_state(frame_number);
    AI->update_state(frame_number);

    check_collision();
}

extern dot checker2_after_dot;
extern dot checker1_after_dot;
extern dot collision_dot;
extern int AB_chet;
extern int AC_chet;
extern int AT_chet;

void draw_end_dot(dot D, sf::Color color) {
    if (D.x != 0 && D.y != 0) {
        sf::CircleShape center_circle(RADIUS/5);
        center_circle.setPosition(D.x - RADIUS/5, D.y - RADIUS/5);
        center_circle.setFillColor(color);
        window.draw(center_circle);
    }
}
void draw_end_dots() {
    draw_end_dot(checker2_after_dot, sf::Color::Green);
    draw_end_dot(checker1_after_dot, sf::Color::Blue);
    draw_end_dot(collision_dot, sf::Color::Red);
}
void CGame::draw() {
    using std::to_string;

    board.draw();
    AI->draw_checkers();
    user->draw_checkers();

    dot checker_dest = user->current_checker->destination_dot;;
    dot checker_center = user->current_checker->center;
    dot checker_clicked = user->current_checker->clicked_dot;

    tmp_text.setString("Destination: x = " + to_string(checker_dest.x) + ", y = " + to_string(checker_dest.y));
    tmp_text.setPosition(BOARD_POSITION_X + CELL_SIZE*BOARD_WIDTH + 40, BOARD_POSITION_Y + 15);
    window.draw(tmp_text);

    tmp_text.setString("Center: x = " + to_string(checker_center.x) + ", y = " + to_string(checker_center.y));
    tmp_text.setPosition(BOARD_POSITION_X + CELL_SIZE*BOARD_WIDTH + 40, BOARD_POSITION_Y + 30);
    window.draw(tmp_text);

    tmp_text.setString("Clicked: x = " + to_string(checker_clicked.x) + ", y = " + to_string(checker_clicked.y));
    tmp_text.setPosition(BOARD_POSITION_X + CELL_SIZE*BOARD_WIDTH + 40, BOARD_POSITION_Y + 45);
    window.draw(tmp_text);

    tmp_text.setString("Power = " + to_string(get_module_of_vector(get_vector(checker_clicked, checker_center))));
    tmp_text.setPosition(BOARD_POSITION_X - 200, BOARD_POSITION_Y + 45);
    window.draw(tmp_text);

    tmp_text.setString("AB_chet = " + to_string(AB_chet));
    tmp_text.setPosition(BOARD_POSITION_X - 200, BOARD_POSITION_Y + 60);
    window.draw(tmp_text);

    tmp_text.setString("AC_chet = " + to_string(AC_chet));
    tmp_text.setPosition(BOARD_POSITION_X - 200, BOARD_POSITION_Y + 75);
    window.draw(tmp_text);

    tmp_text.setString("AT_chet = " + to_string(AT_chet));
    tmp_text.setPosition(BOARD_POSITION_X - 200, BOARD_POSITION_Y + 90);
    window.draw(tmp_text);

    draw_end_dots();
}

void CGame::keyboard_handler(sf::Event& event) {
    switch (event.type) {
        case Event::MouseMoved:
            if (user->current_checker->is_clicked()) {
                update_cur_pos();
                user->update_clicked_position_of_current_checker(get_cursor_position());
            }
            break;
        case Event::MouseButtonReleased:
            if (user->current_checker->is_clicked()) {
                user->current_checker->change_clicked();

                user->move_checker();
            }
            break;
        case Event::MouseButtonPressed:
            update_cur_pos();
            if (user->current_checker->dot_belongs(get_cursor_position())) {
                user->current_checker->change_clicked();

                user->update_clicked_position_of_current_checker(get_cursor_position());
            }
            break;
        case Event::KeyPressed:
            switch (event.key.code) {
                case sf::Keyboard::Right:
                    user->step = RIGHT;
                    user->select_current_checker();
                    break;
                case sf::Keyboard::Left:
                    user->step = LEFT;
                    user->select_current_checker();
                    break;
                case sf::Keyboard::Return:
                    user->move_checker();
                    break;
                case sf::Keyboard::W:
                    user->current_checker->center.y -= 1;
                    break;
                case sf::Keyboard::S:
                    user->current_checker->center.y += 1;
                    break;
                case sf::Keyboard::A:
                    user->current_checker->center.x -= 1;
                    break;
                case sf::Keyboard::D:
                    user->current_checker->center.x += 1;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void CGame::update_cur_pos() {
    Vector2i pixel_position = Mouse::getPosition(window);
    cur_pos = window.mapPixelToCoords(pixel_position);
}
dot CGame::get_cursor_position() {
    return {cur_pos.x, cur_pos.y};
}

void CGame::set_font(char const* font) {
    if (!tmp_text_font.loadFromFile(font)) {
        std::cout << "error\n"; // todo what exactly error
    }
}
void CGame::init_text() {
    set_font("STIX-Bold.otf");

    tmp_text.setFont(tmp_text_font);
    tmp_text.setCharacterSize(TMP_TEXT_SIZE);
    tmp_text.setFillColor(TMP_TEXT_COLOR);
}