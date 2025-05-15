#pragma once

class Subject;

class Observer {
public:
    virtual ~Observer() = default;
    virtual void OnNotify(Subject* subject) = 0;
};
