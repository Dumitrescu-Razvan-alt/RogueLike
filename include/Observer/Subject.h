
#pragma once
#include <algorithm>
#include <vector>
#include "Observer.h"

class Subject {
public:
    void AddObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void RemoveObserver(Observer* observer) {
        observers.erase(
            std::remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
    }

protected:
    void Notify() {
        for (auto observer : observers) {
            observer->OnNotify(this);
        }
    }

private:
    std::vector<Observer*> observers;
};
