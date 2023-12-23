#include "MapView.h"

#include "Window_SectorMap.h"

#include "Hexagon.h"

#include "Globals.h"

#include <QMouseEvent>
#include <QWheelEvent>

#include <QGraphicsItem>

MapView::MapView(){
}

MapView::MapView(QWidget *parent) : QGraphicsView{parent}{
}

void MapView::setWindow(Window_SectorMap *w){
    this->window = w;
}

void MapView::mousePressEvent(QMouseEvent *event){
    QPointF scenePosition = this->mapToScene(event->pos());

    QList<QGraphicsItem*> itemsAtPosition = this->scene()->items(scenePosition);

    QGraphicsRectItem rectangleItem(QRectF(scenePosition, scenePosition+QPointF(1, 1)));
    for(QGraphicsItem *item: itemsAtPosition){
        if(item->collidesWithItem(&rectangleItem)){
            Hexagon *hexagonCast = dynamic_cast<Hexagon*>(item);

            if(hexagonCast != nullptr){
                std::string systemName = hexagonCast->getName();
                this->window->setSystemMapButtonDisabled(!this->findSystem(systemName));
                this->window->setDetails(hexagonCast);
                break;
            }
        }
    }

}

void MapView::wheelEvent(QWheelEvent *event){
    /*----------------------------*
     *   UPDATE THE ZOOM FACTOR   *
     *----------------------------*/
    QPoint delta = event->angleDelta()/8;
    float previousFactor = zoomFactor;
    if(delta.y()>0){
        zoomFactor *= 1.5;
        this->scale(1.5, 1.5);
    }
    else {
        zoomFactor *= 1/1.5;
        this->scale(1/1.5,1/1.5);
    }

    /*-----------------------------------------------*
     *   UPDATE DETAILS SHOWN BASED ON ZOOM FACTOR   *
     *-----------------------------------------------*/
    // When zooming in
    if(zoomFactor > previousFactor){
        if(zoomFactor==2/10){
            //showSystemDetails();
        }
        else if(zoomFactor==1/10){
            //hideSubsectors();
            //showLimitedSystems();
        }
        else if(zoomFactor==1/20){
            //HideSectors();
        }
        else if(zoomFactor==1/30){
            //ShowSubsectors();
        }
    }
    // When zooming out
    else if(zoomFactor < previousFactor){
        if(zoomFactor==1/10){
            //hideSystemDetails();
        }
        else if(zoomFactor==1/20){
            //HideSystems();
            //ShowSubsectors();
        }
        else if(zoomFactor==1/30){
            //ShowSectors();
        }
    }


    if(zoomFactor < 0.4 && previousFactor>=0.4){
        QList<QGraphicsItem*> at = this->scene()->items();
        for(QGraphicsItem* it: at){
            QGraphicsTextItem *t = dynamic_cast<QGraphicsTextItem*>(it);
            if(t!=nullptr && dynamic_cast<Hexagon*>(it->parentItem())!=nullptr){
                QFont font;
                font.setPointSize(30);

                float oldWidth = t->boundingRect().width();
                t->setFont(font);
                float newWidth = t->boundingRect().width();

                QTransform oldTransform = t->transform();
                oldTransform.translate(oldWidth/2 - newWidth/2, -10);
                t->setTransform(oldTransform);
            }
        }
    }
    if(zoomFactor >= 0.4 && previousFactor<0.4) {
        QList<QGraphicsItem*> at = this->scene()->items();
        for(QGraphicsItem* it: at){
            QGraphicsTextItem *t = dynamic_cast<QGraphicsTextItem*>(it);
            if(t!=nullptr && dynamic_cast<Hexagon*>(it->parentItem())!=nullptr){
                QFont font;
                font.setPointSize(20);

                float oldWidth = t->boundingRect().width();
                t->setFont(font);
                float newWidth = t->boundingRect().width();

                QTransform oldTransform = t->transform();
                oldTransform.translate(oldWidth/2 - newWidth/2, 10);
                t->setTransform(oldTransform);
            }
        }
    }

    if(zoomFactor < 0.2 && !hideHexes){
        hideHexes = true;
        // Hide Hexes and show Sector Names
        QList<QGraphicsItem*> at = this->scene()->items();
        for(QGraphicsItem* it: at){
            if(dynamic_cast<Hexagon*>(it)!=nullptr) it->hide();
            if(dynamic_cast<QGraphicsTextItem*>(it)!=nullptr && dynamic_cast<Hexagon*>(it->parentItem())==nullptr) it->setVisible(true);
        }
    }
    if(zoomFactor > 0.2 && hideHexes){
        hideHexes = false;
        // Show Hexes and hide Sector Names
        QList<QGraphicsItem*> at = this->scene()->items();
        for(QGraphicsItem* it: at){
            if(dynamic_cast<Hexagon*>(it)!=nullptr) it->setVisible(true);
            if(dynamic_cast<QGraphicsTextItem*>(it)!=nullptr && dynamic_cast<Hexagon*>(it->parentItem())==nullptr) it->hide();
        }
    }
}

void MapView::initialize(){

}

bool MapView::findSystem(std::string name){
    std::vector<std::string> systemNames = global::getAllJSONFiles(global::path() + "Systems");

    for(std::string s: systemNames){
        if(s.compare(name)==0) return true;
    }
    return false;
}
