#ifndef DELETEELEMENTSWORKER_H
#define DELETEELEMENTSWORKER_H

#include <QObject>

class Sector;

class DeleteElementsWorker : public QObject {
    Q_OBJECT
public:
    explicit DeleteElementsWorker(QObject *parent = nullptr);

public slots:
    void doWork(const QPoint coordinates[], const float zoomFactor, const std::vector<Sector*> sectors);

signals:
    void workDone();
};

#endif // DELETEELEMENTSWORKER_H
