
#ifndef CHAPAEV_IOBJECTSTATE_H
#define CHAPAEV_IOBJECTSTATE_H


class IObjectState {
public:
    virtual void update_state(const int&) = 0;
};


#endif //CHAPAEV_IOBJECTSTATE_H
