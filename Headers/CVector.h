#ifndef CHAPAEV_CVECTOR_H
#define CHAPAEV_CVECTOR_H

class CVector {
    double x_;
    double y_;
public:
    CVector() {
        this->x_ = 1;
        this->y_ = 1;
    }
    CVector(double x, double y) {
        set_vector(x, y);
    }

    void set_vector(double, double);
    int length();

    void rotate_by_angle(double);
    void output_vector();

    friend CVector operator+(const CVector& vector1, const CVector& vector2);
    friend CVector& operator+=(CVector& vector1, const CVector& vector2);

    friend CVector operator-(const CVector& vector1, const CVector& vector2);
    friend CVector operator-=(CVector& vector1, const CVector& vector2);

    friend CVector operator*(const CVector& vector1, const int& n);
    friend CVector operator*=(CVector& vector1, const int& n);

    friend CVector operator/(const CVector& vector1, const int& n);
    friend CVector operator/=(CVector& vector1, const int& n);

    CVector& operator=(const CVector& vector2);
};


#endif //CHAPAEV_CVECTOR_H
