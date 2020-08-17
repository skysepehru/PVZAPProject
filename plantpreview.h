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
    //it is called from View whenever the left mouse button is clicked. used for deselecting a selected plant
    //IF the mouse is not clicked on plant slots.(if the mouse is clicked on a plant slot and it doesn't get planted,
    //the plant will not be unselected.
    void mouseLeftClicked();
};

#endif // PLANTPREVIEW_H
