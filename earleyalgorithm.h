#ifndef EARLEYALGORITHM_H
#define EARLEYALGORITHM_H

#include <QObject>

#include "stack.h"
#include "table.h"
#include "dictionary.h"
#include "grammarrule.h"

class EarleyAlgorithm : public QObject
{
    Q_OBJECT
public:
    explicit EarleyAlgorithm(QObject *parent = 0);
    ~EarleyAlgorithm();

    bool excute();

private:
    void initializeStack(Stack &stack);

    Dictionaries dictionaryReader();

    //void initializeGrammar(GrammarRules grammars, int i);
    GrammarRules grammarReader();

    QStringList checkWord(Dictionaries dictionaries, QString token);
    QStringList analyseWord(Dictionaries dictionaries);

    void print(Table table);

    void expand(Table &table, GrammarRules grammars, Stack &stack, GrammarRule temp, QList<int> check, int i, int t);
    void backTracking(Tables tables, Stack &stack, GrammarRule temp, int m, int n);

    void initializeTable(Table &table, GrammarRules grammars, int i);
    void generateTable(Tables tables, GrammarRules grammars, int i, int m, QStringList s1, int n);

    bool analyseGrammar(GrammarRules grammars, Dictionaries dictionaries, int i);
};

#endif // EARLEYALGORITHM_H
