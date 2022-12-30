#include "widget.h"
#include "ui_widget.h"
#include "lvl.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::Widget)
{
    ui->setupUi(this);

    ledButton = new QPushButton("Начать игру", this);
    ledButton->setGeometry(QRect(QPoint(300, 300), QSize(200, 50)));
    connect(ledButton, SIGNAL(clicked()), this, SLOT(on_button_clicked()));

    exitButton = new QPushButton("Выход", this);
    exitButton->setGeometry(QRect(QPoint(300, 400), QSize(200, 50)));
    connect(exitButton, SIGNAL(clicked()), this, SLOT(on_exitbutton_clicked()));

    difButton = new QPushButton("Сложность", this);
    difButton->setGeometry(QRect(QPoint(300, 200), QSize(200, 50)));
    connect(difButton, SIGNAL(clicked()), this, SLOT(on_difbutton_clicked()));

    lable = new QLabel("Легко", this);
    lable2 = new QLabel("", this);
    lable->setGeometry(QRect(QPoint(550, 200), QSize(200, 50)));

    QShortcut *keyEsc = new QShortcut(this);
    keyEsc->setKey(Qt::Key_Escape);
    connect(keyEsc, &QShortcut::activated, this, &Widget::on_esc_clicked);
    Button1 = new QPushButton("Продолжить игру", this);
    Button1->setGeometry(QRect(QPoint(0, 0), QSize(0, 0)));
    connect(Button1, SIGNAL(clicked()), this, SLOT(on_button1_clicked()));
    Button2 = new QPushButton("Выйти в главное меню", this);
    Button2->setGeometry(QRect(QPoint(500, 0), QSize(0, 0)));
    connect(Button2, SIGNAL(clicked()), this, SLOT(on_button2_clicked()));

    this->resize(1080, 740);
    this->setFixedSize(1080, 740);
    //scene = new QGraphicsScene();
    cat = new Cat();
    cat->cXP -= dificulty * 10;
    cat->hXP -= dificulty * 10;
    val = new valeryana();
    enem = new all_enemies();
    h = new human();
    generate_blocks(lvl);
    generate_enem();
    //keyEsc->setKey(Qt::Key_Escape);
    //connect(keyEsc, &QShortcut::activated, this, &Widget::pauseSlot);

    //scene->setSceneRect(0, 0, 1080, 720);

    timer = new QTimer();
    Widget::connect(h->timer, &QTimer::timeout, this, &Widget::volide_human_enemy);
    Widget::connect(timer, &QTimer::timeout, this, &Widget::colide);
    Widget::connect(timer, &QTimer::timeout, this, &Widget::is_vin);
    Widget::connect(timer, &QTimer::timeout, cat, &Cat::regen);
    Widget::connect(enem->spawntimer, &QTimer::timeout, this, &Widget::opendor);
    Widget::connect(timer, &QTimer::timeout, this, &Widget::rep);
    Widget::connect(timer, &QTimer::timeout, this, &Widget::colide_val);
    Widget::connect(timer, &QTimer::timeout, this, &Widget::colide_bowl);
    Widget::connect(timer, &QTimer::timeout, this, &Widget::colide_enem);
    Widget::connect(cat->atacktimer, &QTimer::timeout, this, &Widget::colide_boss);
    Widget::connect(enem->ahtimer, &QTimer::timeout, this, &Widget::atack_H);
    Widget::connect(val, &valeryana::doXp, cat, &Cat::fillXP);

    //timers_stop();
    timer->start();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_button_clicked()
{
    timers_start();

    cat->cXP = 100 - dificulty * 10;
    cat->hXP = 150 - dificulty * 10;
    enem->spawn();

    ledButton->setGeometry(QRect(QPoint(100, 100), QSize(0, 0)));
    lable->setGeometry(QRect(QPoint(550, 200), QSize(0, 0)));
    difButton->setGeometry(QRect(QPoint(300, 200), QSize(0, 0)));
    exitButton->setGeometry(QRect(QPoint(300, 400), QSize(0, 0)));
    where = 1;
}

void Widget::on_exitbutton_clicked()
{
    close();
}

void Widget::on_difbutton_clicked()
{
    dificulty += 1;
    dificulty %= 3;

    if(dificulty == 0)
        lable->setText("Легко");
    if(dificulty == 1)
        lable->setText("Средне");
    if(dificulty == 2)
        lable->setText("Сложно");
}

void Widget::on_esc_clicked()
{
    if(where == 1){
        where = 2;
        Button1->setGeometry(QRect(QPoint(440, 280), QSize(200, 50)));
        Button2->setGeometry(QRect(QPoint(440, 450), QSize(200, 50)));
        timers_stop();
    }
}

void Widget::on_button1_clicked()
{
    timers_start();
    where = 1;
    Button1->setGeometry(QRect(QPoint(0, 0), QSize(0, 0)));
    Button2->setGeometry(QRect(QPoint(500, 0), QSize(0, 0)));
}

void Widget::on_button2_clicked()
{
    cat->x = 100;
    cat->y = 100;

    h->x = 200;
    h->y = 200;
    h->speed = 5;
    h->gif = new QMovie(":/res/img/h2.gif");
    h->gif->start();

    blocks.clear();
    generate_blocks(lvl);

    enem->boss->xtimer->stop();
    enem->boss->ytimer-> stop();
    enem->boss->switchdirx->stop();
    enem->boss->switchdiry->stop();

    enem->boss->x = 580;
    enem->boss->y = 450;
    enem->boss->hp = 100;
    enem->boss->xspeed = 6;
    enem->boss->yspeed = 3;

    enem->boss->xtimer->start(40);
    enem->boss->ytimer-> start(50);
    enem->boss->switchdirx->start(3000);
    enem->boss->switchdiry->start(3500);

    for(size_t i = 0; i < enem->en.size(); i++){
        enem->en[i].hp = 0;
    }

        enem->spawn();

//    cat = new Cat();
//    val = new valeryana();
//    enem = new all_enemies();
//    h = new human();
    timers_stop();
    where = 0;
    ledButton->setGeometry(QRect(QPoint(300, 300), QSize(200, 50)));
    difButton->setGeometry(QRect(QPoint(300, 200), QSize(200, 50)));
    exitButton->setGeometry(QRect(QPoint(300, 400), QSize(200, 50)));
    lable->setGeometry(QRect(QPoint(550, 200), QSize(200, 50)));
    Button1->setGeometry(QRect(QPoint(0, 0), QSize(0, 0)));
    Button2->setGeometry(QRect(QPoint(500, 0), QSize(0, 0)));
    lable2->setText("");
}

void Widget::rep()
{
    repaint();
}

void Widget::colide()
{
    for (size_t i = 0; i < blocks.size(); i++){
        if (cat->is_colide_b(blocks[i]) && cat->is_jump_now == 0){
            cat->y = blocks[i].y - 26;
            cat->is_pos_jump = 1;
            break;
        }
        else{
            cat->is_pos_jump = 0;
            cat->k = 10;
        }
    }

    for (size_t i = 0; i < platforms.size(); i++){
        if (cat->is_colide_b(platforms[i]) && cat->is_jump_now == 0){
            cat->y = platforms[i].y - 26;
            cat->is_pos_jump = 1;
            break;
        }
        else{
            cat->k = 10;
        }
    }

    for (size_t i = 0; i < blocks.size(); i++){
        if(cat->is_colide_l(blocks[i])){
            cat->x = blocks[i].x + 21;
        }
    }

    for (size_t i = 0; i < blocks.size(); i++){
        if(cat->is_colide_u(blocks[i])){
            cat->y = blocks[i].y + 21;
            cat->stopjump();
        }
    }

    if(cat->x >= 1100){
        cat->x = 0;
        cat->y += 300;
    }

    if(cat->x <= -10){
        cat->x = 1080;
        cat->y -= 380;
    }

    for (size_t i = 0; i < blocks.size(); i++){
        if(cat->is_colide_r(blocks[i])){
            cat->x = blocks[i].x - 26;
        }
    }
}

void Widget::keyPressEvent(QKeyEvent *event)
{
   if(event->text() == "a" || event->text() == "ф" || event->text() == "A" || event->text() == "Ф")
   {
        if(!cat->mltimer->isActive())
            cat->mltimer->start(time);
   }
   if(event->text() == "в" || event->text() == "В" || event->text() == "d" || event->text() == "D")
   {
       if(!cat->mrtimer->isActive())
            cat->mrtimer->start(time);
   }

   if(event->text() == "w" || event->text() == "W" || event->text() == "ц" || event->text() == "Ц")
   {
        if(cat->is_pos_jump == 1){
            cat->k = 0;
            cat->is_pos_jump = 0;
            cat->jtimer->start(time);
        }
   }
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    if(event->text() == "a" || event->text() == "ф" || event->text() == "A" || event->text() == "Ф")
    {
         cat->mltimer->stop();
    }
    if(event->text() == "в" || event->text() == "В" || event->text() == "d" || event->text() == "D")
    {
         cat->mrtimer->stop();
    }
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(where == 1){
        QPixmap pix1(":/res/img/block1.png");
        QPixmap pix2(":/res/img/b.png");
        painter.drawPixmap(0, 0, 1080, 720, pix2);

        for(size_t i = 0; i < blocks.size(); i++){
            painter.drawPixmap(blocks[i].x, blocks[i].y, 20, 20, pix1);
        }

        pix1 = QPixmap (":/res/img/block.png");
        for(size_t i = 0; i < platforms.size(); i++){
            painter.drawPixmap(platforms[i].x, platforms[i].y, 20, 20, pix1);
        }

        pix1 = QPixmap (":/res/img/val.png");
        painter.drawPixmap(val->x , val->y, 25, 25, pix1);

        painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
        painter.drawRect(50 , 10, cat->cXP * 3, 10);

        painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));
        painter.drawRect(400 , 10, cat->hXP * 3, 10);

        if (cat->cXP > 0) {
          if (enem->boss->hp > 0){
            painter.drawPixmap(enem->boss->x, enem->boss->y, 50, 50, enem->boss->gif->currentPixmap());
            painter.setBrush(QBrush(Qt::red ,Qt::SolidPattern));
            painter.drawRect(enem->boss->x, enem->boss->y - 5, (enem->boss->hp * 50 / enem->boss->HP), 5);
          }

          for (size_t i = 0; i < enem->en.size(); i++) {
            if (enem->en[i].hp > 0) {
                painter.drawPixmap(enem->en[i].x, enem->en[i].y, 40, 40, enem->en[i].gif->currentPixmap());
                painter.setBrush(QBrush(Qt::red ,Qt::SolidPattern));
                painter.drawRect(enem->en[i].x, enem->en[i].y - 5, (enem->en[i].hp * 40 / enem->en[i].HP), 5);
            }
          }
        }

        painter.drawPixmap(h->x, h->y, 50, 150, h->gif->currentPixmap());
        if (h->is_empt == 1)
            pix1 = QPixmap (":/res/img/empty_mis.png");
        if (h->is_empt == 0)
            pix1 = QPixmap (":/res/img/full_mis.png");
        painter.drawPixmap(h->bx, h->by, 50, 25, pix1);
        if(cat->mltimer->isActive())
            pix1 = QPixmap (":/res/img/cat1.png");
        else
            pix1 = QPixmap (":/res/img/cat2.png");
        painter.drawPixmap(cat->x, cat->y, 25, 25, pix1);
    }
    if(where == 0){
        QPixmap pix2(":/res/img/cat1.png");
        painter.drawPixmap(700, 500, 100, 100, pix2);
    }
    if(where == 2){
        QPixmap pix2(":/res/img/cat2.png");
        painter.drawPixmap(415, 365, 250, 100, pix2);
    }
    Q_UNUSED(event);
}

