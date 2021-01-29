#include "CVector.h"
#include <iostream>

void CVector::set_vector(int x1, int x2) {
    // TODO validate arg values
    this->x1_ = x1;
    this->x2_ = x2;
}

void CVector::output_vector() {
    std::cout << "\n(" << this->x1_ << "; " << this->x2_ << ")";
}

// operations
CVector operator+(const CVector& vector1, const CVector& vector2) {
    return CVector(vector1.x1_ + vector2.x1_, vector1.x2_ + vector2.x2_);
}
CVector operator-(const CVector& vector1, const CVector& vector2) {
    return CVector(vector1.x1_ - vector2.x1_, vector1.x2_ - vector2.x2_);
}
CVector operator-(const CVector& vector1, const int& n) {
    return CVector(vector1.x1_*n, vector1.x2_*n);
}
CVector& CVector::operator=(const CVector &vector2) {
    this->x1_ = vector2.x1_;
    this->x2_ = vector2.x2_;

    return *this;
}
