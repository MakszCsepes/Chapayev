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

    int i = 0;
    for(auto iter = user->checkers.begin(); iter != user->checkers.end() ; iter++, i++) {
        tmp_text.setString(to_string(i+1) + " - " + to_string(get_distance_between(*user->current_checker, *iter->get_itself())));
        tmp_text.setPosition(BOARD_POSITION_X - 200, BOARD_POSITION_Y + 80 + i*20);
        window.draw(tmp_text);
    }

    tmp_text.setString("RADIUS = " + to_string(RADIUS));
    tmp_text.setPosition(BOARD_POSITION_X - 200, BOARD_POSITION_Y + 250);
    window.draw(tmp_text);
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