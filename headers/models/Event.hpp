#pragma once

#include <vector>

// An implementation of the Observable pattern
class Event
{
    std::vector<Observer *> observers;

public:
    void attach(Observer *o)
    {
        observers.push_back(o);
    }

    void detach(Observer *o)
    {
        std::remove_if(observers.begin(), observers.end(), o);
    }

    void notify()
    {
        for (auto &o : observers)
        {
            o->update(this);
        }
    }
};

// An abstract class used to subscribe to Events
class Observer
{
public:
    virtual void update(Event *) = 0;
};