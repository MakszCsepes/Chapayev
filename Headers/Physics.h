
#ifndef CHAPAEV_PHYSICS_H
#define CHAPAEV_PHYSICS_H

#include <cmath>
#include <math.h>
class CChecker;

extern const int RADIUS;
extern int DISTANCE_FROM_BALL_TO_END_DIRECTION;

struct dot {
    double x;
    double y;
};
struct vector_math {
    double x;
    double y;
};

//vector_math get_vector(dot& start_dot, dot& end_dot);
dot determine_dot(double angle, dot& B, int left_distance);

bool check_collision_between(const CChecker& one, const CChecker& two);

template <typename T>
double get_d_line_of(T& one, T& two) {
    return (two.center.y - one.center.y);
}

double count_angle_between(const CChecker& one, const CChecker& two);

double get_module_of_vector(vector_math AB);
double get_multiplication_of_vectors(vector_math& a, vector_math b);
double count_angle_between_vectors(vector_math AB, vector_math CD) ;
double count_angle_with_horizontal(vector_math AB) ;
vector_math get_vector(dot& start_dot, dot& end_dot);
dot get_direction_end_dot(dot& clicked_dot, dot& center);

int count_frames(double v, double a);
double count_way(double v, double a, int t);


template <typename T>
double get_distance_between(T& one, T& two) {
    double distance;

    dot A{one.center.x, one.center.y};
    dot B{two.center.x, two.center.y};
    vector_math AB = get_vector(A, B);

    distance = get_module_of_vector(AB);

    return distance;
}

#endif //CHAPAEV_PHYSICS_H
