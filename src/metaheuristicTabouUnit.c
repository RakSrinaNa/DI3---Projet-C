#include <stddef.h>
#include <stdlib.h>
#include "metaheuristicTabouUnit.h"
#include "utils.h"
#include "metaheuristicTabou.h"
#include "unit.h"

void metaheuristicTabouTests()
{
	movementTests();
}

void movementTests()
{
	Movement * m1;
	MMALLOC(m1, Movement, 1, NULL);
	m1->a = 9;
	m1->b = 15;
	
	Movement * m2 = movement_duplicate(m1);
	if(movement_equals(m1, m2) != 1)
		unit_error("ASSERT MOVEMENT 1");
	m2->a = 15;
	m2->b = 9;
	if(movement_equals(m1, m2) != 1)
		unit_error("ASSERT MOVEMENT 2");
	free(m1);
	free(m2);
}
