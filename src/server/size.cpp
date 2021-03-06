//
// Created by rodian on 17/05/17.
//

#include "size.h"

Size::Size(int x, int y, int width, int height) : position(x,y),
                                               width(width), height(height){}

Position Size::getPosition() const {
    return this->position;
}

int Size::getWidth() const {
    return width;
}

int Size::getHeight() const {
    return height;
}

bool Size::isThereACollision(Size &other) {
    int x_max, x_min, y_max, y_min;
    bool collision = false;
    this->calculateMaxAndMinForX(x_max, x_min);
    this->calculateMaxAndMinForY(y_max, y_min);

    if (other.areYouOnThisPoint(x_max, y_max) ||
        other.areYouOnThisPoint(x_max, y_min) ||
        other.areYouOnThisPoint(x_min, y_max) ||
        other.areYouOnThisPoint(x_min, y_min)) {
        collision = true;
    }

    other.calculateMaxAndMinForX(x_max, x_min);
    other.calculateMaxAndMinForY(y_max, y_min);
    if (this->areYouOnThisPoint(x_max, y_max) ||
            this->areYouOnThisPoint(x_max, y_min) ||
            this->areYouOnThisPoint(x_min, y_max) ||
            this->areYouOnThisPoint(x_min, y_min)) {
        collision = true;
    }

   return collision;
}


bool Size::areYouHalfOutSide(Size &other) {
    int x_max, x_min, y_max, y_min;
    other.calculateMaxAndMinForX(x_max, x_min);
    other.calculateMaxAndMinForY(y_max, y_min);

    // If a point is not inside returns true
    return (!this->areYouOnThisPoint(x_max, y_max) ||
            !this->areYouOnThisPoint(x_max, y_min) ||
            !this->areYouOnThisPoint(x_min, y_max) ||
            !this->areYouOnThisPoint(x_min, y_min));
}

bool Size::areYouOnThisPoint(int x_pos, int y_pos) {
    int x_max, x_min, y_max, y_min;
    this->calculateMaxAndMinForX(x_max, x_min);
    this->calculateMaxAndMinForY(y_max, y_min);

    return ((x_pos < x_max) && (x_pos >= x_min) &&
            (y_pos < y_max) && (y_pos >= y_min));
}

void Size::calculateMaxAndMinForX(int &max, int &min) {
    max = position.getX() + width;
    min = position.getX();
}

void Size::calculateMaxAndMinForY(int &max, int &min) {
    max = position.getY() + height;
    min = position.getY();
}

void Size::moveTo(int x, int y) {
    position.moveTo(x,y);
}

Size::~Size() {}

