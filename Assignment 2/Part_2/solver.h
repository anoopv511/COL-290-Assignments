#include <stdio.h>
#include <complex.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct
{
	char name[50];
	int pos;
	int ingoing[100];
	int outgoing[100];
	int insize;
	int outsize;
	
} net;


typedef struct 
{
	char name[50];
	int net1;
	int net2;
	char type;
	double value;	
	int pos;
	double freq;
	double valdc;
	double delay;
} element;

double complex* solve_matrix(double complex* matrix1,double complex* matrix2,int rows,int columns);

void printmatrix(double complex* A,int rows,int columns);

void printsoln(FILE* o,double complex* A,element e[],int size);


int findfreq(double A[],int size,double freq){
	for (int i = 0; i < size; i++)
	{
		if(A[i]==freq)
			return i;
	}
	return -1;
}

void addfreq(double freq,double A[],int* size){
	if(findfreq(A,*size,freq)!=-1)
		return;
	A[*size]=freq;
	*size=*size+1;
}

int netpos(char name[],net vertices[],int size){
	for (int i = 0; i < size; i++)
	{
		if(strcmp(name,vertices[i].name)==0)
			return i;
	}

	return -1;
}

void gaddnet(char $2[],net v[],int* size){
	 char zero[2]="0";
	 if(strcmp(zero,$2)==0)
	 	return;
	 int vs=*size;
	 if(netpos($2,v,vs)==-1){
            net newnet;
            strcpy(newnet.name,$2);
            newnet.outsize=0;
            newnet.insize=0;
            v[vs]=newnet;
            vs++;
          	*size=*size+1;
          	//printf("add %d %d\n", *size,vs);
          }

          return;
                                                                 
}

double getval(char val[]){
	double dval;
	int len = strlen(val);
	//printf("val=%s\n",val );
	if(val[len-1]=='F'){
		val[len-1]='\0';
		 sscanf(val,"%lf",&dval);
		 //printf("%.9lf\n",dval );
		return dval*pow(10,-15);	
	}
	if(val[len-1]=='P'){
		val[len-1]='\0';
		 sscanf(val,"%lf",&dval);
		return dval*pow(10,-12);	
	}
	if(val[len-1]=='K'){
		val[len-1]='\0';
		 sscanf(val,"%lf",&dval);
		return dval*pow(10,3);	
	}
	if(val[len-1]=='N'){
		val[len-1]='\0';
		 sscanf(val,"%lf",&dval);
		return dval*pow(10,-9);	
	}
	if(val[len-1]=='M'){
		val[len-1]='\0';
		 sscanf(val,"%lf",&dval);
		return dval*pow(10,-3);	
	}
	if(val[len-1]=='U'){
		val[len-1]='\0';
		 sscanf(val,"%lf",&dval);
		//printf("%.9lf\n",dval );
		return dval*pow(10,-6);	

	}
	if(val[len-1]=='G'){
		val[len-1]='\0';
		 sscanf(val,"%lf",&dval);
		//printf("%.9lf\n",dval );
		return dval*pow(10,9);	

	}
	if(val[len-1]=='T'){
		val[len-1]='\0';
		 sscanf(val,"%lf",&dval);
		//printf("%.9lf\n",dval );
		return dval*pow(10,12);	

	}
	
	
	if(val[len-1]=='G' && val[len-3]=='M'){
		val[len-3]='\0';
		 sscanf(val,"%lf",&dval);
		return dval*pow(10,6);	
	}

		
	(sscanf(val,"%lf",&dval));
	return dval;

}

void reduce(char val[],int k){
	val[strlen(val)-k]='\0';
}


void seteq1(int m,double complex* A,int p,int q,double complex*  B,int x,int y){
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			A[(x+i)*m+(y+j)]=B[(i*q)+j];
		}
	}

}


void seteq2(int m,double complex* A,int p,int q,double complex*  B,int x,int y){
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			A[(x+j)*m+(y+i)]=-B[(i*q)+j];
		}
	}

}

