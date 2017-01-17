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
	solutionIndirect_decode(solution2->solutions.indirect);
	Solution * solution3 = solution_duplicate(solution1);
	Solution * solution4 = solution_duplicate(solution2);
	Solution * solution5 = solution_duplicate(solution1);

	Population * population = population_create(3);
	population_append(population, solution1);
	population_append(population, solution2);
	population_append(population, solution3);

	if(population_evaluate(population) != 312)
		unit_error("ASSERT GENETIC 0");

	Solution * solution = population_getBest(population);
	if(solution_evaluate(solution) != solution_evaluate(solution1))
		unit_error("ASSERT GENETIC 1");

	solution_destroy(solution);
	solution = population_getWorst(population);
	if(solution_evaluate(solution) != solution_evaluate(solution2))
		unit_error("ASSERT GENETIC 2");
	solution_destroy(solution);

	Population * populationDup = population_duplicate(population);
	if(populationDup == NULL || population->size != populationDup->size || population->maxSize != populationDup->maxSize)
		unit_error("ASSERT GENETIC 3");
	
	population_remove(population, solution2);
	if(population->size != 2 || population->maxSize != 3 || solution_evaluate(population->persons[0]) != solution_evaluate(solution1) || solution_evaluate(population->persons[1]) != solution_evaluate(solution3))
		unit_error("ASSERT GENETIC 4");

	population_append(population, solution4);
	if(population->size != 3 || population->maxSize != 3 || solution_evaluate(population->persons[0]) != solution_evaluate(solution1) || solution_evaluate(population->persons[1]) != solution_evaluate(solution3) || solution_evaluate(population->persons[2]) != solution_evaluate(solution4))
		unit_error("ASSERT GENETIC 5");

	population_replace(population, solution4, solution5);
	if(population->size != 3 || population->maxSize != 3 || solution_evaluate(population->persons[0]) != solution_evaluate(solution1) || solution_evaluate(population->persons[1]) != solution_evaluate(solution3) || solution_evaluate(population->persons[2]) != solution_evaluate(solution5))
		unit_error("ASSERT GENETIC 6");

	population_destroy(populationDup);
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
	if(result != 1 || population->size != 1 || population->persons == NULL || population->persons[0] != solution)
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
