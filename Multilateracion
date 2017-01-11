#include <stdio.h>
#include <math.h>

//Calcula los parámetros x e y
void parametros(float xa, float ya, float xb, float yb, float xc, float yc, float da, float db, float dc, float *x, float *y){
	float distab, i, j;
	
	distab=sqrt(pow(xb-xa,2)+pow(yb-ya,2)); //Distancia entre modulo A y B
	i=xc-xa;
	j=yc-ya;

	*x=(pow(da,2)-pow(db,2)+pow(distab,2))/(2*distab); //Calculo del parámetro X
	*y=((pow(da,2)-pow(dc,2)+pow(i,2)+pow(j,2))/(2*j))-(i*(*x)/j); //Calculo del parámetro Y

}

//Struct
struct Modulo {
   float x;
   float y;
   float dist;
};


void main(){

	struct Modulo m1; //Declaramos
	struct Modulo m2;	
	struct Modulo m3;
	struct Modulo m4;

	int N=4;
	float px=0;
	float py=0;
	
	
	// Fijamos los puntos y distancias
	m1.x=0; 
	m1.y=0;
	m1.dist=5;

	m2.x=m1.x+6; //Punto 2 en función del punto 1
	m2.y=m1.y;
	m2.dist=5;

	m3.x=m1.x+0; // Punto 3 en función del punto 1, valor i = 0
	m3.y=m1.y+8; //            ""                 , valor j = 8
	m3.dist=5;

	m4.x=6;
	m4.y=8;
	m4.dist=5;

	//Funcion
	parametros(m1.x, m1.y, m2.x, m2.y, m3.x, m3.y, m1.dist, m2.dist, m3.dist, &px, &py);
	
   	printf( "P(%.3f,%.3f)", px,py);
