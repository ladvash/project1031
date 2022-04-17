#ifndef CONSOLE_H
#define CONSOLE_H

#include <QPlainTextEdit>
#include "qcustomplot.h"

class CONSOLE : public QPlainTextEdit
{
    Q_OBJECT

signals:
    void getData(const QByteArray &data);

public:
    explicit CONSOLE(QWidget *parent = nullptr);
    void putData(const int, QCustomPlot &Graph);

protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
    long N;
    QVector<double> Y;
    int count;
    QByteArray firstbyte;

};

#endif // CONSOLE_H
