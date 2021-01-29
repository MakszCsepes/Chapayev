#include <CWorld.h>
#include "CChecker.h"

extern CWorld* game;

int DISTANCE_FROM_BALL_TO_END_DIRECTION = 50;
const int RADIUS = (CELL_SIZE - 25*CELL_SIZE/100)/2;


double velo_k = 105;
double acc_k = 5;
int v = 15;
int a = 4;
double count_dest(double velocity, double acceleration) {
    double distance_to_destination = 0;
    if (velocity != 0) {
        double v = std::abs(velocity);
        while (v >= 0) {
            distance_to_destination += v;
            v -= std::abs(acceleration);
        }
        if (velocity < 0) {
            distance_to_destination = 0 - distance_to_destination;
        }
    }

    return distance_to_destination;
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

void CChecker::draw_checker_center() {
    sf::CircleShape center_circle(RADIUS/5);
    center_circle.setPosition(center.x - RADIUS/5, center.y - RADIUS/5);
    if (selected) {
        center_circle.setFillColor(SELECTED_CHECKER_OUTLINE_COLOR);
    } else {
        center_circle.setFillColor(CHECKER_OUTLINE_COLOR);
    }
    window.draw(center_circle);

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

    draw_checker_center();
    if (clicked || moving) {
        sf::CircleShape dest_circle(RADIUS/6);
        dest_circle.setPosition(destination_dot.x - RADIUS/6, destination_dot.y - RADIUS/6);
        dest_circle.setFillColor(sf::Color::Yellow);
        window.draw(dest_circle);
    }
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
        old_center = center;
    }
}

const int clockwise = 1;
const int anticlockwise = -1;

const int one = 1;
const int two = 2;
const int three = 3;
const int four = 4;

dot checker2_after_dot = {0, 0};
dot checker1_after_dot = {0, 0};
dot collision_dot = {0, 0};
int AB_chet = one;
int AC_chet = one;
int AT_chet = one;

int determine_vel_chet(const double& vel_x, const double& vel_y) {
    if (vel_y > 0) {
        if (vel_x > 0) {
            return one;
        } else {
            return two;
        }
    } else {
        if (vel_x > 0) {
            return four;
        } else {
            return three;
        }
    }
}

int determine_vector_chet(const dot& A, const dot& B) {
    if (B.y >= A.y) {
        if (B.x >= A.x) {
            return one;
        } else {
            return two;
        }
    } else {
        if (B.x >= A.x) {
            return four;
        } else {
            return three;
        }
    }
}
void determine_velocity_by_chet(const int& chet, double& velocity_x, double& velocity_y) {
    switch (chet) {
        case one:
            break;
        case two:
            velocity_x = -velocity_x;
            break;
        case three:
            velocity_x = -velocity_x;
            velocity_y = -velocity_y;
            break;
        case four:
            velocity_y = -velocity_y;
            break;
    }
}
int get_changed_chet(int current_chet, int& mode) {
    current_chet += mode;

    if (current_chet == 0) {
        current_chet = four;
    } else if (current_chet == 5) {
        current_chet = one;
    }

    return current_chet;
}

int define_mode(const int& chet, const double& BABx, const double& CACx) {
    int mode; // clockwise or anticlockwise;
    if (chet == four || chet == two) {
        if (BABx > CACx) {
            mode = anticlockwise;
        } else {
            mode = clockwise;
        }
    } else if (chet == three || chet == one) {
        if (BABx > CACx) {
            mode = clockwise;
        } else {
            mode = anticlockwise;
        }
    }

    return mode;
}
void determine_angles(double& BABx, double& CACx, const CChecker* checker1, const CChecker* checker2) {
    BABx = std::abs(atan(checker1->velocity_y/checker1->velocity_x));
    CACx = std::abs(atan((checker2->center.y - checker1->center.y)/(checker2->center.x - checker1->center.x)));
}
double get_alpha(const CChecker& checker1, const CChecker& checker2) {
    double alpha;
    dot A = checker1.center;
    dot B = {checker1.center.x + checker1.velocity_x, checker1.center.y + checker1.velocity_y};
    dot C = checker2.center;
    vector_math AB = get_vector(A, B);
    vector_math AC = get_vector(A, C);

    alpha = count_angle_between_vectors(AB, AC);
    return alpha;
}
double get_beta(const CChecker& checker1, const double& PPx, const double& APx) {
    dot B = {checker1.center.x + checker1.velocity_x, checker1.center.y + checker1.velocity_y};
    dot P = {checker1.center.x + APx, checker1.center.y + PPx};
    vector_math BP = get_vector(B, P);
    dot By = {0, checker1.center.y + checker1.velocity_y};
    vector_math BBy = get_vector(B, By);

    double beta = count_angle_between_vectors(BP, BBy);
    if (beta > 1.5707) {
        beta = 3.14159 - beta;
    }
    return beta;
}

