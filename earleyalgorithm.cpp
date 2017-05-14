#include "earleyalgorithm.h"

#include <QFile>
#include <QTextStream>

#include <QDebug>

EarleyAlgorithm::EarleyAlgorithm(QObject *parent) :
    QObject(parent)
{
}

EarleyAlgorithm::~EarleyAlgorithm()
{
}

bool EarleyAlgorithm::excute()
{
    //initializeGrammar(a);
    GrammarRules grammars = grammarReader();
    Dictionaries dictionaries = dictionaryReader();
    cout << analyseGrammar(grammars, dictionaries);
}


void EarleyAlgorithm::initializeStack(Stack &stack)
{
    stack.initialize();
}

Dictionaries EarleyAlgorithm::dictionaryReader()
{
    QFile file("tudien.txt");

    if (!file.open(QIODevice::ReadOnly)) {
        return Dictionaries();
    }

    QTextStream in(&file);
    QString line = "";
    Dictionaries dictionaries;

    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        QStringList values = line.split(QRegExp("\\\t"), QString::SkipEmptyParts);

        if (values.size() == 2) {
            dictionaries.append(Dictionary(values[0], values[1]));
        } else if (values.size() == 1) {
            dictionaries.append(Dictionary(values[0]));
        }
    }

    file.close();
    return dictionaries;
}

//void EarleyAlgorithm::initializeGrammar(GrammarRules grammars, int i)
//{

//}

GrammarRules EarleyAlgorithm::grammarReader()
{
    QFile file("nguphap.txt");

    if (!file.open(QIODevice::ReadOnly)) {
        return GrammarRules();
    }

    QTextStream in(&file);
    QString line = "";
    GrammarRules grammars;

    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        QStringList values = line.split("=", QString::SkipEmptyParts);

        if (values.size() == 2) {
            GrammarRule grammar;
            grammar.setLeft(values[0].trimmed());
            QStringList tokens = values[1].split(" ", QString::SkipEmptyParts);
            grammar.setRight(tokens);
            grammar.setLength(tokens.size());
            grammars.append(grammar);
        }
    }

    file.close();
    return grammars;
}

QStringList EarleyAlgorithm::checkWord(Dictionaries dictionaries, QString token)
{
    for (int i = 0; i < dictionaries.size(); i++) {
        if (token == dictionaries[i].word()) {
            return dictionaries[i].classifier();
        }
    }

    return QStringList();
}

QStringList EarleyAlgorithm::analyseWord(Dictionaries dictionaries)
{
    QFile file("text.txt");

    if (!file.open(QIODevice::ReadOnly)) {
        return QStringList();
    }

    QTextStream in(&file);
    QString line = "";
    QStringList tokens;
    QStringList types;

    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        tokens = line.split(QRegExp("\\ "), QString::SkipEmptyParts);

        foreach (QString token, tokens) {
            types.append(checkWord(dictionaries, token));
        }
    }

    file.close();
    return types;
}

void EarleyAlgorithm::print(Table table)
{
    for (int i = 0; i < table.length(); i++) {
        qDebug() << table.itemAt(i).left() << '=';

        for (int m = 0; m < table.itemAt(i).length(); m++) {
            qDebug() << table.itemAt(i).right().at(m) << " ";
        }

        qDebug() << table.itemAt(i).items();
    }
}

void EarleyAlgorithm::expand(Table &bangi, GrammarRules grammars, int i, int check[], Stack &s, GrammarRule tam, int t)
{
    for (int j = 0; j < i; j++) {
        if (grammars[j].trai == tam.phai[tam.contro] && check[j] == 0) {
            check[j] = 1;
            bangi.tram[bangi.sotram] = grammars[j];
            bangi.tram[bangi.sotram].contro = 0;
            bangi.tram[bangi.sotram].item = t;
            push(s, bangi.tram[bangi.sotram]);
            bangi.sotram++;
        }
    }
}

