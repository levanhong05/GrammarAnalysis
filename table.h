#ifndef TABLE_H
#define TABLE_H

#include <QObject>

#include "grammarrule.h"

class Table
{
public:
    Table();
    ~Table();

    int length() const;
    void setLength(int length);

    GrammarRule itemAt(int index);

private:
    GrammarRules _items;
    int _length;

};

typedef QList<Table> Tables;

#endif // TABLE_H
