#include <stdio.h>
#include "fractal.h"
#include "perimetro.h"
#include "area.h"
#include <string.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_color.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <allegro5/allegro_primitives.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include "definesconstantes.h"

int main(int argc, char *argv[]) 
{
   ALLEGRO_DISPLAY *display = NULL; 
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
 
   if(!al_init_primitives_addon()){
	  fprintf(stderr, "failed to initialize primitives!\n");
	  return -1;
   }
   
   display = al_create_display(D_WIDTH, D_HEIGHT);
 
   if(!display) {
	  al_shutdown_primitives_addon();
	  fprintf(stderr, "failed to create display!\n");
      return -1;
   }
   
   
   
   /************************hasta aca las inicializaciones********************/
   
   
   
   int i;
   unsigned int orden = NULL;   //tomamos los inputs del user
   float tol = NULL;
   int r = NULL;
   int g = NULL;
   int b = NULL;
   char name[MAX_CHARACT];
   for (i=0 ; i<argc ; i++)
   {
       if(strcmp(argv[i],"-order"))
       {
           orden = atoi(argv[i+1]);
       }
       else if(strcmp(argv[i],"-tol"))
       {
           tol = atof(argv[i+1]);
       }
       else if(strcmp(argv[i],"-colorr"))
       {
           r = atoi(argv[i+1]);
       }
       else if(strcmp(argv[i],"-colorg"))
       {
           g = atoi(argv[i+1]);
       }
       else if(strcmp(argv[i],"-colorb"))
       {
           b = atoi(argv[i+1]);
       }
       else if(strcmp(argv[i],"-report"))
       {
           strcpy(name,argv[i+1]);
       }
   }
   
   
   
   
   if ((orden == NULL && tol == NULL) || r == NULL || b == NULL || g == NULL)
   {
       printf("no ha introducido debidamente los parametros, escriba lo siguiente \n%s -order 'n' -tol 'tolerancia' -colorr 'red' -colorb 'blue' -color 'green'", argv[0]);
       return 0;
   }
   
   float length;
        
   float *px = (float *)malloc((3*pow(4,orden))*sizeof(float)); //arreglo dinamico en el que guardamos los valores de x
   float *py = (float *)malloc((3*pow(4,orden))*sizeof(float)); //arreglo dinamico en el que guardamos los valores de y

   fractal(orden, tol, r, g, b, px, py, &length);
   
   
      
   /*******************************+*/
   
   
   FILE* archivo = NULL;
	archivo = fopen( nombre, "w+"); //creacion del archivo en el que vamos a escribir, elegimos el nombre al principio
						// usamos w+ para escribir y leer en el archivo que se crea si no existe
	
	if (archivo != NULL)
        {

	fprintf(archivo, "Reporte descriptivo del fractal dibujado\n");	 
	fprintf(archivo, "Orden : %d\n", orden);	
	fprintf(archivo, "Tolerancia : %d\n", tol);
	fprintf(archivo, "Perimetro : %f\n", perimetro (orden,length));
	fprintf(archivo, "Area : %f\n", area(orden,length));
	fclose(archivo);
	printf("Done\n");
        
        }

    else

        {


        printf("Imposible de abrir el archivo reporte.txt");

        }
        
        
        /*****************************************/
        
        
        
        
   
   al_destroy_display(display);
   al_shutdown_primitives_addon();
   free(px);
   free(py);    //NO VA A HABER PROBLEMAS CON LOS TIEMPOS DE COMPILACION Y EJECUCION?
   return 0;
}