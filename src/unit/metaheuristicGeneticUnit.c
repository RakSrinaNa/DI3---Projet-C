#include "headers/metaheuristicGeneticUnit.h"
#include "../headers/metaheuristicGenetic.h"
#include "headers/unit.h"
#include "../headers/metaheuristicTabou.h"
#include "../headers/parser.h"
#include "../headers/solution.h"

void metaheuristicGeneticTests() //TODO
{
	Instance * instance = parser_readAllFile("MKP-Instances/theBestBag2.txt");
	populationTests(instance);
	
	Solution * solution1 = heuristic(instance, INDIRECT, 5);
	Solution * solution2 = solution_duplicate(solution1);
	solution2->solutions.indirect->itemsOrder[0] = 1;
	solution2->solutions.indirect->itemsOrder[1] = 0;
	solution2->solutions.indirect->itemsOrder[2] = 2;
	Solution * solution3 = solution_duplicate(solution1);
	
	Population * population = population_create(3);
	population_append(population, solution1);
	population_append(population, solution2);
	population_append(population, solution3);
	
	Solution * solution = metaheuristicGenetic_bestFromPopulation(population);
	if(solution != solution1)
		unit_error("ASSERT GENETIC 1");
	
	solution_destroy(solution);
	population_destroy(population);
	instance_destroy(instance);
}

void populationTests(Instance * instance)
{
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
}
