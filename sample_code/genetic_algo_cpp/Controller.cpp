#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include "Controller.hpp"

#include <QDebug>

Controller::Controller()
    : _worker(new GeneticAlgo)
{
    qDebug() << Q_FUNC_INFO;

    _worker->moveToThread(&_workerThread);

    connect(this, &Controller::startAlgo, _worker, &GeneticAlgo::doWork);
    connect(_worker, &GeneticAlgo::updateHighestScore, &_view, &Chart::updateHighestScore);
    connect(&_workerThread, &QThread::finished, _worker, &QObject::deleteLater);
}

Controller::~Controller()
{
    qDebug() << Q_FUNC_INFO;

    _workerThread.quit();
    _workerThread.wait();
}

void Controller::start()
{
    qDebug() << Q_FUNC_INFO;

    _view.initWindow();
    _workerThread.start();
    emit startAlgo();
}