void init_matrix(double complex* A,int r,int c){
	for (int i = 0; i < r*c; i++)
	{
		A[i]=0;
	}
}
double complex*  getsoln(net v[],element e[],int nb,int nv,double freq){
	double complex* M = (double complex*)malloc(sizeof(double complex)*((2*nb+nv)*(2*nb+nv)));

	double complex* A = (double complex*)malloc(sizeof(double complex)*(nb*(nv)));

	init_matrix(M,2*nb+nv,2*nb+nv);
	init_matrix(A,nv,nb);

	int j1=0,j2=0;
	for (int i = 0; i < nv; i++)
	{
		while(j1<v[i].insize){
			//printf("%s456\n",v[i].name);
			A[nb*i+v[i].ingoing[j1]]=1;
			j1++;
		}

		while(j2<v[i].outsize){
			A[nb*i+v[i].outgoing[j2]]=-1;
			j2++;
		}
		j1=0;
		j2=0;
			
	}

//	printmatrix(A,nv,nb);


	double complex* Iden = (double complex*)malloc(sizeof(double complex)*(nb*(nb)));
	init_matrix(Iden,nb,nb);
	double complex* Y = (double complex*)malloc(sizeof(double complex)*(nb*(nb)));
	double complex* Z = (double complex*)malloc(sizeof(double complex)*(nb*(nb)));
	double complex* Var = (double complex*)malloc(sizeof(double complex)*(2*nb+nv));
	init_matrix(Y,nb,nb);
	init_matrix(Z,nb,nb);
	init_matrix(Var,2*nb+nv,1);
	


	seteq1(2*nb+nv,M,nv,nb,A,0,0);
	float pi=acos(-1);

	for (int i = 0; i < nb; i++)
	{
		Iden[i*nb+i]=1;
		if(e[i].type=='R'){
			Y[i*nb+i]=1;
			Z[i*nb+i]=e[i].value;		
		}

		if(e[i].type=='L'){
			Y[i*nb+i]=1;
			Z[i*nb+i]=2*pi*freq*e[i].value*I;		
		}

		if(e[i].type=='C'){
			Z[i*nb+i]=1;
			Y[i*nb+i]=2*pi*freq*e[i].value*I;		
		}

		if(e[i].type=='V'){
			Y[i*nb+i]=1;
			Z[i*nb+i]=0;

			Var[nb+nv+i]=0;
			
			if(freq==0)
			Var[nb+nv+i]= e[i].valdc;
			
			if(freq==e[i].freq)
			Var[nb+nv+i]= e[i].value*(cos(-2*pi*freq*e[i].delay)+sin(-2*pi*freq*e[i].delay)*I);


		}

		if(e[i].type=='I'){
			Z[i*nb+i]=1;
			Y[i*nb+i]=0;

			Var[nb+nv+i]=0;

			if(freq==0)
			Var[nb+nv+i]= e[i].valdc;
			
			if(freq==e[i].freq)
			Var[nb+nv+i]= e[i].value*(cos(-2*pi*freq*e[i].delay)+sin(-2*pi*freq*e[i].delay)*I);
		}
	}
//	printmatrix(Y,nb,nb);
//	printf("\n");
//	printmatrix(Z,nb,nb);
//	printf("\n");
	
//	printmatrix(Iden,nb,nb);
//	printf("\n");
//	printmatrix(Var,1,2*nb+nv);
	
	seteq1(2*nb+nv,M,nb,nb,Iden,nv,nb);
	seteq2(2*nb+nv,M,nv,nb,A,nv,2*nb);
	seteq1(2*nb+nv,M,nb,nb,Z,nb+nv,0);
	seteq1(2*nb+nv,M,nb,nb,Y,nb+nv,nb);
//	printmatrix(M,2*nb+nv,2*nb+nv);
//	printf("\n");

	return solve_matrix(M,Var,2*nb+nv,2*nb+nv+1);





}

void swap(double complex*A,int i,int j,int rows,int columns){
	double complex temp=0;
	for (int z = 0; z < columns;z++)
	{
		temp=A[i*columns+z];
		A[i*columns+z]=A[j*columns+z];
		A[j*columns+z]=temp;

	}
}

double complex* solve_matrix(double complex* matrix1,double complex* matrix2,int rows,int columns){
	double complex* matrix = (double complex*)malloc(sizeof(double complex)*(rows*columns));

	for (int i = 0; i < rows;i++)
	{
		for (int j = 0; j < columns-1;j++)
		{
			matrix[i*columns + j] = matrix1[i*(columns-1) + j] ;
		}
	}
	for (int i = 0; i < columns; ++i)
	{
		matrix[(  (i)*columns) + columns-1] = matrix2[i]; 
			
	}

//	printmatrix(matrix,rows,columns);

	if(rows < columns-1) return NULL;
	int i,j,k;
	double complex factor,temp;

	int invalid = 0;
	for(i=0;i<rows;i++){	
		if(creal(matrix[i*columns + i]) == 0 && cimag(matrix[i*columns + i])==0){
			for (int zeta = i+1; zeta < rows; zeta++)
			{
				if((creal(matrix[zeta*columns + i]) != 0 || cimag(matrix[zeta*columns + i])!=0)){
					swap(matrix,i,zeta,rows,columns);
					//printf("%d\n",zeta );

					break;
				}


			}
		}
		double complex temp=matrix[i*columns+i];

		for (int mega = 0; mega < columns; mega++)
		{
			matrix[i*columns+mega]=matrix[i*columns+mega]/temp;
		}

		//printf("\n");
		//printmatrix(matrix,rows,columns);
		//printf("\n");
		for(k=0;k<rows;k++){
			if(k == i) continue;
			factor = (matrix[k*columns + i]);
			for(j=0;j<columns;j++){
				temp = (matrix[i*columns + j]*factor);
				matrix[k*columns + j] = (matrix[k*columns + j]-temp);
			}
		}
	}
	//printf("\n");
	//printmatrix(matrix,rows,columns);
	//printf("invalid=%d\n",invalid );
	double complex* solution = (double complex*)malloc(sizeof(double complex)*(rows-invalid));
	for(i=0;i<rows-invalid;i++){
		if(creal(matrix[i*columns + i]) == 0 && cimag(matrix[i*columns + i])==0) continue;
		solution[i] = (matrix[i*columns + (columns-1)]/matrix[i*columns + i]);
	}


	return solution;
}

