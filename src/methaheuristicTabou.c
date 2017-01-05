#include "methaheuristicTabou.h"

int mouvement_equals(Mouvement * m1, Mouvement * m2)
{
    if((m1->a == m2->a && m1->b == m2->b) || (m1->a == m2->b && m1->b == m2->a))
        return 1;
    return 0;
}
