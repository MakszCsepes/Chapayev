#ifndef CHAPAEV_IINTERFACE_H
#define CHAPAEV_IINTERFACE_H

#endif //CHAPAEV_IINTERFACE_H
#include "SFML/Graphics.hpp"
#include "Physics.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 750

class IDrawable {
public:
    virtual void draw() = 0;
};