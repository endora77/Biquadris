#ifndef OBSERVER_H
#define OBSERVER_H
class Subject;
class Observer{
public:
    //Two ways of getting notificationf from the subject
    virtual void notify(){}
    virtual void notify(Subject* s){}
};

#endif