void arraysort(double A[],int size){
	for (int i = 0; i < size; i++)
	{
		for (int j = i+1; j < size; j++)
		{
			if(A[i]>A[j]){
				double temp = A[i];
				A[i]=A[j];
				A[j]=temp;
			}
		}
	}
}

void printmatrix(double complex* A,int rows,int columns){
	for (int i = 0; i < rows;i++)
	{
		for (int j = 0; j < columns; j++)
		{
			printf("%.1lf,%.9lf ",creal(A[i*columns+j]),cimag(A[i*columns+j]) );
		}
		printf("\n");
	}
}

void printsoln(FILE* o,double complex* A,element e[],int size){
	float pi = acos(-1);
	//printf("pi=%f\n",pi);
	
	fprintf(o,"VOLTAGES\n");
	for (int i = size; i < 2*size; i++)
	{
		double amp = sqrt(creal(A[i])*creal(A[i])+cimag(A[i])*cimag(A[i]));
		
		double ang=0;
		
		 ang = 180*atan(cimag(A[i])/creal(A[i]))/pi;
		if(fabs(creal(A[i]))<=pow(10,-15))
			ang=90;

		if(fabs(cimag(A[i]))<=pow(10,-15))
			ang=0;



		fprintf(o,"%s %.3lf %.3lf \n",e[i-size].name,amp,ang);
		//printf("V=%.12lf,%.12lf\n ",creal(A[i]),cimag(A[i]) );

	}
	fprintf(o,"\n");
	fprintf(o,"CURRENTS\n");
	
	for (int i = 0; i < size; i++)
	{
		double amp = sqrt(creal(A[i])*creal(A[i])+cimag(A[i])*cimag(A[i]));
		double ang=0;
		
		 ang = 180*atan(cimag(A[i])/creal(A[i]))/pi;
		if(fabs(creal(A[i]))<=pow(10,-15))
			ang=90;

		if(fabs(cimag(A[i]))<=pow(10,-15))
			ang=0;

		fprintf(o,"%s %.3lf %.3lf \n",e[i].name,amp,ang);
		//printf("I=%.12lf,%.12lf\n ",creal(A[i]),cimag(A[i]) );
	}


	fprintf(o,"\n");
	fprintf(o,"\n");
}
/*
int main(){
	//double complex A[5][5]={{1,1,0,0,0},{0,0,1,0,1},{0,0,0,1,1},{0,0,1,0,0},{0,10,0,1,0}};
	//double complex B[3][3];
	//double complex B[5]={0,0,0,5,0};
	//printf("%f\n",creal(getdet(5,A))); 
	char val[20] = "1.2MEG";
	printf("%f\n", getval(val));
	double pi=acos(-1);


	net vertices[100];
	char name1[20]="n1";
	char name2[20]="n0";
	char name3[20]="n2";

	net n1;
	strcpy(n1.name,name1);
	n1.insize=1;
	n1.outsize=1;
	n1.ingoing[0]=2;
	n1.outgoing[0]=3;

	net n2;
	strcpy(n2.name,name3);
	n2.insize=1;
	n2.outsize=1;
	n2.ingoing[0]=2;
	n2.outgoing[0]=0;

	net n3;
	strcpy(n3.name,name2);
	n3.insize=1;
	n3.outsize=1;
	n3.outgoing[0]=3;
	n3.outgoing[0]=1;

	vertices[0]=n2;
	vertices[1]=n3;
	vertices[2]=n1;

	element e1,e2,e3,e4;
	e3.type='V';
	e3.value=5;
	e3.pos=2;
	e3.freq=2*pi*60;
	e3.valdc=0;

	e4.type='V';
	e4.value=5;
	e4.pos=3;
	e4.freq=2*pi*90;
	e4.valdc=0;

	e1.type='R';
	e1.value=2200;
	e1.pos=0;


	e2.type='C';
	e2.value=0.000001;
	e2.pos=1;





	element edges[100];

	edges[0]=e1;
	edges[1]=e2;

	edges[2]=e3;
	edges[3]=e4;

	printsoln(getsoln(vertices,edges,4,3,2*pi*60),4);
	printsoln(getsoln(vertices,edges,4,3,2*pi*90),4);

	
	//getinv(5,A,B);
	//printsoln(solve_matrix(&A[0][0],&B[0],5,6),5);
	//printmatrix(2,B);

	//printmatrix(5,B);



}
*/