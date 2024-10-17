#include "DeleteElementsWorker.h"
#include "Data/Sector.h"

#include <QPoint>

DeleteElementsWorker::DeleteElementsWorker(QObject *parent): QObject{parent}{

}

void DeleteElementsWorker::doWork(const QPoint coordinates[], const float zoomFactor, const std::vector<Sector*> sectors){
    /*----------------------------------------------------------------------------------*
     *   CHECK WHICH SECTORS ARE WITHIN THE VIEWPORT BOUNDARIES AND "DELETE" THE REST   *
     *----------------------------------------------------------------------------------*/
    // GET SECTOR COORDINATES
    int topLeftX = coordinates[0].x();
    int topLeftY = coordinates[0].y();
    int bottomRightX = coordinates[1].x();
    int bottomRightY = coordinates[1].y();

    for(Sector *s: sectors){
        // "DELETE" ALL SECTORS NOT IN THE VIEWPORT
        if(!s->getHidden() && (s->getX()>bottomRightX || s->getX()<topLeftX || s->getY()>bottomRightY || s->getY()<topLeftY) ){
            s->setHidden(true);
        }
    }

    /*-----------------------------------------------------------------------------*
     *   TODO: CHECK THE ZOOM FACTOR AND DECIDES WITH VERSION OF THE MAP TO SHOW   *
     *-----------------------------------------------------------------------------*/
    // DEPENDING ON CURRENT VALUE OF ZOOM FACTOR, CHOOSE WHICH ELEMENTS TO SHOW
    if(zoomFactor > 0.2){
        //---> zoom super close => show system details
    }
    else if (zoomFactor > 0.4) {
        //---> zoom close => show systems and subsector grid
    }
    else if (zoomFactor > 0.6) {
        //---> zoom mid => show subsector details
    }
    else if (zoomFactor > 0.8) {
        //---> zoom far => show subsector names
    }
    else {
        //---> zoom super far => show sectors only
    }

    /*-----------------------------------------------------*
     *    EMIT SIGNAL TO MAIN THREAD TO SAY WORK IS DONE   *
     *-----------------------------------------------------*/
    emit workDone();
}