void Widget::generate_blocks(int array[37][60])
{
    for(int i = 0; i < 37; i++){
        for(int j = 0; j < 60; j++){
            if(array[i][j] == 1){
                b.setpos(j * 20 - 60, i * 20);
                blocks.push_back(b);
            }
            if(array[i][j] == 2){
                pl.setpos(j * 20 - 60, i * 20);
                platforms.push_back(pl);
            }
        }
    }
}

void Widget::generate_enem()
{
    for(int i = 0; i < 37; i++){
        for(int j = 0; j < 60; j++){
            if(lvl[i][j] == 3){
                e.set_all(j * 20, i * 20, 0, 1, 4, 0);
                enem->en.push_back(e);
            }
        }
    }

    enem->spawn();
}

void Widget::gameOver()
{
    on_esc_clicked();
    Button1->setGeometry(QRect(QPoint(0, 0), QSize(0, 0)));
    lable2->setGeometry(QRect(QPoint(500, 200), QSize(200, 50)));
    lable2->setText("Вы проиграли");
    Button2->setGeometry(QRect(QPoint(440, 450), QSize(200, 60)));
    Button2->setText("Вернуться в главное меню");
}

void Widget::ggwp()
{
    on_esc_clicked();
    Button1->setGeometry(QRect(QPoint(0, 0), QSize(0, 0)));
    lable2->setGeometry(QRect(QPoint(500, 200), QSize(200, 50)));
    lable2->setText("Вы выиграли");
    Button2->setGeometry(QRect(QPoint(440, 450), QSize(200, 60)));
    Button2->setText("Вернуться в главное меню");
}

