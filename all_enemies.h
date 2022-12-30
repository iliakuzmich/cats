#ifndef ALL_ENEMIES_H
#define ALL_ENEMIES_H

#include <QObject>
#include <enemy.h>
#include <boss.h>

class all_enemies : public QObject
{
    Q_OBJECT
public:
    explicit all_enemies(QObject *parent = nullptr);
    std::vector<enemy> en;
    Boss *boss;
    void spawn();
    void calckHD();
    int D = 0;
    int kK = 0;
    QTimer *ahtimer;
    QTimer *spawntimer;

};

#endif // ALL_ENEMIES_H
