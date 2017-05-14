#include "stack.h"

Stack::Stack(QObject *parent) :
    QObject(parent)
{
}

Stack::~Stack()
{
}

bool Stack::isFull()
{
    return _top >= MAX_SIZE ? true : false;
}

bool Stack::isEmpty()
{
    return _rules.isEmpty();
}

void Stack::initialize()
{
    _top = -1;
}

void Stack::push(GrammarRule grammar)
{
    if (!isFull()) {
        _top++;
        _rules.append(grammar);
    } else {
        return;
    }
}

GrammarRule Stack::pop()
{
    if (!isEmpty()) {
        _top--;
        return _rules.takeLast();
    } else {
        return GrammarRule();
    }
}
