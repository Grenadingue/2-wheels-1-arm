# Algorithm pseudo code

## Generic genetic algorithm
### English
1. __[Start]__ Generate random population of n chromosomes (suitable solutions for the problem)
2. __[Fitness]__ Evaluate the fitness f(x) of each chromosome x in the population
3. __[New population]__ Create a new population by repeating following steps until the new population is complete
  1. __[Selection]__ Select two parent chromosomes from a population according to their fitness (the better fitness, the bigger chance to be selected)
  2. __[Crossover]__ With a crossover probability cross over the parents to form a new offspring (children). If no crossover was performed, offspring is an exact copy of parents.
  3. __[Mutation]__ With a mutation probability mutate new offspring at each locus (position in chromosome).
  4. __[Accepting]__ Place new offspring in a new population
4. __[Harsh life]__ Kill a part of the population, we do not need it to grow too much
5. __[Test]__ If the end condition is satisfied, stop, and return the best solution in current population
6. __[Loop]__ Go to step 2

### Object oriented (js style)
```js
class GeneticAlgorithm {
  var population;
  var fitness;
  var params;

  function algorithm(params) { // algorithm launcher
    params = params;
    population = initPopulation(); // generate random population
    while (!solutionFound(population, fitness)) { // loop while solution is not found
      var fitness = evaluateFitness(population); // evaluate the fitness, give a mark to an individual, from its genome's potential
      generateOffspring(population, fitness); // generate children from population
      harshLife(population, fitness); // kill a part of the population, we do not need it to grow too much
    }
    return population.bestSolution(); // return solution
  }

  function generateOffspring(population, fitness) {
    var children;
    for (n times) {
      var parents = selectParents(population, fitness);
      var child = itsSexTime(parents); // generate child from parents genome
      mutateChildGenome(child); // apply a probability function to determine if some genes will mutate 
      children += child;
    }
    insertChildrenInPopulation(children, population); // insert new individuals
  }
}
```

## String finder algorithm
A more detailed algorithm describing the string finder [sample code](../sample_code/genetic_algo_cpp/GeneticAlgo.cpp)

```js
class GeneticAlgorithm {
  var population;
  var fitness;
  var params;

  function initPopulation() {
    for (params.populationSize times) {
      var individual;
      for (params.stringToFind.length times) {
        var character = random.numberInRange<char>('!', '~'); // first and last ascii printable characters
        individual.genome += character; // the genome of an individual is literally a string
      }
      population += individual;
    }
    return population;
  }

  function algorithm(params) { // algorithm launcher
    params = params;
    population = initPopulation(); // generate random population
    while (!solutionFound(population)) { // loop while solution is not found
      var fitness = evaluateFitness(population); // evaluate the fitness, give a mark to an individual, from its genome's potential
      harshLife(population, fitness); // kill a part of the population, we do not need it to grow too much
      // killing individuals before reproduction is very elitist 
      generateOffspring(population); // generate children from curated population
    }
    return population.bestSolution(); // return solution
  }

  function solutionFound(population) {
    for each (individual in population) {
      if (individual.genome == params.stringToFind) { // the genome of an individual is literally a string
        return true; // result found
      }
    }
    return false; // result not found
  }

  function evaluateFitness(population) {
    for each (individual in population) {
      fitness[individual] = rateIndividual(individual);
    }
    population = sortPopulationByScoreDesc(population, fitness) // Better scores first
  }

  function rateIndividual(individual) {
    var score;
    score = addOnePointForEachCharacterAtTheRightPlace(individual, params.stringToFind);
    score += addNPointsForEachSerieOfNValidCharacters(individual, params.stringToFind); // a serie is valid if >= 2 characters
    score += reAddNPointsForTheLongestSerieOfNValidCharacters(individual, params.stringToFind);
    return score;
  }

  function harshLife(population) { // kill the last `params.populationRenewal` percents of the population
    var numberOfSentencedToDeath = params.populationRenewal / 100 * population.size;
    for (numberOfSentencedToDeath times) {
      population.removeLast(); // population is ordered with better scores first
    }
  }

  function generateOffspring(population) {
    var numberOfNeededChildren = params.populationRenewal / 100 * population.size;
    var children;
    for (numberOfNeededChildren times) {
      var parents = selectParents(population); // pick fully random parents from population
      var child = itsSexTime(parents); // generate child from parents genome
      mutateGenome(child); // apply a probability function to determine if some genes will mutate 
      children += child;
    }
    insertChildrenInPopulation(children, population); // insert new individuals
  }

  function selectParents(population) {
    var parents;
    parents.mom = population[random.numberInRange<int>(0, population.size - 1)];
    parents.dad = population[random.numberInRange<int>(0, population.size - 1)];
    return parents;
  }

  function itsSexTime(parents) {
    var child;
    for (var i = 0; i != parents.mom.genome.size; ++i) {
      var possibleGenes;
      possibleGenes[0] = parents.mom.genome[i]; // so a character
      possibleGenes[1] = parents.dad.genome[i];
      child.genome += possibleGenes[random.numberInRange(0, 1)];
    }
    return child;
  }

  function mutateGenome(child) {
    var currentProbabilty = random.numberInRange<int>(0, 100);
    var mutationProbabilty = params.mutationRate * 100;
    if (mutationProbability > currentProbability) { // test mutation rate probability in reality
      child.genome[random.numberInRange<int>(0, child.genome.length - 1)] = random.numberInRange<char>('!', '~');
    }
  }

  function insertChildrenInPopulation(children, population) {
    population += children;
  }
}
```

## 2w1a algorithm
### Goal
The goal of the algorithm is to find a solution to __move straightforward__ the 2w1a robot, __inside a 3D environment__.

> 2w1a robot will be the representation of an individual inside the virtual environment

### Genome construction
#### 2w1a moving capabilities
2w1a has three *articulations*, a *wrist*, an *elbow* and a *shoulder*. Each *articulation* can be controlled independantly with a motor. To control a motor, we need to indicate a value in degrees, inside the range `[0, 300]`. Lets call the event of controlling an *articulation*, an *articulation instruction*.

Lets now call a *step* a combination of one *articulation instruction* sent simultanously to each *articulation*.

#### Needed data to move
As a human has two symetrical legs, it needs two symetrical *steps* to control its legs, and finaly move itself in a direction. The succession of this two steps is a *cycle*. A human repeat this *cycle* while it wants to move.

As 2w1a has only one arm (its equivalent of the human leg), we could be tempted to consider that only one *step* would be needed to move. But if we would use only one *step*, this one always containing the same *articulation instructions* values, the robot would move one time, from its initial position, to the desired one, and then would never move again.

> Lets imagine the first step being "put the arm in the air", and the second "pull the floor with the arm".

So, to make a *cycle* we need at least two different *steps*. For simpleness we will consider two *steps* enough for our needs.

#### Data encoding
As we need to encode two *steps*, a *step* beeing three *articulation instructions*, and an *articulation instruction* being a value in the range `[0, 300]`. We need to encode the genome in a list of set of three values.

Something like
```c++
class Genome {
  struct gene_t {
    float wrist;
    float elbow;
    float shoulder;
  }

  std::list<gene_t> genes;
  
  Genome() : genes({ { 42.0001, 0.0, 284.165156 }, { 84.4645, 300.0, 10.1010 } }) {
    int i = 0;
    for (gene_t gene : genes) {
      std::cout << "Step " << i++ << std::endl
        << "\t" << "Wrist value: " << gene.wrist << std::endl
        << "\t" << "Elbow value: " << gene.elbow << std::endl
        << "\t" << "Shoulder value: " << gene.shoulder << std::endl;
    }
  }
}
```
