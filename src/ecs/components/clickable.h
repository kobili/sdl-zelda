#ifndef CLICKABLE_H
#define CLICKABLE_H

#include <functional>

#include "../entity.h"

typedef std::function<void(Entity&)> ClickHandler;


class Clickable {
public:
    Clickable(ClickHandler handler);

    ClickHandler get_callback() const;

private:
    ClickHandler on_click;
};

#endif
