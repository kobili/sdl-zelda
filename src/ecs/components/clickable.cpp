#include "clickable.h"


Clickable::Clickable(ClickHandler handler) {
    on_click = handler;
}


ClickHandler Clickable::get_callback() const {
    return on_click;
}
