#include "observer.h"

void Observer::start_observing(Observable* observable) {
    observable->add_observer(this);
}


void Observable::add_observer(Observer* observer) {
    observers.push_back(observer);
}
