#ifndef COLOR_VIEW_HPP
#define COLOR_VIEW_HPP

#include <QWidget>
#include <QColor>

class color_view : public QWidget
{
    Q_OBJECT
public:
    explicit color_view(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void set_color(const QColor &color);
    QColor get_color();

private:
    QColor widget_color = QColor(255, 255, 255);

signals:

};

#endif // COLOR_VIEW_HPP
