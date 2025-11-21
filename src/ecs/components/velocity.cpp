#include "velocity.h"


Velocity::Velocity() {
    m_vel_x = 0;
    m_vel_y = 0;
}


Velocity::Velocity(double vel_x, double vel_y) {
    m_vel_x = vel_x;
    m_vel_y = vel_y;
}


double Velocity::get_x() const {
    return m_vel_x;
}


double Velocity::get_y() const {
    return m_vel_y;
}


void Velocity::set_x(double x) {
    m_vel_x = x;
}


void Velocity::set_y(double y) {
    m_vel_y = y;
}


bool Velocity::in_motion() {
    return m_vel_x || m_vel_y;
}
