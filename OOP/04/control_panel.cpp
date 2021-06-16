#include <QDebug>
#include "control_panel.hpp"

control_panel::control_panel(QObject *parent) : QObject(parent)
{
    for (size_t i = 0; i < 5; i++)
    {
        is_target.push_back(false);
    }

    QObject::connect(this, SIGNAL(panel_new_target(long,direction)), this, SLOT(busy(long,direction)));
}

void control_panel::new_target(long floor)
{
    qDebug() << "Get new target: floor №: " << floor;
    is_target[floor - 1] = true;

    next_target();
}

void control_panel::next_target()
{
    if (is_target[current_floor - 1])
    {
        emit panel_new_target(current_floor, STAY);
    }
    else if (state == FREE)
    {
        for (size_t i = 0; i < is_target.size(); i++)
            if (is_target[i])
            {
                if (i + 1 > current_floor)
                    emit panel_new_target(i + 1, UP);
                else
                    emit panel_new_target(i + 1, DOWN);
                break;
            }
    }
}

void control_panel::busy(long floor, const direction &_direction)
{
    if (state == FREE)
    {
        state = BUSY;
        current_target = floor;
        current_direction = _direction;
    }
    else if (state == BUSY)
    {
        current_floor = floor;
        if (is_target[floor - 1])
        {
            is_target[floor - 1] = false;
            emit cabin_achieved_target();
        }
        else
            qDebug() << "Passed floor № " << floor;
    }
}

void control_panel::free(long floor)
{
    state = FREE;
    current_floor = floor;
    next_target();
}
