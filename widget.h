#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QShortcut>
#include <QPixmap>
#include <QDialog>

#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QCoreApplication>

#include "cat.h"
#include "all_enemies.h"
#include "valeryana.h"
#include "block.h"
#include "human.h"
#include "music.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    int dificulty = 0;

    int where = 0;
    music m;
    Widget(QWidget *parent = nullptr);
    ~Widget();
    virtual void paintEvent(QPaintEvent *event) override;
    void generate_blocks(int array[37][60]);
    void generate_enem();
    int time = 40;
    void gameOver();
    void ggwp();
    void timers_stop();
    void timers_start();

    void opendor();
    block b;
    std::vector<block> blocks;

    QTimer* gtimer;

signals:
    void down(); // остановитьб таймер прыжка

public slots:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void rep();
    void colide();
    void colide_enem();
    void colide_boss();
    void colide_val();
    void colide_bowl();
    void volide_human_enemy();
    void atack_H();
    void is_vin();


private slots:
    void on_button_clicked();
    void on_exitbutton_clicked();
    void on_difbutton_clicked();
    void on_esc_clicked();
    void on_button1_clicked();
    void on_button2_clicked();


private:
    Ui::Widget *ui;
    Cat *cat;
    QGraphicsScene *scene;
    QTimer *timer;

    platform pl;
    std::vector<platform> platforms;

    valeryana *val;
    enemy e;
    all_enemies *enem;
    human* h;

    QLabel *lable;
    QLabel *lable2;
    QPushButton *ledButton;
    QPushButton *exitButton;
    QPushButton *difButton;
    QPushButton *Button1;
    QPushButton *Button2;

private slots:
    void pauseSlot();
};
#endif // WIDGET_H