void Widget::timers_stop()
{
   // cat->timer->stop(); // переместить в паблик
    cat->atacktimer->stop();
    cat->stopjump();
    cat->mltimer->stop();
    cat->mrtimer->stop();
    cat->gtimer->stop();
    enem->ahtimer->stop();
    enem->spawntimer->stop();
    h->glrtimer->stop();
    //val->valtimer->stop();
}

void Widget::timers_start()
{
  //  cat->timer->start(); // переместить в паблик
    cat->atacktimer->start(1000);
    cat->gtimer->start(40);

    enem->ahtimer->start(5000);
    enem->spawntimer->start(10000);
//    enem->boss->xtimer->start(80);
//    enem->boss->ytimer->start(100);
//    enem->boss->switchdirx->start(3000);
//    enem->boss->switchdiry->start(3500);

//    for(size_t i = 0; i < enem->en.size(); i++){
//        enem->en[i].golrtimer->start(40);
//        enem->en[i].swithdirtimer->start(rand() % 1000 + 2000);
//    }

    h->timer->start(500);
    h->glrtimer->start(40);
    val->valtimer->start(10 * 1000 * (2 + dificulty));
}

void Widget::opendor()
{
    if (enem->kK >= 3){
        blocks.clear();
        generate_blocks(lvl1);
    }
}

