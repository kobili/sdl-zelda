#ifndef ECS_ENTITY_H
#define ECS_ENTITY_H

class Entity {
public:
    Entity(int id);

    int get_id();

private:
    int m_id;
};

#endif
