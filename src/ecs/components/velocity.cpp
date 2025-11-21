#include "velocity.h"


Velocity::Velocity() {
    m_vel_x = 0;
    m_vel_y = 0;
}


Velocity::Velocity(float vel_x, float vel_y) {
    m_vel_x = vel_x;
    m_vel_y = vel_y;
}


float Velocity::get_x() const {
    return m_vel_x;
}


float Velocity::get_y() const {
    return m_vel_y;
}


void Velocity::set_x(float x) {
    m_vel_x = x;
}


void Velocity::set_y(float y) {
    m_vel_y = y;
}


bool Velocity::in_motion() {
    return m_vel_x || m_vel_y;
}
