#ifndef STACK_H
#define STACK_H

#include <QObject>

#include "grammarrule.h"

#define MAX_SIZE 100

class Stack
{
public:
    Stack();
    ~Stack();

    bool isFull();
    bool isEmpty();

    void initialize();

    void push(GrammarRule grammar);
    GrammarRule pop();

private:
    GrammarRules _rules;
    int _top;
};

#endif // STACK_H
