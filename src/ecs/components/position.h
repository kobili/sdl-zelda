#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

class Position {
public:
    Position(int x, int y);

    int get_x();
    int get_y();

private:
    int m_x, m_y;
};

#endif
