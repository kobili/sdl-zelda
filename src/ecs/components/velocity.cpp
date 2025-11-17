#include "velocity.h"


Velocity::Velocity() {
    m_vel_x = 0;
    m_vel_y = 0;
}


Velocity::Velocity(int vel_x, int vel_y) {
    m_vel_x = vel_x;
    m_vel_y = vel_y;
}


int Velocity::get_x() const {
    return m_vel_x;
}


int Velocity::get_y() const {
    return m_vel_y;
}


void Velocity::add_x(int x) {
    m_vel_x += x;
}


void Velocity::add_y(int y) {
    m_vel_y += y;
}


bool Velocity::in_motion() {
    return m_vel_x || m_vel_y;
}
