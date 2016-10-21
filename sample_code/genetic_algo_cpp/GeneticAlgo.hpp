#ifndef     GENETIC_ALGO_HPP_
# define    GENETIC_ALGO_HPP_

# include <QObject>
# include <QList>
# include <QString>

class GeneticAlgo : public QObject
{
    Q_OBJECT

private:
    const QString _referenceString;
    const int _populationSize;
    const int _genocideSize;

    QList<QString> _population;
    QList<QString> _offspring;

    int _highestScore;

public:
    GeneticAlgo();
    ~GeneticAlgo();

private:
    void _initPopulation();
    int _rateIndividual(const QString &individual) const;
    int _getTheoreticalMaximumRate() const;
    void _sortPopulationByScore(const QMap<QString, int> &individualsScore);
    void _genocide();
    void _selectIndividualsForMating();
    QString _produceChildFromParents(const QString &parent1, const QString &parent2) const;
    void _mateIndividualsToProduceOffspring();
    void _mutateOffspring();
    void _insertOffspringIntoPopulation();
    bool _resultFound(unsigned long int i);

public slots:
    void doWork();

signals:
    void updateHighestScore(int iteration, int highestScore);
};

#endif      // !GENETIC_ALGO_HPP_
