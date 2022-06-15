#include "PIDValues.h"

double PIDValues::getP() const {
    return p;
}

void PIDValues::setP(double p) {
    this->p = p;
}

double PIDValues::getI() const {
    return i;
}

void PIDValues::setI(double i) {
    this->i = i;
}

double PIDValues::getD() const {
    return d;
}

void PIDValues::setD(double d) {
    this->d = d;
}
