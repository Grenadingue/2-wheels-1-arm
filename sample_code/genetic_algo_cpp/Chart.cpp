#include "Chart.hpp"

#include <QDebug>

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(parent, wFlags),
    _window(new QMainWindow),
    _chartView(new QChartView(this)),
    _series(this),
    _x(0),
    _y(0)
{
    QPen pen(Qt::red);

    qDebug() << Q_FUNC_INFO;

    pen.setWidth(2);
    _series.setPen(pen);

    // Set serie's name
    _series.setName("Best individual score");

    // Set x axis legend
    _axisX.setTitleText("x = number of iterations");
    _axisX.setTitleVisible(true);

    // Set y axis legend
    _axisY.setTitleText("y = individual score");
    _axisY.setTitleVisible(true);

    // Init serie with axis
    addSeries(&_series);
    setAxisX(&_axisX, &_series);
    setAxisY(&_axisY, &_series);

    // Init first (x, y) point
    _series.append(_x, _y);
}

Chart::~Chart()
{
}

void Chart::initWindow()
{
    qDebug() << Q_FUNC_INFO;

    _chartView->setRenderHint(QPainter::Antialiasing);
    setTitle("Genetic algorithm string finder");
    _window->setCentralWidget(_chartView);
    _window->resize(800, 600);
    _window->show();
}

void Chart::updateHighestScore(int iteration, int highestScore)
{
    qDebug() << Q_FUNC_INFO << iteration << highestScore;

    _x = iteration;
    _y = highestScore;
    axisX()->setRange(0, _x + 10);
    axisY()->setRange(0, _y + 10);
    _series.append(_x, _y);
}
