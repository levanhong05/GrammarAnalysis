#include "grammarrule.h"

GrammarRule::GrammarRule()
{
    _length = 0;
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
