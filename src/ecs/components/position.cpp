#include "position.h"


Position::Position(int x, int y) {
    m_x = x;
    m_y = y;
}

int Position::get_x() {
    return m_x;
}

int Position::get_y() {
    return m_y;
}


void Position::set_x(int val) {
    m_x = val;
}


void Position::set_y(int val) {
    m_y = val;
}
