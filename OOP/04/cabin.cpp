#include <QDebug>
#include "cabin.hpp"

cabin::cabin(QObject *parent) : QObject(parent)
{
    cross_floor_timer.setSingleShot(true);

    QObject::connect(&_doors, SIGNAL(doors_closed()), this, SLOT(stay_closed()));
    QObject::connect(this, SIGNAL(cabin_stopped()), &_doors, SLOT(start_opening()));
    QObject::connect(&cross_floor_timer, SIGNAL(timeout()), this, SLOT(move()));
    QObject::connect(this, SIGNAL(cabin_called()), this, SLOT(move()));
}

void cabin::move()
{
    if (_state != START_MOVING && _state != MOVE)
        return;

    if (_state == MOVE)
        cur_floor += cur_direction;

    _state = MOVE;
    emit cabin_crossed_floor(cur_floor, cur_direction);
    cross_floor_timer.start(CROSS_FLOOR_TIME);
}

void cabin::stay_not_closed()
{
    if (_state != MOVE && _state != STAY_NOT_CLOSED)
        return;

    if (_state == MOVE)
        qDebug() << "Cabin stopped at floor № " << cur_floor;

    _state = STAY_NOT_CLOSED;
    emit cabin_stopped();
}

void cabin::stay_closed()
{
    if (_state != STAY_NOT_CLOSED)
        return;

    _state = STAY_CLOSED;
    qDebug() << "Cabin waiting";

    emit cabin_stay_closed(cur_floor);
}

void cabin::start_moving(long floor, const direction &dir)
{
    if (_state != STAY_CLOSED)
        return;

    _state = START_MOVING;
    cur_direction = dir;

    emit cabin_called();
}
