#ifndef STACK_H
#define STACK_H

#include <QObject>

#include "grammarrule.h"

#define MAX_SIZE 100

class Stack : public QObject
{
    Q_OBJECT
public:
    explicit Stack(QObject *parent = 0);
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
