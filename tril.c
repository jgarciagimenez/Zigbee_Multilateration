#include <stdio.h>
#include <math.h>

//Hallar la coordenada x
float hallarx(float d1, float d2, float dist){
   float x;

   x=(pow(d1,2)-pow(d2,2)+pow(dist,2))/(2*dist);

   return x;
}

//Hallar la coordenada y
float hallary(float d1, float d2, float i, float j, float x){
   float y;
   
   y=((pow(d1,2)-pow(d2,2)+pow(i,2)+pow(j,2))/(2*j))-(i*x/j);
   return y;
}


void main()
{   //Potencia
   float d1=3; //Distancia a partir de la potencia del modulo 1
   float d2=3; //Distancia a partir de la potencia del modulo 2
   float d3=3; //Distancia a partir de la potencia del modulo 3
   
   //Parametros fijos
   float i=2.5; //Distancia de componente i del punto 3 con respecto el punto 1
   float j=4; //Distancia de componente j del punto 3 con respecto el punto 1
   float d=3; // Distancia entre el punto 1 y 2
   
   //Puntos
   float x1=0; //Punto 1
   float y1=0;
   float x2=d; //Punto 2
   float y2=0;
   float x3=x1+i; //Punto 3
   float y3=y1+j;
   float px, py; //Resultados
   
   px=hallarx(d1,d2,d);
   py=hallary(d1,d2,i,j,px);

      printf( "P(%.3f,%.3f)", px,py);
}
