#ifndef CLICKABLE_H
#define CLICKABLE_H

#include <functional>


typedef std::function<void(int)> ClickHandler;


class Clickable {
public:
    Clickable(ClickHandler handler);

    ClickHandler get_callback() const;

private:
    ClickHandler on_click;
};

#endif
