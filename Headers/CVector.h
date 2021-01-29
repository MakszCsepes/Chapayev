#ifndef CHAPAEV_CVECTOR_H
#define CHAPAEV_CVECTOR_H


class CVector {
    int x1_;
    int x2_;
public:
    CVector() {
        this->x1_ = 1;
        this->x1_ = 1;
    }
    CVector(int x1, int x2) {
        set_vector(x1, x2);
    }

    void set_vector(int, int);

    void output_vector();

    CVector& operator=(const CVector& vector2);
    friend CVector operator+(const CVector& vector1, const CVector& vector2);
    friend CVector operator-(const CVector& vector1, const CVector& vector2);
    friend CVector operator-(const CVector& vector1, const int& n);
};


#endif //CHAPAEV_CVECTOR_H
