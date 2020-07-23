#include <CWorld.h>
#include "CChecker.h"

extern CWorld* game;

int DISTANCE_FROM_BALL_TO_END_DIRECTION = 50;
const int RADIUS = (CELL_SIZE - 25*CELL_SIZE/100)/2;

double velo_k = 10;
double acc_k = 30;

double count_dest(double velocity, double acceleration) {
    double distance_to_destination_x = 0;
    if (velocity != 0) {
        double v = std::abs(velocity);
        while (v >= 0) {
            distance_to_destination_x += v;
            v -= std::abs(acceleration);
        }
        if (velocity < 0) {
            distance_to_destination_x = 0 - distance_to_destination_x;
        }
    }

    return distance_to_destination_x;
}

void draw_way(dot clicked, dot wayz) {
    sf::Vertex way[] = {
            sf::Vertex(sf::Vector2f(0, 0)),
            sf::Vertex(sf::Vector2f(100, 100)),
            sf::Vertex(sf::Vector2f(100, 100))
    };

    way[0].position = {float(clicked.x), float(clicked.y)};
    way[1].position = {float(wayz.x), float(wayz.y)};

    window.draw(way, 2, sf::Lines);
}

void CChecker::draw() {
    sf::CircleShape checker(RADIUS);

    checker.setPosition(center.x - RADIUS, center.y - RADIUS);

    checker.setFillColor(CHECKER_FILL_COLOR);

    checker.setOutlineThickness(CHECKER_OUTLINE_THICKNESS);
    if (selected) {
        checker.setOutlineColor(SELECTED_CHECKER_OUTLINE_COLOR);
    } else {
        checker.setOutlineColor(CHECKER_OUTLINE_COLOR);
    }

    window.draw(checker);

    if (selected && clicked) {
        draw_way(clicked_dot, destination_dot);
    }


    sf::CircleShape center_circle(RADIUS/5);
    center_circle.setPosition(center.x - RADIUS/5, center.y - RADIUS/5);
    if (selected) {
        center_circle.setFillColor(SELECTED_CHECKER_OUTLINE_COLOR);
    } else {
        center_circle.setFillColor(CHECKER_OUTLINE_COLOR);
    }
    window.draw(center_circle);
}
void CChecker::update_state(const int& frame_number) {
    if (moving && frame_number <= time_v) {
        // center movement in x
            modify_x_position();
            modify_x_velocity();

        // center movement in y
            modify_y_position();
            modify_y_velocity();
    } else {
        if (moving) {
            moving = false;
        }
    }
}

void CChecker::check_collision_with(CChecker* checker) {
    if (get_distance_between(*this, *checker) < 2*RADIUS) {

        checker->update_clicked_position(this->center);
        checker->move();

        double angle_between_velocity_and_center = count_angle_between_vectors(get_vector(center, destination_dot),
                get_vector(center, checker->center));

        if (angle_between_velocity_and_center == 0) {
            moving = false;
            destination_dot = center;
        } else {
            double new_current_angle = 1.57 - angle_between_velocity_and_center;

            double x_distance = (checker->center.x - center.x);
            double y_distance = (x_distance * tan(new_current_angle));
            dot cl_dot = {center.x - x_distance, center.y + y_distance};
            update_clicked_position(cl_dot);
            move();
        }
    }
}

void CChecker::modify_x_position() {
    center.x += velocity_x;
}
void CChecker::modify_y_position() {
    center.y += velocity_y;
}

void CChecker::modify_x_velocity() {
    velocity_x += acceleration_x;
}
void CChecker::modify_y_velocity() {
    velocity_y += acceleration_y;
}
void CChecker::move() {
    old_center = center;
    start_frame = game->get_current_frame();
    moving = true;

    determine_velocity();
    determine_acceleration();

    destination_dot = {center.x + count_dest(velocity_x, acceleration_x),
                       center.y + count_dest(velocity_y, acceleration_y)};

    if (velocity_x == 0) {
        time_v = abs(velocity_y / acceleration_y);
    } else {
        time_v = abs(velocity_x / acceleration_x);
    }
}
void CChecker::move_to(const dot& dest_dot) {
    old_center = center;

    this->destination_dot = dest_dot;

    start_frame = game->get_current_frame();
}

void CChecker::determine_acceleration() {
    if (velocity_x == 0) {
      acceleration_x = 0;

      acceleration_y = (0 - velocity_y)/acc_k;
      return;
    }
    if (velocity_y == 0) {
        acceleration_y = 0;

        acceleration_x = (0 - velocity_x)/acc_k;
        return;
    }

    acceleration_x = (0 - velocity_x)/acc_k;
    acceleration_y = (0 - velocity_y)/acc_k;
}
void CChecker::determine_velocity() {
    double click_dot_distance_x = center.x - clicked_dot.x;
    double click_dot_distance_y = center.y - clicked_dot.y;

    velo_k = get_module_of_vector(get_vector(clicked_dot, center))/10;
    acc_k = velo_k*3;

    if (click_dot_distance_x == 0) {
        velocity_x = 0;
        velocity_y = click_dot_distance_y / velo_k;
        return;
    }
    if (click_dot_distance_y == 0) {
        velocity_y = 0;
        velocity_x = click_dot_distance_x / velo_k;
        return;
    }

    velocity_x = click_dot_distance_x/velo_k;
    velocity_y = click_dot_distance_y/velo_k;
}

void CChecker::update_clicked_position(const dot& new_clicked_dot) {
    clicked_dot = new_clicked_dot;

    determine_velocity();
    determine_acceleration();

    destination_dot = {center.x + count_dest(velocity_x, acceleration_x),
                       center.y + count_dest(velocity_y, acceleration_y)};
}

void CChecker::change_select() {
    selected = !selected;
}
void CChecker::change_clicked() {
    clicked = !clicked;
}

bool CChecker::is_selected() {
    return selected;
}
bool CChecker::is_clicked(){
    return clicked;
}
bool CChecker::is_on_board() {
    if (center.x + RADIUS + CHECKER_OUTLINE_THICKNESS <= BOARD_POSITION_X ||
        center.x - RADIUS >= BOARD_POSITION_X + BOARD_WIDTH*CELL_SIZE) {
        return false;
    }
    if (center.y + RADIUS + CHECKER_OUTLINE_THICKNESS <= BOARD_POSITION_Y ||
        center.y - RADIUS >= BOARD_POSITION_Y + BOARD_HEIGHT*CELL_SIZE) {
        return false;
    }

    return true;
}
bool CChecker::dot_belongs(const dot &dot_clicked) {
    return (dot_clicked.y >= center.y - RADIUS && dot_clicked.y <= center.y + RADIUS) &&
           (dot_clicked.x >= center.x - RADIUS && dot_clicked.x <= center.x + RADIUS);
}

CChecker* CChecker::get_itself() {
    return this;
}

void CChecker::set_clicked(bool new_clicked) {
    clicked = new_clicked;
}