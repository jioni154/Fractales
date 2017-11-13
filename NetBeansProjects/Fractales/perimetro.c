#include "perimetro.h"
#include <math.h>


double perimetro (int n, int l)
{
	
	return 3*l*(pow(4,n)/pow(3,n)); // debemos compilar con gcc ... -lm para la funcion pow
}