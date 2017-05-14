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

    void expand(Table &bangi, GrammarRules grammars, int i, int check[], Stack &s, GrammarRule tam, int t);
    void backTracking(Table bangi[], Stack &s, GrammarRule tam, int m, int n);

    void initializeTable(Table &bang0, GrammarRules grammars, int i);
    void generateTable(Table bangi[], GrammarRules grammars, int i, int m, QStringList s1, int n);

    bool analyseGrammar(GrammarRules grammars, Dictionaries dictionaries);
};

#endif // EARLEYALGORITHM_H