void algorithm(CChecker* checker1, CChecker* checker2) {
    chapaevMath::angle aBABx;
    chapaevMath::angle aCACx;

    determine_angles(aBABx.RadAngle, aCACx.RadAngle, checker1, checker2);

    // the most significant thing is to determine alpha corner;
    chapaevMath::angle alpha;
    alpha.RadAngle = get_alpha(*checker1, *checker2);

    // the algorithm will be the same for any alpha corner's value;
    double AB = (sqrt(checker1->velocity_x*checker1->velocity_x + checker1->velocity_y*checker1->velocity_y));
    double AP = std::abs(cos(alpha.RadAngle)*AB);

    double APx = std::abs(cos(aCACx.RadAngle) * AP);
    double PPx = std::abs(sin(aCACx.RadAngle) * AP);

    // define velocity direction
    determine_velocity_by_chet(determine_vector_chet(checker1->center, checker2->center), APx, PPx);

    checker2->velocity_x = APx;
    checker2->velocity_y = PPx;

    // if angle between velocity (of the first checker) and a line segment (between centers of two checkers)
    // equals 0 then the first checker should be stopped;
    if (alpha.RadAngle == 0) {
        checker1->moving = false;
        checker1->destination_dot = checker1->center;
        // otherwise the new velocity should be measured
    } else {
        chapaevMath::angle smaller_angle = aBABx.RadAngle < aCACx.RadAngle ? aBABx : aCACx;
        double beta = get_beta(*checker1, PPx, APx);
        double BP = std::abs(sqrt(AB*AB - AP*AP));
        double new_vel_x = std::abs(sin(beta)*BP);
        double new_vel_y = std::abs(cos(beta)*BP);

        // func
        AC_chet = determine_vector_chet(checker1->center, checker2->center);
        AB_chet = determine_vel_chet(checker1->velocity_x, checker1->velocity_y);
        if (AC_chet == AB_chet) {
            int mode; // clockwise or anticlockwise;
            mode = define_mode(AC_chet, aBABx.RadAngle, aCACx.RadAngle);
            determine_velocity_by_chet(get_changed_chet(AC_chet, mode), new_vel_x, new_vel_y);
        } else {
            determine_velocity_by_chet(AB_chet, new_vel_x, new_vel_y);
        }
        //

        checker1->velocity_x = new_vel_x;
        checker1->velocity_y = new_vel_y;
        checker1->determine_acceleration();
        checker1->determine_destination_dot();

        AT_chet = determine_vector_chet(checker1->center, checker1->destination_dot);
    }
}
dot help_func(CChecker cur_checker, CChecker possible_collision_checker) {
    double const_v_x = cur_checker.velocity_x;
    double const_v_y = cur_checker.velocity_y;

    // increase position by velocity to detect collision
    while(get_distance_between_dots(cur_checker.center, possible_collision_checker.center) > 2 * RADIUS) {
        if (const_v_x < 0) {
            if (cur_checker.velocity_x >= 0) {
                return {0, 0};
            }
        } else {
            if (cur_checker.velocity_x <= 0) {
                return {0, 0};
            }
        }

        if (const_v_y < 0) {
            if (cur_checker.velocity_y >= 0) {
                return {0, 0};
            }
        } else {
            if (cur_checker.velocity_y <= 0) {
                return {0, 0};
            }
        }

        cur_checker.center.x += cur_checker.velocity_x;
        cur_checker.center.y += cur_checker.velocity_y;

        cur_checker.velocity_x += cur_checker.acceleration_x;
        cur_checker.velocity_y += cur_checker.acceleration_y;
    }

    // collision will absolutely occur;
//    std::cout << "collision may occur at " << cur_checker.center.x << ", " << cur_checker.center.y << std::endl;
    collision_dot = cur_checker.center;
    algorithm(&cur_checker, &possible_collision_checker);

    possible_collision_checker.determine_acceleration();
    possible_collision_checker.determine_destination_dot();

    checker2_after_dot = possible_collision_checker.destination_dot;
    checker1_after_dot = cur_checker.destination_dot;
    /*vector_math WC = get_vector(collision_dot, checker2_after_dot);
    vector_math WD = get_vector(collision_dot, checker1_after_dot);
    double ang = count_angle_between_vectors(WC, WD);
    if(ang <= 1.57 || ang >= 1.5808) {
        std::cout << ang << " wrong angle\n";
    }*/
    return checker2_after_dot;
}
void CChecker::check_collision_with(CChecker* possible_collision_checker) {

    if (get_distance_between(*this, *possible_collision_checker) <= 2 * RADIUS) {
        algorithm(this, possible_collision_checker);

        this->move();

        possible_collision_checker->determine_acceleration();
        possible_collision_checker->determine_destination_dot();
        possible_collision_checker->move();
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
    this->old_center = this->center;
    this->start_frame = game->get_current_frame();
    this->moving = true;

    if (velocity_x == 0) {
        this->time_v = std::abs(velocity_y/acceleration_y);
    } else {
        this->time_v = std::abs(velocity_x/acceleration_x);
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

    velo_k = get_module_of_vector(get_vector(clicked_dot, center))/v;
    acc_k = velo_k*a;

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
void CChecker::determine_destination_dot() {
    destination_dot = {center.x + count_dest(velocity_x, acceleration_x),
                       center.y + count_dest(velocity_y, acceleration_y)};
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