void EarleyAlgorithm::backTracking(Table bangi[], Stack &s, GrammarRule tam, int m, int n)
{
    int check = 0;

    for (int j = 0; j < bangi[tam.item].sotram; j++) {
        if (tam.trai == bangi[tam.item].tram[j].phai[bangi[tam.item].tram[j].contro] && check == 0) {
            bangi[m].tram[bangi[m].sotram] = bangi[tam.item].tram[j];
            bangi[m].tram[bangi[m].sotram].contro++;
            push(s, bangi[m].tram[bangi[m].sotram]);
            bangi[m].sotram++;

            if (n == m && bangi[tam.item].tram[j].trai == "S") {
                check = 1;
            }
        }
    }
}

void EarleyAlgorithm::initializeTable(Table &bang0, GrammarRules grammars, int i)
{
    int k = 0;
    int flag = 0;
    stack s;
    initializeStack(s);
    int check[i];

    for (int j = 0; j < i; j++) {
        check[j] = 0;
    }

    for (int j = 0; j < i && flag != 2; j++) {
        if (grammars[j].trai == "S") {
            bang0.tram[k] = grammars[j];
            bang0.tram[k].contro = 0;
            bang0.tram[k].item = 0;
            bang0.sotram = k + 1;
            push(s, bang0.tram[k]);
            k++;
            flag = 1;
        }

        if (flag == 1 && grammars[j].trai != "S") {
            flag = 2;
        }
    }

    while (isEmpty(s) != 1) {
        nguphap tam;
        pop(s, tam);
        string b = tam.phai[tam.contro];

        if (b[0] >= 'A' && b[0] <= 'Z') {
            expand(bang0, grammars, i, check, s, tam, 0);
        }
    }
}

void EarleyAlgorithm::generateTable(Table bangi[], GrammarRules grammars, int i, int m, QStringList s1, int n)
{
    int k = 0;
    stack s;
    initializeStack(s);
    int check[i];

    for (int j = 0; j < i; j++) {
        check[j] = 0;
    }

    for (int j = 0; j < bangi[m - 1].sotram; j++) {
        if (s1[m - 1] == bangi[m - 1].tram[j].phai[bangi[m - 1].tram[j].contro]) {
            bangi[m].tram[k] = bangi[m - 1].tram[j];
            bangi[m].tram[k].contro++;
            bangi[m].sotram = k + 1;
            push(s, bangi[m].tram[k]);
            k++;
        }
    }

    while (isEmpty(s) != 1) {
        nguphap tam;
        pop(s, tam);

        if (m == n && tam.trai == "S") {
            break;
        }

        string b = tam.phai[tam.contro];

        if (tam.contro == tam.dodai) {
            backTracking(bangi, s, tam, m, n);
        }

        if (b[0] >= 'A' && b[0] <= 'Z') {
            expand(bangi[m], grammars, i, check, s, tam, m);
        }
    }
}

bool EarleyAlgorithm::analyseGrammar(GrammarRules grammars, Dictionaries dictionaries)
{
    QString s[100];// toi da 100 tu trong 1 cau
    int k = 0;
    QStringList type = analyseWord(dictionaries);
    bang bangi[k + 1];
    initializeTable(bangi[0], grammars, i);
    cout << "bang 0:" << endl;
    xuatbang(bangi[0]);

    for (int m = 1; m <= k; m++) {
        bangi[m].sotram = 0;
    }

    for (int m = 1; m <= k; m++) {
        generateTable(bangi, grammars, i, m, s, k);
        cout << "bang " << m << ':' << endl;
        xuatbang(bangi[m]);
    }

    int u = bangi[k].tram[bangi[k].sotram - 1].contro;
    int v = bangi[k].tram[bangi[k].sotram - 1].dodai;

    if (bangi[k].tram[bangi[k].sotram - 1].trai == "S" && u == v) {
        return true;
    } else {
        return false;
    }
}
