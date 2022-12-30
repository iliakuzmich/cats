#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>
#include <QGraphicsItem>

class block : public QObject
{
    Q_OBJECT
public:
    explicit block(QObject *parent = nullptr);
    block(block const &a);
    int x = 0;
    int y = 0;
    void setpos(int X, int Y);
};

class platform: public QObject
{
    Q_OBJECT
public:
    explicit platform(QObject *parent = nullptr);
    platform(platform const &a);
    int x = 0;
    int y = 0;
    void setpos(int X, int Y);
};

#endif // BLOCK_H
