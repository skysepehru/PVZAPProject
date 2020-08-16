#ifndef PLANTPREVIEW_H
#define PLANTPREVIEW_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QString>
#include <QMouseEvent>

class PlantPreview : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    QString plant;
public:
    explicit PlantPreview(QString plant, QTimer* timer , QGraphicsItem *parent = nullptr);
    QString getPlant();
signals:

public slots:
    void update();
    void mouseLeftClicked();
};

#endif // PLANTPREVIEW_H
