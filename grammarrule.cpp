#include "grammarrule.h"

GrammarRule::GrammarRule()
{
    _length = 0;
    _pointer = 0;
}

GrammarRule::~GrammarRule()
{
}

QString GrammarRule::left() const
{
    return _left;
}

void GrammarRule::setLeft(const QString &left)
{
    _left = left;
}

QStringList GrammarRule::right() const
{
    return _right;
}

void GrammarRule::setRight(const QStringList &right)
{
    _right = right;
}

int GrammarRule::length() const
{
    return _length;
}

void GrammarRule::setLength(int length)
{
    _length = length;
}

int GrammarRule::items() const
{
    return _items;
}

int GrammarRule::pointer() const
{
    return _pointer;
}

void GrammarRule::setPointer(int pointer)
{
    _pointer = pointer;
}

void GrammarRule::copy(GrammarRule grammar)
{
    _left = grammar.left();
    _right = grammar.right();

    _length = grammar.length();
    _items = grammar.items();
    _pointer = grammar.pointer();
}

void GrammarRule::setItems(int items)
{
    _items = items;
}
