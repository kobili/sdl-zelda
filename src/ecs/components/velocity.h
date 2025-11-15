#ifndef VELOCITY_H
#define VELOCITY_H


class Velocity {
public:
    Velocity();
    Velocity(int vel_x, int vel_y);

    int get_x() const;
    int get_y() const;

    void add_x(int x);
    void add_y(int y);

private:
    int m_vel_x, m_vel_y;
};

#endif
