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
    int i = 0;
    //initializeGrammar(a);
    GrammarRules grammars = grammarReader();
    Dictionaries dictionaries = dictionaryReader();

    return analyseGrammar(grammars, dictionaries, i);
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
            dictionaries.append(Dictionary(values[0],
                                QStringList() << values[1].split(QRegExp("\\,|\\ "), QString::SkipEmptyParts)));
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

void EarleyAlgorithm::expand(Table &table, GrammarRules grammars, Stack &stack, GrammarRule temp, QList<int> check, int i, int t)
{
    for (int j = 0; j < i; j++) {
        if (grammars[j].left() == temp.right().at(temp.pointer()) && check[j] == 0) {
            check[j] = 1;

            table.itemAt(table.length()).copy(grammars[j]);
            table.itemAt(table.length()).setPointer(0);
            table.itemAt(table.length()).setItems(t);

            stack.push(table.itemAt(table.length()));

            table.setLength(table.length() + 1);
        }
    }
}

void EarleyAlgorithm::backTracking(Tables tables, Stack &stack, GrammarRule temp, int m, int n)
{
    int check = 0;

    for (int j = 0; j < tables[temp.items()].length(); j++) {
        if (temp.left() == tables[temp.items()].itemAt(j).right().at(tables[temp.items()].itemAt(j).pointer()) && check == 0) {
            tables[m].itemAt(tables[m].length()).copy(tables[temp.items()].itemAt(j));
            tables[m].itemAt(tables[m].length()).setPointer(tables[m].itemAt(tables[m].length()).pointer() + 1);

            stack.push(tables[m].itemAt(tables[m].length()));

            tables[m].setLength(tables[m].length() + 1);

            if (n == m && tables[temp.items()].itemAt(j).left() == "S") {
                check = 1;
            }
        }
    }
}

void EarleyAlgorithm::initializeTable(Table &table, GrammarRules grammars, int i)
{
    int k = 0;
    int flag = 0;

    Stack stack;

    initializeStack(stack);
    QList<int> check;

    for (int j = 0; j < i; j++) {
        check.append(0);
    }

    for (int j = 0; j < i && flag != 2; j++) {
        if (grammars[j].left() == "S") {
            table.itemAt(k).copy(grammars[j]);

            table.itemAt(k).setPointer(0);
            table.itemAt(k).setItems(0);
            table.setLength(k + 1);

            stack.push(table.itemAt(k));

            k++;

            flag = 1;
        }

        if (flag == 1 && grammars[j].left() != "S") {
            flag = 2;
        }
    }

    while (!stack.isEmpty()) {
        GrammarRule temp;
        temp = stack.pop();

        QString token = temp.right().at(temp.pointer());

        if (token[0] >= 'A' && token[0] <= 'Z') {
            expand(table, grammars, stack, temp, check, i, 0);
        }
    }
}

void EarleyAlgorithm::generateTable(Tables tables, GrammarRules grammars, int i, int m, QStringList s1, int n)
{
    int k = 0;
    Stack stack;
    initializeStack(stack);
    QList<int> check;

    for (int j = 0; j < i; j++) {
        check.append(0);
    }

    for (int j = 0; j < tables[m - 1].length(); j++) {
        if (s1[m - 1] == tables[m - 1].itemAt(j).right().at(tables[m - 1].itemAt(j).pointer())) {
            tables[m].itemAt(k).copy(tables[m - 1].itemAt(j));
            tables[m].itemAt(k).setPointer(tables[m].itemAt(k).pointer() + 1);
            tables[m].setLength(k + 1);

            stack.push(tables[m].itemAt(k));

            k++;
        }
    }

    while (!stack.isEmpty()) {
        GrammarRule temp;
        temp = stack.pop();

        if (m == n && temp.left() == "S") {
            break;
        }

        QString token = temp.right().at(temp.pointer());

        if (temp.pointer() == temp.length()) {
            backTracking(tables, stack, temp, m, n);
        }

        if (token[0] >= 'A' && token[0] <= 'Z') {
            expand(tables[m], grammars, stack, temp, check, i, m);
        }
    }
}

bool EarleyAlgorithm::analyseGrammar(GrammarRules grammars, Dictionaries dictionaries, int i)
{
    int k = 0;

    QStringList types = analyseWord(dictionaries);

    Tables tables;

    Table table;

    initializeTable(table, grammars, i);

    qDebug() << "bang 0:";

    print(table);

    tables.append(table);

    for (int m = 1; m <= k; m++) {
        Table table;
        table.setLength(0);

        tables.append(table);
    }

    for (int m = 1; m <= k; m++) {
        generateTable(tables, grammars, i, m, types, k);

        qDebug() << "bang " << m << ":";
        print(tables[m]);
    }

    int u = tables[k].itemAt(tables[k].length() - 1).pointer();
    int v = tables[k].itemAt(tables[k].length() - 1).length();

    if (tables[k].itemAt(tables[k].length() - 1).left() == "S" && u == v) {
        return true;
    } else {
        return false;
    }
}
