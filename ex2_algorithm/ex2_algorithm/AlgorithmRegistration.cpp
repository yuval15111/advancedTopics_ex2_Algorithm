#include "AlgorithmRegistration.h"

//registers a new algorithm
AlgorithmRegistration::AlgorithmRegistration(std::function<std::unique_ptr<AbstractAlgorithm>()> factoryMethod)
{
	//MatchManager::getMatchManager().registerAlgorithm(factoryMethod);
}
