#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

class Position {
public:
    Position(double x, double y);

    double get_x();
    double get_y();
    void set_x(double val);
    void set_y(double val);

private:
    double m_x, m_y;
};

#endif
