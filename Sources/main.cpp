#include "CWorld.h"
#include "CVector.h"

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

const int W = 640;
const int H = 480;

int main() {
    CVector v1(2, 3);
    v1.output_vector();
    CVector v2(-2, 7);
    v2.output_vector();

    CVector v3 = v1 + v2;

    v3.output_vector();
    return 0;
    float center1_x = W / 4;
    float center1_y = H / 2;

    float center2_x = W / 4 * 3;
    float center2_y = H / 2;

    float r1 = 50;
    float r2 = 50;

    float vel_x1 = rand() % 10;
    float vel_y1 = rand() % 10;
    float vel_x2 = rand() % 10;
    float vel_y2 = rand() % 10;
    vel_x2 = 0;
    vel_y2 = 0;

    sf::Color col1 = sf::Color(255, 0, 255);
    sf::Color col2 = sf::Color(255, 255, 0);
    sf::RenderWindow window(sf::VideoMode(W, H), "My SFML WORKS!!!");

    sf::CircleShape shape(0);
    sf::CircleShape shape2(0);

    shape.setRadius(r1);
    shape.setOrigin(r1, r1);
    shape.setFillColor(col1);

    shape2.setRadius(r2);
    shape2.setOrigin(r2, r2);
    shape2.setFillColor(col2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }


        center1_x += vel_x1;
        center1_y += vel_y1;
        if ((center1_x + r1 > W) || (center1_x - r1 < 0)){
            vel_x1 =- vel_x1;
        }
        if ((center1_y + r1 > H) || (center1_y - r1 < 0)){
            vel_y1 =- vel_y1;
        }

        center2_x += vel_x2;
        center2_y += vel_y2;
        if ((center2_x + r2 > W) || (center2_x - r2 < 0)){
            vel_x2=-vel_x2;
        }
        if ((center2_y + r2 > H) || (center2_y - r2 < 0)){
            vel_y2=-vel_y2;
        }


        float Dx = center1_x - center2_x;
        float Dy = center1_y - center2_y;
        float d = sqrt(Dx*Dx+Dy*Dy); if (d == 0) d = 0.01;
        float s = Dx/d; // sin
        float e = Dy/d; // cos
        if (d < r1+r2){
            float Vn1 = vel_x2 * s + vel_y2 * e;
            float Vn2 = vel_x1 * s + vel_y1 * e;
            float dt = (r2+r1-d)/(Vn1-Vn2);
            if (dt > 0.6) dt = 0.6;
            if (dt < -0.6) dt = -0.6;
            center1_x-= vel_x1 * dt;
            center1_y-= vel_y1 * dt;
            center2_x-= vel_x2 * dt;
            center2_y-= vel_y2 * dt;
            Dx = center1_x - center2_x;
            Dy = center1_y - center2_y;
            d = sqrt(Dx*Dx+Dy*Dy); if (d == 0) d = 0.01;
            s = Dx/d; // sin
            e = Dy/d; // cos
            Vn1 = vel_x2 * s + vel_y2 * e;
            Vn2 = vel_x1 * s + vel_y1 * e;
            float Vt1 = -vel_x2 * e + vel_y2 * s;
            float Vt2 = -vel_x1 * e + vel_y1 * s;


            float o = Vn2;
            Vn2 = Vn1;
            Vn1 = o;


            vel_x1 = Vn2 * s - Vt2 * e;
            vel_y1 = Vn2 * e + Vt2 * s;
            vel_x2 = Vn1 * s - Vt1 * e;
            vel_y2 = Vn1 * e + Vt1 * s;
            center1_x+= vel_x1 * dt;
            center1_y+= vel_y1 * dt;
            center2_x+= vel_x2 * dt;
            center2_y+= vel_y2 * dt;
        }


        window.clear();

        shape.setPosition(center1_x, center1_y);
        window.draw(shape);

        shape2.setPosition(center2_x, center2_y);
        window.draw(shape2);


        window.display();
        sf::sleep(sf::milliseconds(int(1000/30)));
    }

    return 0;
    sf::Cursor cursor;
    if (cursor.loadFromSystem(sf::Cursor::Cross)) {
        window.setMouseCursor(cursor);
    }

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