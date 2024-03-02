#include "MapView.h"

#include "Window_SectorMap.h"

#include "Hexagon.h"
#include "SectorRectangle.h"

#include "Globals.h"

#include <QMouseEvent>
#include <QWheelEvent>

#include <QGraphicsItem>
#include <QScrollBar>

MapView::MapView(){
}

MapView::MapView(QWidget *parent) : QGraphicsView{parent}{
    connect(this->horizontalScrollBar(), &QScrollBar::valueChanged, this, &MapView::viewMoved);
    connect(this->verticalScrollBar(), &QScrollBar::valueChanged, this, &MapView::viewMoved);

    this->scale(this->zoomFactor, this->zoomFactor);
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
    if(delta.y()>0 && zoomFactor<maximumZoom){
        this->zoomFactor *= this->zoomStep;
        this->scale(this->zoomStep, this->zoomStep);
    }
    else if (delta.y()<0 && zoomFactor>minimumZoom) {
        this->zoomFactor /= this->zoomStep;
        this->scale(1/this->zoomStep, 1/this->zoomStep);
    }

    /*-----------------------------------------------*
     *   UPDATE DETAILS SHOWN BASED ON ZOOM FACTOR   *
     *-----------------------------------------------*/
    QList<QGraphicsItem*> at = this->scene()->items();

    // When zooming in
    if(zoomFactor > previousFactor){
        if(zoomFactor > 0.9){
            if(zoomLevel != 0){
                for(QGraphicsItem* it: at){
                    if(it!=nullptr && dynamic_cast<Hexagon*>(it)!=nullptr){
                        dynamic_cast<Hexagon*>(it)->showFullInfo();
                    }
                }
            }
            zoomLevel = 0;
            this->hideHexes = false;
        }
        else if(zoomFactor > 0.2){
            if(zoomLevel !=1){
                for(QGraphicsItem* it: at){
                    if(it!=nullptr && dynamic_cast<Hexagon*>(it)!=nullptr){
                        dynamic_cast<Hexagon*>(it)->show();
                        dynamic_cast<Hexagon*>(it)->showLimitedInfo();
                    }
                    // Hide SubSector and Sector text
                    if(dynamic_cast<SectorRectangle*>(it)!=nullptr){
                        (dynamic_cast<SectorRectangle*>(it))->hideText();
                    }
                }
            }
            zoomLevel = 1;
            this->hideHexes = false;
        }
        else if(zoomFactor > 0.1){
            if(zoomLevel !=2){
                for(QGraphicsItem* it: at){
                    // Hide Sector text
                    if(dynamic_cast<SectorRectangle*>(it)!=nullptr && !(dynamic_cast<SectorRectangle*>(it))->isSubsector()){
                        (dynamic_cast<SectorRectangle*>(it))->hideText();
                        QPen pen = (dynamic_cast<SectorRectangle*>(it))->pen();
                        pen.setWidth(pen.width()/4);
                        (dynamic_cast<SectorRectangle*>(it))->setPen(pen);
                    }
                }
            }
            zoomLevel = 2;
        }
        else if(zoomFactor > 0.05){
            if(zoomLevel != 3){
                for(QGraphicsItem* it: at){
                    // Show SubSector text
                    if(dynamic_cast<SectorRectangle*>(it)!=nullptr && (dynamic_cast<SectorRectangle*>(it))->isSubsector()){
                        (dynamic_cast<SectorRectangle*>(it))->showText();
                    }
                }
            }
            zoomLevel = 3;
        }
    }
    // When zooming out
    else if(zoomFactor < previousFactor){
        if(zoomFactor < 0.05){
            if(zoomLevel != 4){
                for(QGraphicsItem* it: at){
                    // Hide SubSector text
                    if(dynamic_cast<SectorRectangle*>(it)!=nullptr && (dynamic_cast<SectorRectangle*>(it))->isSubsector()){
                        (dynamic_cast<SectorRectangle*>(it))->hideText();
                    }
                }
            }
            zoomLevel = 4;
            this->hideHexes = true;
        }
        else if(zoomFactor < 0.1){
            if(zoomLevel != 3){
                for(QGraphicsItem* it: at){
                    // Show Sector text
                    if(dynamic_cast<SectorRectangle*>(it)!=nullptr && !(dynamic_cast<SectorRectangle*>(it))->isSubsector()){
                        (dynamic_cast<SectorRectangle*>(it))->showText();
                        QPen pen = (dynamic_cast<SectorRectangle*>(it))->pen();
                        pen.setWidth(pen.width()*4);
                        (dynamic_cast<SectorRectangle*>(it))->setPen(pen);
                    }
                }
            }
            zoomLevel = 3;
            this->hideHexes = true;
        }
        else if(zoomFactor < 0.2){
            if(zoomLevel != 2){
                for(QGraphicsItem* it: at){
                    if(it!=nullptr && dynamic_cast<Hexagon*>(it)!=nullptr){
                        dynamic_cast<Hexagon*>(it)->hide();
                    }

                    // Show SubSector text
                    if(dynamic_cast<SectorRectangle*>(it)!=nullptr && (dynamic_cast<SectorRectangle*>(it))->isSubsector()){
                        (dynamic_cast<SectorRectangle*>(it))->showText();
                    }
                }
            }
            zoomLevel = 2;
            this->hideHexes = true;
        }
        else if(zoomFactor < 0.9){
            if(zoomLevel != 1){
                for(QGraphicsItem* it: at){
                    if(it!=nullptr && dynamic_cast<Hexagon*>(it)!=nullptr){
                        dynamic_cast<Hexagon*>(it)->showLimitedInfo();
                    }
                }
            }
            zoomLevel = 1;
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

void MapView::viewMoved() {
    if(!this->hideHexes){
        QPointF topLeft = this->mapToScene(QPoint(0,0));
        QPointF bottomRight = this->mapToScene(QPoint(this->width(), this->height()));
        this->window->updateViewPosition(topLeft, bottomRight);
    }
}
