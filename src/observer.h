#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>

class Observable;

class Observer {
public:
    void virtual start_observing(Observable* observerable);
    void virtual observe(int w, int h) = 0;
};


class Observable {
public:
    void virtual add_observer(Observer* observer);
    void virtual notify_observers() = 0;

protected:
    std::vector<Observer*> observers;
};

#endif