int p(int Px, int Py, int Ax, int Ay, int Bx, int By)
{
  return (Bx - Ax) * (Py - Ay) - (By - Ay) * (Px - Ax);
}

void Widget::colide_enem(){
    int j = 50; // мб покажется мало дистанции, можно увеличить
    for(size_t i = 0; i < enem->en.size(); i++){
        int a = p(enem->en[i].x, enem->en[i].y, cat->x - j, cat->y - j , cat->x + 20 + j, cat->y - j);
        int b = p(enem->en[i].x, enem->en[i].y, cat->x + 20 + j, cat->y - j , cat->x + 20 + j, cat->y + 20 + j);
        int c = p(enem->en[i].x, enem->en[i].y, cat->x + 20 + j, cat->y + 20 + j , cat->x - j, cat->y + 20 + j);
        int d = p(enem->en[i].x, enem->en[i].y, cat->x - j, cat->y + 20 + j , cat->x - j, cat->y - j);
        if (((a < 0 && b < 0 && c < 0 && d < 0) || (a > 0 && b > 0 && c > 0 && d > 0)) && enem->en[i].hp > 0){
//            if(cat->cXP > enem->en[i].damag)
//                cat->cXP -= enem->en[i].damag * 10;
//            else
//                cat->cXP = 0;
            if(cat->koh == 0){
                enem->en[i].hp -= 60 - dificulty * 5;
                if(cat->cXP > enem->en[i].damag)
                    cat->cXP -= enem->en[i].damag + dificulty * 10;
                else
                    cat->cXP = 0;
            }
            cat->koh += 1;
            cat->koh %= 25;
            if(enem->en[i].hp < 0){
                enem->en[i].die();
                enem->kK += 1;
            }
        }
    }
}

void Widget::colide_val(){
    int j = 20; // мб покажется мало дистанции, можно увеличить
    int a = p(val->x, val->y, cat->x - j, cat->y - j , cat->x + 20 + j, cat->y - j);
    int b = p(val->x, val->y, cat->x + 20 + j, cat->y - j , cat->x + 20 + j, cat->y + 20 + j);
    int c = p(val->x, val->y, cat->x + 20 + j, cat->y + 20 + j , cat->x - j, cat->y + 20 + j);
    int d = p(val->x, val->y, cat->x - j, cat->y + 20 + j , cat->x - j, cat->y - j);
    if (((a < 0 && b < 0 && c < 0 && d < 0) || (a > 0 && b > 0 && c > 0 && d > 0)) ){
        cat->fillXP();
        val->x = -300;
        val->valtimer->stop();
        val->valtimer->start(10 * 1000 * (2 + dificulty));
    }
}

