#ifndef TABLE_H
#define TABLE_H

#include <QObject>

#include "grammarrule.h"

class Table : public QObject
{
    Q_OBJECT
public:
    explicit Table(QObject *parent = 0);
    ~Table();

    int length() const;
    void setLength(int length);

    GrammarRule itemAt(int index);

private:
    GrammarRules _items;
    int _length;

};

#endif // TABLE_H
