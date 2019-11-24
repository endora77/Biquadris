#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "Observer.h"
class Subject{
    std::vector<Observer*> Observers;
public:
    void attach(const Observer* obs){
        Observers.emplace_back(obs);
    }
    void detach(const Observer* obs){
        for(auto a = Observers.begin(); a != Observers.end(); a++){
            if(*a == obs) Observers.erase(a);
        }
    }
    void notifyObservers() const {
        for(auto &a : Observers){
            a->notify();
        }
    }
    virtual int getState() const = 0;

};

#endif