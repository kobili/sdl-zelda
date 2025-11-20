#ifndef ECS_ENTITY_H
#define ECS_ENTITY_H

#include <cstddef>     // for std::size_t
#include <functional>  // for std::hash

class Entity {
public:
    Entity(int id);

    int get_id() const;

    bool is_active() const;
    void deactivate();

    bool operator==(const Entity& other) const {
        return m_id == other.m_id;
    }

private:
    int m_id;
    bool m_is_active;
};

namespace std {
    template <>
    struct hash<Entity> {
        std::size_t operator()(const Entity& e) const noexcept {
            return std::hash<int>()(e.get_id());
        }
    };
}

#endif
