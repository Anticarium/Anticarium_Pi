#include "PIDValues.h"

int PIDValues::getP() const {
    return p;
}

void PIDValues::setP(int p) {
    this->p = p;
}

int PIDValues::getI() const {
    return i;
}

void PIDValues::setI(int i) {
    this->i = i;
}

int PIDValues::getD() const {
    return d;
}

void PIDValues::setD(int d) {
    this->d = d;
}
