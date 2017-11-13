#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "area.h"


double a0 (int l)
{

	return (sqrt(3)/4) * (pow(l,2));   // calcul del area del primer triangulo

}

double area (int n, int l)
{

	return (a0(l)/5) * (8-3*(pow(4,n)/pow(9,n)));

}
