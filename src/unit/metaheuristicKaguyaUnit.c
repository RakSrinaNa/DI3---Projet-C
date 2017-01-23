#include "headers/metaheuristicKaguyaUnit.h"
#include "../headers/instance.h"
#include "../headers/parser.h"
#include "../headers/solution.h"
#include "../headers/metaheuristicKaguya.h"

void metaheuristicKaguyaTests()
{
	Parser * parser = parser_create("MKP-Instances/_mknapcb1_res.txt");
	Instance * instance = parser_getNextInstance(parser);
	solution_destroy(metaheuristicKaguya_search(instance, DIRECT));
	solution_destroy(metaheuristicKaguya_search(instance, INDIRECT));
	instance_destroy(instance);
	parser_destroy(parser);
}