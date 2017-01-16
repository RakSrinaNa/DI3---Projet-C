#include "headers/metaheuristicGeneticUnit.h"
#include "../headers/metaheuristicGenetic.h"
#include "headers/unit.h"
#include "../headers/metaheuristicTabou.h"
#include "../headers/parser.h"

void metaheuristicGeneticTests() //TODO
{
	populationTests();
}

void populationTests()
{
	Instance * instance = parser_readAllFile("MKP-Instances/theBestBag2.txt");
	Population * population = population_create(2);
	if(population == NULL || population->size != 0 || population->maxSize != 2 || population->persons != NULL)
		unit_error("ASSERT POPULATION 1");
	
	Solution * solution = heuristic(instance, INDIRECT, 5);
	int result = population_append(population, solution);
	if(result == 1 || population->size != 1 || population->persons == NULL || population->persons[0] != solution)
		unit_error("ASSERT POPULATION 2");
	
	Solution * solution2 = heuristic(instance, INDIRECT, 4);
	result = population_append(population, solution2);
	if(result != 1 || population->size != 2 || population->persons[1] != solution2)
		unit_error("ASSERT POPULATION 3");
	
	Solution * solution3 = heuristic(instance, INDIRECT, 3);
	result = population_append(population, solution3);
	if(result != 0 || population->size != 2)
		unit_error("ASSERT POPULATION 4");
	
	solution_destroy(solution3);
	population_destroy(population);
	instance_destroy(instance);
}
