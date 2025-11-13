#include "window_observer.h"

void WindowObserver::start_observing(ObservableWindow* observable) {
    observable->add_observer(this);
}


void ObservableWindow::add_observer(WindowObserver* observer) {
    observers.push_back(observer);
}
