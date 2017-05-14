#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QObject>

class Dictionary : public QObject
{
    Q_OBJECT
public:
    explicit Dictionary(QString content = "", QString classifier = "", QObject *parent = 0);
    ~Dictionary();

    QString word() const;
    void setWord(const QString &word);

    QStringList classifier() const;
    void setClassifier(const QStringList &classifier);
    void addClassifier(const QString &classifier);

private:
    QString _word;
    QStringList _classifier;

};

typedef QList<Dictionary> Dictionaries;

#endif // DICTIONARY_H
