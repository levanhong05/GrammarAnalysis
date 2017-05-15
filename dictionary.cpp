#include "dictionary.h"

Dictionary::Dictionary(QString content, QStringList classifier)
{
    _word = content;
    _classifier = classifier;
}

Dictionary::~Dictionary()
{
}

QString Dictionary::word() const
{
    return _word;
}

void Dictionary::setWord(const QString &word)
{
    _word = word;
}

QStringList Dictionary::classifier() const
{
    return _classifier;
}

void Dictionary::addClassifier(const QString &classifier)
{
    _classifier.append(classifier);
}

void Dictionary::setClassifier(const QStringList &classifier)
{
    _classifier = classifier;
}
