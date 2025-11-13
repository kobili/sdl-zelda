#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <memory>

#include "entity.h"
#include "../utils.h"
#include "../clickable.h"
#include "../observers/window_observer.h"
#include "../cameras/camera.h"


const int DEFAULT_VELOCITY = 1;


class Player : public Entity {
public:
    Player() {};
    Player(SpriteSheet* sprite, ObservableWindow* window, Camera* camera);

    void handle_event(SDL_Event& e);

    void move(std::vector<SDL_Rect*> colliders) override;

    Zone get_current_zone();

    void set_x(int x);
    void set_y(int y);

private:
    std::unique_ptr<ClickHitbox> click_hitbox;
};

void player_on_click(int x, int y);

#endif
