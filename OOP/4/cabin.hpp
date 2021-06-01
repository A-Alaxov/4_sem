#ifndef CABIN_H
#define CABIN_H

#include <QObject>
#include <QTimer>
#include <doors.hpp>

#include "direction.hpp"

#define CROSS_FLOOR_TIME 3000

class cabin : public QObject
{
    Q_OBJECT

    enum cabin_state
    {
        STAY_CLOSED,
        START_MOVING,
        MOVE,
        STAY_NOT_CLOSED,
    };

public:
    explicit cabin(QObject *parent = nullptr);

signals:
    void cabin_called();
    void cabin_stopped();
    void cabin_crossed_floor(long, const direction &_direction);
    void cabin_stay_closed(long floor);

public slots:
    void move();
    void stay_not_closed();
    void stay_closed();
    void start_moving(long floor, const direction &dir);

private:
    long cur_floor = 1;
    direction cur_direction = STAY;
    doors _doors;
    cabin_state _state = STAY_CLOSED;
    QTimer cross_floor_timer;
};

#endif // CABIN_H
