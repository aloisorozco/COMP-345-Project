#include "../Observer/LoggingObserver.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>


using namespace std;
//ILoggable PURE VIRTUAL CLASS
ILoggable::ILoggable()=default;
ILoggable::~ILoggable()= default;
ILoggable::ILoggable(const ILoggable &) {}
ILoggable &ILoggable::operator=(const ILoggable &) {return *this;}
ostream &operator<<(ostream& out, const ILoggable &) {return out ;}


//SUBJECT
Subject::Subject() {
    _observers = new list<Observer*>;}
Subject::~Subject() {
    delete _observers;
}
void Subject::Attach(Observer* o){
    _observers->push_back(o);
};
void Subject::Detach(Observer* o){
    _observers->remove(o);
};
void Subject::Notify(ILoggable *iLoggable) {
    list<Observer *>::iterator i = _observers->begin();
    for (; i != _observers->end(); ++i) {
        (*i)->Update(iLoggable);
    }
}
Subject::Subject(const Subject &) {}
Subject &Subject::operator=(const Subject &) {return *this;}
ostream &operator<<(ostream& out, const Subject &) {return out ;}



//OBSERVER
Observer::Observer() {};
Observer::~Observer() {};
Observer::Observer(const Observer &) {}
Observer &Observer::operator=(const Observer &) {return *this;}
ostream &operator<<(ostream &os, const Observer &observer) {return os;}

//LOG OBSERVER

LogObserver::LogObserver() = default;
void LogObserver::AddSubject(Subject* s) {
    _subject.push_back(s);
    s->Attach(this);
}
LogObserver::~LogObserver(){
    //Upon destruction, detaches itself from its Subject
    for(Subject* s : _subject)
        s->Detach(this);
}
//LogObserver::LogObserver(OrdersList* s) {
//    _ordersList_subject = s;
//    _ordersList_subject->Subject::Attach(this);
//
//}
//
//LogObserver::LogObserver(GameEngine* s) {
//    _gameEngine_subject = s;
//    _gameEngine_subject ->Subject::Attach(this);
//
//}
//LogObserver::LogObserver(CommandProcessor *commandProcessor) {
//
//}
//LogObserver::LogObserver(FileCommandProcessorAdapter *fileCommandProcessorAdapter) {
//
//}
//We want to open a file and append to the end of it.
void LogObserver::Update(ILoggable* iLoggable) {
    ofstream log;
    log.open("gamelog.txt", ofstream::app);
    log<<iLoggable->stringToLog() << endl;
    log.close();
}
LogObserver::LogObserver(const LogObserver &) {}
LogObserver &LogObserver::operator=(const LogObserver &) {return *this;}
ostream &operator<<(ostream &os, const LogObserver &logObserver) {return os;}

const vector<Subject *> &LogObserver::getSubject() const {
    return _subject;
}


