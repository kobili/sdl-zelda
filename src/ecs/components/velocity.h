#ifndef VELOCITY_H
#define VELOCITY_H


class Velocity {
public:
    Velocity();
    Velocity(double vel_x, double vel_y);

    double get_x() const;
    double get_y() const;

    void set_x(double x);
    void set_y(double y);

    bool in_motion();

private:
    double m_vel_x, m_vel_y;
};

#endif
