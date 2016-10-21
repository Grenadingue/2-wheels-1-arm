#include <QTime>
#include "GeneticAlgo.hpp"

#include <QDebug>

/*
** Generate a random number in the given range
*/
int randomNumberInRange(int min, int max)
{
    return min + ((int)qrand() % (max - min + 1));
}

/*
** Generate a string with random uppercase letters
*/
QString randomString(int size)
{
    QString str;

    str.resize(size);
    for (int i = 0; i != size; ++i)
        str[i] = QChar(randomNumberInRange(' ', '~'));
    return str;
}

GeneticAlgo::GeneticAlgo()
    : _referenceString("abcdzGa4cyrf7b f8 4**7-+we+f+ew6r5f+wf6hythr9+t5934~ t59h59+9sd;m;ldc ;aZG79QWbcdeK'wlkncwe[jnec[wo'eodw  q3289rhfcb"),
      _populationSize(400),
      _genocideSize(132), // 33 % of population
      _highestScore(0)
{
    qDebug() << Q_FUNC_INFO;
}

GeneticAlgo::~GeneticAlgo()
{
    qDebug() << Q_FUNC_INFO;
}

void GeneticAlgo::_initPopulation()
{
    qsrand((uint)QTime::currentTime().msec());
    for (int i = 0; i != _populationSize; ++i)
        _population.push_back(randomString(_referenceString.size()));
}

/*
** Criteres de selection:
** - nombre de bonnes lettres au bon endroit
** - nombre de bonnes lettres a la suite
**   - nombre total de lettres a la suite (si serie de plus de 1)
**   - nombre de max de lettres a la suite dans un mot
*/
int GeneticAlgo::_rateIndividual(const QString &individual) const
{
    int nbRightLetters = 0,
            currentMaxValidLettersAligned = 0,
            maxValidLettersAligned = 0,
            totalValidLettersAligned = 0;

    for (int i = 0; i != _referenceString.size(); ++i)
        if (_referenceString[i] == individual[i])
            ++nbRightLetters;

    for (int i = 0; i != _referenceString.size(); ++i)
    {
        if (_referenceString[i] == individual[i])
            ++currentMaxValidLettersAligned;
        else
        {
            if (currentMaxValidLettersAligned > 1)
                totalValidLettersAligned += currentMaxValidLettersAligned;
            if (currentMaxValidLettersAligned > maxValidLettersAligned)
                maxValidLettersAligned = currentMaxValidLettersAligned;
            currentMaxValidLettersAligned = 0;
        }
    }
    if (currentMaxValidLettersAligned > 1)
        totalValidLettersAligned += currentMaxValidLettersAligned;
    if (currentMaxValidLettersAligned > maxValidLettersAligned)
        maxValidLettersAligned = currentMaxValidLettersAligned;

    return nbRightLetters + maxValidLettersAligned + totalValidLettersAligned;
}

int GeneticAlgo::_getTheoreticalMaximumRate() const
{
    return _rateIndividual(_referenceString);
}

void GeneticAlgo::_sortPopulationByScore(const QMap<QString, int> &individualsScore)
{
    QList<QString> rankedPopulation;
    int bestScore = 0;

    for (auto individual : individualsScore.toStdMap())
        bestScore = individual.second > bestScore ? individual.second : bestScore;

    qDebug() << "Best score:" << bestScore;
    _highestScore = bestScore;

    while (bestScore >= 0)
    {
        for (auto individual : individualsScore.toStdMap())
        {
            if (individual.second == bestScore)
                rankedPopulation.push_back(individual.first);
        }
        --bestScore;
    }
    _population = rankedPopulation;
}

void GeneticAlgo::_genocide()
{
    while (_population.size() != (_populationSize - _genocideSize))
        _population.pop_back();
}

/*
** Attribuer une note a chaque individu en fonction des criteres de selection
** Attribuer un rang a chaque individu en fonction de sa note
** Exterminer `g_GENOCIDE_SIZE` individus
*/
void GeneticAlgo::_selectIndividualsForMating()
{
    QMap<QString, int> individualsScore;

    for (QString individual : _population)
        individualsScore[individual] = _rateIndividual(individual);

    _sortPopulationByScore(individualsScore);
    _genocide();
}

QString GeneticAlgo::_produceChildFromParents(const QString &parent1, const QString &parent2) const
{
    QList<QString> allGenes;
    QString child;

    const int nbGenes = 2;
    int min = 0, max = nbGenes - 1;
    for (int i = 0; i != _referenceString.size(); i += nbGenes)
    {
        allGenes.push_back(parent1.mid(i, nbGenes));
        allGenes.push_back(parent2.mid(i, nbGenes));
        child.append(allGenes[randomNumberInRange(min, max)]);
        min += nbGenes;
        max += nbGenes;
    }
    return child;
}

/*
** It's sex time
*/
void GeneticAlgo::_mateIndividualsToProduceOffspring()
{
    for (int i = 0; i != _genocideSize; ++i)
    {
        QString parent1 = _population[randomNumberInRange(0, _populationSize - _genocideSize - 1)],
                parent2 = _population[randomNumberInRange(0, _populationSize - _genocideSize - 1)],
                child;

        child = _produceChildFromParents(parent1, parent2);
        _offspring.push_back(child);
    }
}

/*
** Uranium
*/
void GeneticAlgo::_mutateOffspring()
{
    for (int i = 0; i != 4; ++i)
        _offspring[randomNumberInRange(0, _genocideSize - 1)][randomNumberInRange(0, _referenceString.size() - 1)] = QChar(randomNumberInRange(' ', '~'));
}

void GeneticAlgo::_insertOffspringIntoPopulation()
{
    _population << _offspring;
    _offspring.clear();
}

bool GeneticAlgo::_resultFound(unsigned long int i)
{
    for (auto individual : _population)
        if (individual == _referenceString)
        {
            _highestScore = _rateIndividual(individual);
            emit updateHighestScore(i, _highestScore);
            qDebug() << "Final (max) score:" << _highestScore << "Solution =" << individual;
            return true;
        }
    return false;
}

void GeneticAlgo::doWork()
{
    unsigned long int i = 0;

    qDebug() << Q_FUNC_INFO;

    emit updateHighestScore(0, 0);
    _initPopulation();

    qDebug() << "Reference string:" << _referenceString << "| Size:" << _referenceString.size() << "\n";
    qDebug() << "Initial population:" << _population << "\n";

    while (!_resultFound(i))
    {
        _highestScore = 0;

        _selectIndividualsForMating();
        _mateIndividualsToProduceOffspring();
        _mutateOffspring();
        _insertOffspringIntoPopulation();

        emit updateHighestScore(i, _highestScore);
        qDebug() << "iteration i =" << i << "Best solution =" << _population[0];
        ++i;
    }
    emit updateHighestScore(i, _highestScore);
}
