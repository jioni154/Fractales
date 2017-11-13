#include"fractal.h"
#include"definesconstantes.h"
#include <math.h>


void fractal (unsigned int n,  float tol, unsigned int r, unsigned int g, unsigned int b, float *px, float *py, float *length)
{
    int i; //unicamente para usarse en el for
    if (n <= 0)
    {
        float x1 = D_WIDTH/2;
        float y1 = D_HEIGHT/4;
    
        float x2 = D_WIDTH/4;
        float y2 = D_HEIGHT*3/4; 
    
        float x3 = D_WIDTH*3/4;
        float y3 = D_HEIGHT*3/4;    //coordenadas del triangulo base
    
        al_clear_to_color(al_color_name("black"));
        al_draw_line(x1, y1, x2 , y2, al_map_rgb(r,g,b) , 20.0 );
        al_draw_line(x2, y2, x3 , y3, al_map_rgb(r,g,b) , 20.0 );
        al_draw_line(x3, y3, x1 , y1, al_map_rgb(r,g,b) , 20.0 ); 
        al_flip_display();
        al_rest(3.0);
        al_clear_to_color(al_color_name("black"));
        px[0] = x1;
        px[1] = x2;   
        px[2] = x3;   
                
        py[0] = y1;
        py[1] = y2;   
        py[2] = y3;  
        
        if (sqrt(pow(px[1]-px[0],2) + pow(py[1]-py[0],2)) < tol)    //si la longitud de la linea es menor a la tolerancia sale de la funcion
            break;
    }/*****************************CASO BASE**********************************/
    else
    {
        fractal(n-1);
        rec_array_coord (px, py,n);    //le damos los arreglos y nos los devuelve con los puntos intermedios
        for (i=0 ; i < (3*pow(4,n)) ; i++)
        {
            al_draw_line(px[i], py[i], px[i+1] , py[i+1], al_map_rgb(r,g,b) , 5.0 );
        }
        al_draw_line(px[(int)(3*pow(4,n))], py[(int)(3*pow(4,n))], px[0] , py[0], al_map_rgb(r,g,b) , 5.0 );   //unimos el 'ultimo' vertices con el cual partimos (y cerrar el fractal)
        al_flip_display();
        al_rest(3);
        al_clear_to_color(al_color_name("black"));
        if (sqrt(pow(px[1]-px[0],2) + pow(py[1]-py[0],2)) < tol)
            break;
    }
    *length = sqrt(pow(px[1]-px[2],2) + pow(py[1]-py[2],2));    //obtenemos el largo
}

void rec_array_coord (float *px, float *py, unsigned int k)
{
    float array_x[3];
    float array_y[3];
    int i;
    float *px_copia = (float *)malloc((3*pow(4,k))*sizeof(float));       
    float *py_copia = (float *)malloc((3*pow(4,k))*sizeof(float));
    for(i=0 ; i < (3*pow(4,k-1)) ; i++)
    {
        px_copia[i] = px[i];
        py_copia[i] = py[i];
    }                   //hacemos una copia ya que deberemos modificar el arreglo en base el el mismo 
    px_copia[(int)(3*pow(4,k-1))] = px_copia[0];
    py_copia[(int)(3*pow(4,k-1))] = py_copia[0];
    for(i=0 ; i < (3*pow(4,k-1)) ; i++)
    {
        px[4*i] = px_copia[i];
        py[4*i] = py_copia[i];
    }//si antes px = [1,2,3, , , , ...] ahora px = [1, , , ,2, , , ,3, , , ...] los espacios 'vacios' son para colocar las siguientes coordenadas
    for(i=0 ; i < (3*pow(4,k-1)) ; i++)
    {
        get3points(px_copia[i], py_copia[i], px_copia[i+1], py_copia[i+1], array_x, array_y);    //an ambos arrays vas a estar contenidas las coordenadas de los vertices del fractal de siguiente orden
        px[4*i+1] = array_x[1];
        px[4*i+2] = array_x[2];
        px[4*i+3] = array_x[3];
        
        py[4*i+1] = array_y[1];
        py[4*i+2] = array_y[2];
        py[4*i+3] = array_y[3];        
    }
    free(px_copia);
    free(py_copia);
}       


void get3points(int x1, int y1, int x2, int y2, int array_x[3], int array_y[3])
{
   float vertice1_x = x1+(x2-x1)/3;
   float vertice3_x = x1+(x2-x1)/3*2;
   
   float vertice1_y = y1+(y2-y1)/3;
   float vertice3_y = y1+(y2-y1)/3*2;
   
   float modulo_A = sqrt(pow(x1-x2,2) + pow(y1-y2,2));  //pura trigonometria para hallar el pico (vertice) creado del fractal
   float modulo_B = cos(M_PI/6)*modulo_A/3;
   float modulo_C = sqrt(pow(modulo_A/2,2) + pow(modulo_B,2));
   float alpha = atan(modulo_B/(modulo_A/2));   
   float theta = atan((y2-y1)/(x2-x1))+alpha;
   
      if ((x2-x1)<0)
   {
       theta += M_PI;   //caracteristica del arcotangente de todo angulo
   }
   
   float vertice2_x = x1+modulo_C*cos(theta);
   float vertice2_y = y1+modulo_C*sin(theta);
   
   
   array_x[0] = vertice1_x;
   array_x[1] = vertice2_x;
   array_x[2] = vertice3_x;
   
   array_y[0] = vertice1_y;
   array_y[1] = vertice2_y;
   array_y[2] = vertice3_y;     //introdicimos en los arreglos proporcionador los nuevos vertices 
}

/*por alguna razon que no logramos descubir no se guardan coorectamente las coordenadas en los arreglos*/