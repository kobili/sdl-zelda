#ifndef WINDOW_OBSERVER_H
#define WINDOW_OBSERVER_H

#include <vector>

class ObservableWindow;

class WindowObserver {
public:
    void virtual start_observing(ObservableWindow* observerable);
    void virtual on_window_resize(int w, int h) = 0;
};


class ObservableWindow {
public:
    void virtual add_observer(WindowObserver* observer);
    void virtual notify_observers() = 0;

protected:
    std::vector<WindowObserver*> observers;
};

#endif
