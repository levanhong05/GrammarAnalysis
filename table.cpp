#include "table.h"

Table::Table()
{
}

Table::~Table()
{
}

int Table::length() const
{
    return _length;
}

void Table::setLength(int length)
{
    _length = length;
}

GrammarRule Table::itemAt(int index)
{
    return _items.at(index);
}