void Widget::colide_bowl()
{
    int j = 150; // мб покажется мало дистанции, можно увеличить
    int a = p(h->bx, h->by, cat->x - j, cat->y , cat->x + 20, cat->y);
    int b = p(h->bx, h->by, cat->x + 20, cat->y, cat->x + 20, cat->y + 20);
    int c = p(h->bx, h->by, cat->x + 20, cat->y + 20 , cat->x - j, cat->y + 20);
    int d = p(h->bx, h->by, cat->x - j, cat->y + 20, cat->x - j, cat->y);
    if (((a < 0 && b < 0 && c < 0 && d < 0) || (a > 0 && b > 0 && c > 0 && d > 0)) && h->is_empt == 0 ){
        cat->fillcxp();
        h->is_empt = 1;
    }
}

void Widget::volide_human_enemy()
{
    int j = 50; // мб покажется мало дистанции, можно увеличить
    for(size_t i = 0; i < enem->en.size(); i++){
        int a = p(enem->en[i].x, enem->en[i].y, h->x - j, h->y - j , h->x + 50 + j, h->y - j);
        int b = p(enem->en[i].x, enem->en[i].y, h->x + 50 + j, h->y - j , h->x + 50 + j, h->y + 150 + j);
        int c = p(enem->en[i].x, enem->en[i].y, h->x + 50 + j, h->y + 150 + j , h->x - j, h->y + 150 + j);
        int d = p(enem->en[i].x, enem->en[i].y, h->x - j, h->y + 150 + j , h->x - j, h->y - j);
        if (((a < 0 && b < 0 && c < 0 && d < 0) || (a > 0 && b > 0 && c > 0 && d > 0)) && enem->en[i].hp > 0 && enem->en[i].is_checkble == 1 && h->is_scared()){
            if(!h->jtimer->isActive())
                h->jtimer->start(40);
            cat->hXP -= 50;
            enem->en[i].is_checkble = 0;
        }
    }
}

void Widget::colide_boss(){
    int j = 50; // мб покажется мало дистанции, можно увеличить
    int a = p(enem->boss->x, enem->boss->y, cat->x - j, cat->y - j , cat->x + 20 + j, cat->y - j);
    int b = p(enem->boss->x, enem->boss->y, cat->x + 20 + j, cat->y - j , cat->x + 20 + j, cat->y + 20 + j);
    int c = p(enem->boss->x, enem->boss->y, cat->x + 20 + j, cat->y + 20 + j , cat->x - j, cat->y + 20 + j);
    int d = p(enem->boss->x, enem->boss->y, cat->x - j, cat->y + 20 + j , cat->x - j, cat->y - j);
    if (((a < 0 && b < 0 && c < 0 && d < 0) || (a > 0 && b > 0 && c > 0 && d > 0)) ){
            enem->boss->hp -= 5 - dificulty;
            if (enem->boss->hp <= 0){
                enem->boss->is_alive = 0;
            }
            if(cat->cXP > enem->boss->damag)
                cat->cXP -= enem->boss->damag;
            else
                cat->cXP = 0;

    }
}

void  Widget::atack_H(){
    enem->calckHD();
    if(cat->hXP > enem->D * (dificulty + 1) * (0.25))
        cat->hXP -= enem->D * (dificulty + 1) * (0.25);
    else
        gameOver();
}

void Widget::is_vin()
{
    if(where == 1){
        int l = -1;
        if(enem->boss->hp <= 0 ){
            l = 0;
            for(size_t i = 0; i < enem->en.size(); i++){
                if(enem->en[i].hp > 0){
                    l++;
                }
            }
        }
        if(l == 0){
            ggwp();
        }
    }
}

void Widget::pauseSlot()
{
    if (timer->isActive())
    {
        timer->stop();
    }
    QDialog pause;
    pause.exec();
    timer->start(time);
}

