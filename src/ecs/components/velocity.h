#ifndef VELOCITY_H
#define VELOCITY_H


class Velocity {
public:
    Velocity();
    Velocity(float vel_x, float vel_y);

    float get_x() const;
    float get_y() const;

    void set_x(float x);
    void set_y(float y);

    bool in_motion();

private:
    float m_vel_x, m_vel_y;
};

#endif
