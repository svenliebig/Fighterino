#include "startmenu.h"
#include "ui_startmenu.h"

#include <QDebug>

StartMenu::StartMenu(QWidget *parent) : QWidget(parent), ui(new Ui::StartMenu)
{
    this->parent = parent;
    countAnimation = 0;
    timerUpdate = new QTimer(this);
    connect(timerUpdate, SIGNAL(timeout()), this, SLOT(update()));
    timerUpdate->start(20);

    ui->setupUi(this);
    animation = new QPropertyAnimation(this, "ptitle");
    animation->setStartValue(QRect(250, -125, 300, 100));
    animation->setEndValue(QRect(250, 100, 300, 100));

    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->setDuration(1000);
    QSound::play(":/welcome.wav");
}

StartMenu::~StartMenu()
{
    delete ui;
}

void StartMenu::Anim() {
    animation->start();
}

void StartMenu::paintEvent(QPaintEvent *e) {
    QPainter *painter = new QPainter(this);
    QBrush brush(Qt::yellow, Qt::DiagCrossPattern);
    painter->setBrush(Qt::red);
    painter->setPen(Qt::green);
    painter->setFont(QFont("Arial", 60, -1, false));
    painter->setBrush(brush);
    painter->setPen(Qt::NoPen);
    painter->drawRect(title);
    painter->setPen(Qt::cyan);
    painter->drawText(title, "Überschrift", QTextOption(Qt::AlignCenter));

    countAnimation++;
    if (countAnimation == 100) {
        animation->start();
    } else if (countAnimation < 100) {
        painter->drawText(QRect(250,100,300,100), "" + QString::number(100 - countAnimation), QTextOption(Qt::AlignCenter));
    }
}

void StartMenu::on_pushButton_3_clicked()
{
    parent->close();
}

void StartMenu::on_pushButton_clicked()
{
    emit setCurrent(3);
}

void StartMenu::on_pushButton_5_clicked()
{
    emit setCurrent(3);
}
