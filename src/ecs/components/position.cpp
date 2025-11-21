#include "position.h"


Position::Position(double x, double y) {
    m_x = x;
    m_y = y;
}

double Position::get_x() {
    return m_x;
}

double Position::get_y() {
    return m_y;
}


void Position::set_x(double val) {
    m_x = val;
}


void Position::set_y(double val) {
    m_y = val;
}
