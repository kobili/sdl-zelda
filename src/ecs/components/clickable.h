#ifndef CLICKABLE_H
#define CLICKABLE_H

#include <functional>
#include "SDL.h"


typedef std::function<void(Uint32)> ClickHandler;


class Clickable {
public:
    Clickable(ClickHandler handler);

    ClickHandler get_callback() const;

private:
    ClickHandler on_click;
};

#endif
