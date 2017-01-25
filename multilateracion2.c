#include <stdio.h>
#include <math.h>

//Calcula los parámetros x e y
void parametros(float xa, float ya, float xb, float yb, float xc, float yc, float pa, float pb, float pc, float *x, float *y){
	float distab, i, j, da, db, dc;
	
	distab=sqrt(pow(xb-xa,2)+pow(yb-ya,2)); //Distancia entre modulo A y B
	i=xc-xa;
	j=yc-ya;

	da=0.012*exp(-0.118*pa); //Pasar la potencia de dBm a metros
	db=0.012*exp(-0.118*pb);
	dc=0.012*exp(-0.118*pc);

	*x=(pow(da,2)-pow(db,2)+pow(distab,2))/(2*distab); //Calculo del parámetro X
	*y=((pow(da,2)-pow(dc,2)+pow(i,2)+pow(j,2))/(2*j))-(i*(*x)/j); //Calculo del parámetro Y

}

//Struct
struct Modulo {
   float x;
   float y;
   float pot;
};


void main(){

	struct Modulo m1; //Declaramos
	struct Modulo m2;	
	struct Modulo m3;
	struct Modulo m4;
	
	int i;	
	int j=1;
	int N=4;
	float px=0;
	float py=0;
	float V[3*(N-2)];
	float sumax=0;
	float sumay=0;
	
	
	// Fijamos los puntos y distancias
	m1.x=0; 
	m1.y=0;
	m1.pot=-52; //en dBm

	m2.x=m1.x+6; //Punto 2 en función del punto 1
	m2.y=m1.y;
	m2.pot=-51;

	m3.x=m1.x+0; // Punto 3 en función del punto 1, valor i
	m3.y=m1.y+8; //            ""                 , valor j
	m3.pot=-51.5;

	m4.x=6;
	m4.y=8;
	m4.pot=-52.5;
	
	V[1]=m3.x;
	V[2]=m3.y;
	V[3]=m3.pot;
	V[4]=m4.x;
	V[5]=m4.y;
	V[6]=m4.pot;

	//Funcion
	for (i=1; i<3*(N-2); i=i+3){
		parametros(m1.x, m1.y, m2.x, m2.y, V[i], V[i+1], m1.pot, m2.pot, V[i+2], &px, &py);
		sumax=px+sumax;
		sumay=py+sumay;
		j=j+1;
	}
	
	px=sumax/(N-2);
	py=sumay/(N-2);
   	printf( "P(%.3f,%.3f)", px,py);
}
