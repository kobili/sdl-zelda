#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

class Position {
public:
    Position(float x, float y);

    float get_x();
    float get_y();
    void set_x(float val);
    void set_y(float val);

private:
    float m_x, m_y;
};

#endif
