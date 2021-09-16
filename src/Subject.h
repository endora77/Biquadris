#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "Observer.h"
class Subject{
    std::vector<Observer*> Observers;
public:
    //Attach the observer
    void attach(Observer* obs){
        Observers.emplace_back(obs);
    }
    //Detatch the observer
    void detach(Observer* obs){
        for(auto a = Observers.begin(); a != Observers.end(); a++){
            if(*a == obs) Observers.erase(a);
        }
    }
    //Notify all the observers
    void notifyObservers() const {
        for(auto &a : Observers){
            a->notify();
        }
    }
    //Notify all the observers
    void notifyObservers(Subject* s) const {
        for(auto &a : Observers){
            a->notify(s);
        }
    }
    //Get the state of the subject
    virtual int getState() const = 0;

};

#endif
