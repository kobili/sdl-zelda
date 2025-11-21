#include "position.h"


Position::Position(float x, float y) {
    m_x = x;
    m_y = y;
}

float Position::get_x() {
    return m_x;
}

float Position::get_y() {
    return m_y;
}


void Position::set_x(float val) {
    m_x = val;
}


void Position::set_y(float val) {
    m_y = val;
}
