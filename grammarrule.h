#ifndef GRAMMARRULE_H
#define GRAMMARRULE_H

#include <QObject>

class GrammarRule
{
public:
    GrammarRule();
    ~GrammarRule();

    QString left() const;
    void setLeft(const QString &left);

    QStringList right() const;
    void setRight(const QStringList &right);

    int length() const;
    void setLength(int length);

    int items() const;

private:
    QString _left;
    QStringList _right;

    int _length; //length of right-hand of rules
    int _items;
    int _pointer;

};

typedef QList<GrammarRule> GrammarRules;

#endif // GRAMMARRULE_H
