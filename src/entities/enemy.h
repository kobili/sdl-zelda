#ifndef ENEMY_H
#define ENEMY_H

#include "clickable_entity.h"

class Enemy : public ClickableEntity {
public:
    using ClickableEntity::ClickableEntity;

private:
    void on_click() override;
};

#endif
