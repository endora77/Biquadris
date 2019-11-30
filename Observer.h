#ifndef OBSERVER_H
#define OBSERVER_H
class Subject;
class Observer{
public:
    virtual void notify(){}
    virtual void notify(Subject* s){}
};

#endif
