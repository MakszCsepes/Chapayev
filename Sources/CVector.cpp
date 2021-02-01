#include "CVector.h"
#include <iostream>
#include <math.h>

int CVector::length() {
    return sqrt(x_*x_ + y_*y_);
}
void CVector::set_vector(double x, double y) {
    // TODO validate arg values
    this->x_ = x;
    this->y_ = y;
}

void CVector::rotate_by_angle(double angle) {
    // using a rotation matrix
    set_vector(this->x_*cos(angle) - this->y_*sin(angle),
               this->x_*sin(angle) + this->y_*cos(angle));
}
void CVector::output_vector() {
    std::cout << "\n(" << this->x_ << "; " << this->y_ << ")";
}

// operations
CVector operator+(const CVector& vector1, const CVector& vector2) {
    return CVector(vector1.x_ + vector2.x_, vector1.y_ + vector2.y_);
}
CVector& operator+=(CVector& vector1, const CVector& vector2) {
    vector1.x_ += vector2.x_;
    vector1.y_ += vector2.y_;

    return vector1;
}

CVector operator-(const CVector& vector1, const CVector& vector2) {
    return CVector(vector1.x_ - vector2.x_, vector1.y_ - vector2.y_);
}
CVector operator-=(CVector& vector1, const CVector& vector2) {
    vector1.x_ -= vector2.x_;
    vector1.y_ -= vector2.y_;

    return vector1;
}

CVector operator*(const CVector& vector1, const int& n) {
    return CVector(vector1.x_ * n, vector1.y_ * n);
}
CVector operator*=(CVector& vector1, const int& n) {
    vector1.x_ *= n;
    vector1.y_ *= n;

    return vector1;
}

CVector operator/(const CVector& vector1, const int& n) {
//    TODO validate values
    return CVector(vector1.x_ / n, vector1.y_ / n);
}
CVector operator/=(CVector& vector1, const int& n) {
//    TODO validate values
    vector1.x_ /= n;
    vector1.y_ /= n;

    return vector1;
}

CVector& CVector::operator=(const CVector &vector2) {
    this->x_ = vector2.x_;
    this->y_ = vector2.y_;

    return *this;
}
