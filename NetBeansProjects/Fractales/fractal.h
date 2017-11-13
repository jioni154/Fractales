#ifndef FRACTAL_H
#define FRACTAL_H

void fractal (unsigned int n, float tol, unsigned int r, unsigned int g, unsigned int b, float *px, float *py, float *length);
void get3point (float x1, float y1, float x2, float y2, float array_x[3], float array_y[3]); //le das 2 coordenadas y te develve ne el array los 3 puntos de interes
void rec_array_coord (float *px, float *py, unsigned int k); //le das los arreglos de 'x' e 'y' y los modifica para que a la salida tengan todos lo vertices del fractal del siguiente orden

#endif /* FRACTAL_H */

