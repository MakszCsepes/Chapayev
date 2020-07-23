#include <valarray>
#include <iostream>
#include "Physics.h"

double get_module_of_vector(vector_math AB) {
    return sqrt(pow(AB.x, 2) + pow(AB.y, 2));
}
double get_multiplication_of_vectors(vector_math& a, vector_math b) {
    return a.x*b.x + a.y*b.y;
}
double count_angle_between_vectors(vector_math AB, vector_math CD) {
    double cos_angle;

    cos_angle = (get_multiplication_of_vectors(AB, CD))/
                (get_module_of_vector(AB)*get_module_of_vector(CD));

    return acos(cos_angle);
}
double count_angle_with_horizontal(vector_math AB) {
    dot O = {0, 0};
    dot C = {10, 0};
    vector_math OC = get_vector(O, C);
    return count_angle_between_vectors(AB, OC);
}
vector_math get_vector(dot& start_dot, dot& end_dot) {
    return {end_dot.x - start_dot.x, end_dot.y - start_dot.y};
}
dot get_direction_end_dot(dot& clicked_dot, dot& center) {
    dot C = {clicked_dot.x, clicked_dot.y - 2*(clicked_dot.y - center.y)};

    vector_math AB = get_vector(C, center);

    dot dot_on_ball = {center.x + RADIUS, center.y};
    vector_math horizontal_vec = get_vector(center, dot_on_ball);

    double angle = count_angle_between_vectors(AB, horizontal_vec);

    dot end_dot;
    if (C.y <= center.y) {
        end_dot = {cos(-angle) * (RADIUS + DISTANCE_FROM_BALL_TO_END_DIRECTION),
                   sin(-angle) * (RADIUS + DISTANCE_FROM_BALL_TO_END_DIRECTION)};
    } else {
        end_dot = {cos(angle) * (RADIUS + DISTANCE_FROM_BALL_TO_END_DIRECTION),
                   sin(angle) * (RADIUS + DISTANCE_FROM_BALL_TO_END_DIRECTION)};
    }

    end_dot.x += center.x;
    end_dot.y += center.y;

    return end_dot;
}

int count_frames(double v, double a) {
    int i = 0;

    while(std::abs(v) - a >= 0){
        v = v < 0 ? v + a : v - a;
        i++;
    }

    return i;
}
double count_way(double v, double a, int t) {
    return v*t + a*t*t/2;
}
