#include <iostream>
#include <vector>
#include <string>
#include "../Observer/LoggingObserver.h"

using namespace std;
//OBSERVER
Observer::~Observer() {

}

//SUBJECT
void Subject::Attach(Observer *observer) {

}
void Subject::Detach(Observer *observer) {

}
Subject::Subject() {

}
Subject::~Subject() {

}

void LogObserver::Update(ILoggable) {
    stringToLog();
}
