#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.141592654

/******************************Helper Functions**********************************/

float rnd_0(float number){
	return (-0.00099 < number || number < 0.0001 ? 0 : number);
}

float rnd(float number,int n){
	return roundf(rnd_0(number) * pow(10,n))/pow(10,n);
}

/********************************************************************************/

/**************************Complex Numbers and Functions*************************/

typedef struct complex{
	float real;
	float imaginary;
	float amplitude;
	float phase;
}complex;

void calc_amp_phase(complex *c){
	c->amplitude = sqrt(pow(c->real,2)+pow(c->imaginary,2));
	if(c->real > 0){
		c->phase = (atan(c->imaginary / c->real) * 180 / PI);
	}
	else if(c->real < 0){
		c->phase = (atan(c->imaginary / c->real) * 180 / PI) + 180;	
	}
	else{
		c->phase = c->imaginary < 0 ? 270 : 90;
	}
}

void calc_real_imag(complex *c){
	c->real = (c->phase == 90 || c->phase == 270 || c->phase == -90) ? 0 : c->amplitude * cos(c->phase * PI / 180);
	c->imaginary = (c->phase == 0 || c->phase == 180) ? 0 : c->amplitude * sin(c->phase * PI / 180);
}

complex init_complex(float r,float i,float a,float p){
	complex c;
	c.real = r;
	c.imaginary = i;
	c.amplitude = a;
	c.phase = p;
	if(r != 0 || i != 0) calc_amp_phase(&c);
	else if(a != 0) calc_real_imag(&c);
	return c;
}

complex copy_complex(complex c){
	complex cc;
	cc.real = c.real;
	cc.imaginary = c.imaginary;
	cc.amplitude = c.amplitude;
	cc.phase = c.phase;
	return cc;
}

void print_complex(complex c){
	printf("Real = %0.3f and Imaginary = %0.3f\n", c.real,c.imaginary);
	printf("Ampiltude = %0.3f and Phase = %0.3f\n", c.amplitude,c.phase);
}

int equal(complex *c,complex *d){
	return ((c->real == d->real) && (c->imaginary == d->imaginary) && (c->amplitude == d->amplitude) && (c->phase == d->phase)) ? 1 : 0;
}

complex neg(complex *c){
	complex out;
	out.real = c->real * -1;
	out.imaginary = c->imaginary * -1;
	out.amplitude = c->amplitude * -1;
	out.phase = c->phase;
	return out;
}

complex add(complex *c,complex *d){
	complex out;
	out.real = c->real + d->real;
	out.imaginary = c->imaginary + d->imaginary;
	calc_amp_phase(&out);
	return out;
}

complex subtract(complex *c,complex *d){
	complex out;
	out.real = c->real - d->real;
	out.imaginary = c->imaginary - d->imaginary;
	calc_amp_phase(&out);
	return out;
}

complex multiply(complex *c,complex *d){
	complex out;
	out.amplitude = c->amplitude * d->amplitude;
	out.phase = c->phase + d->phase;
	calc_real_imag(&out);
	return out;
}

complex divide(complex *c,complex *d){
	complex out;
	out.amplitude = c->amplitude/d->amplitude;
	out.phase = c->phase - d->phase;
	calc_real_imag(&out);
	return out;
}

/********************************************************************************/

/*******************************Matrix Realted***********************************/

complex* solve_matrix(complex* matrix,int rows,int columns){
	if(rows < columns-1) return NULL;
	int i,j,k;
	complex factor,temp;
	for(i=0;i<rows;i++){
		for(j=0;j<columns;j++){
			for(k=0;k<rows;k++){
				if(k == i) continue;
				matrix[i*columns + j] = add(&matrix[i*columns + j],&matrix[k*columns + j]);
			}
		}
	}
	int invalid = 0;
	for(i=0;i<rows;i++){	
		if(matrix[i*columns + i].amplitude == 0){
			invalid++;
			continue;
		}
		for(k=0;k<rows;k++){
			if(k == i) continue;
			factor = divide(&matrix[k*columns + i],&matrix[i*columns + i]);
			for(j=0;j<columns;j++){
				temp = multiply(&matrix[i*columns + j],&factor);
				matrix[k*columns + j] = subtract(&matrix[k*columns + j],&temp);
			}
		}
	}
	complex* solution = (complex*)malloc(sizeof(complex)*(rows-invalid));
	for(i=0;i<rows-invalid;i++){
		if(matrix[i*columns + i].amplitude == 0) continue;
		solution[i] = divide(&matrix[i*columns + (columns-1)],&matrix[i*columns + i]);
	}
	return solution;
}

complex* transpose_matrix(complex* matrix,int rows,int columns){
	complex* transpose = (complex*)malloc(sizeof(complex)*rows*columns);
	int i,j;
	for(i=0;i<rows;i++){
		for(j=0;j<columns;j++){
			transpose[j*rows + i] = matrix[i*columns + j];
		}
	}
	return transpose;
}

void print_matrix(complex* matrix,int rows,int columns){
	int i,j;
	for(i=0;i<rows;i++){
		for(j=0;j<columns;j++){
			printf("%f+j%f\t", matrix[i*columns + j].real,matrix[i*columns + j].imaginary);
		}
		printf("\n");
	}
}

/********************************************************************************/

/*******************************Graph Related************************************/

typedef struct edge edge;

typedef struct node{
	edge** in;
	edge** out;
	int number;
	int in_count;
	int out_count;
	complex node_voltage;
}node;

struct edge{
	node *start;
	node *end;
	int id;
	complex current;
	complex voltage;
	complex	impedance;
};

node circuit[100000];
edge components[100000];
int voltage_sources[100000];
int current_sources[100000];
int node_count = 0;
int edge_count = 0;
int vol_src_count = 0;
int curr_src_count = 0;
int m = 0;
float source_freq;

node addNode(){
	circuit[node_count].number = node_count;
	circuit[node_count].in_count = 0;
	circuit[node_count].out_count = 0;
	circuit[node_count].in = (edge**)malloc(sizeof(edge*)*1000);
	circuit[node_count].out = (edge**)malloc(sizeof(edge*)*1000);
	circuit[node_count].node_voltage = init_complex(0,0,0,0);
	return circuit[node_count++];
}

edge* addEdge(int m,int n,complex i,complex v,complex z){
	node startNode = m < node_count ? circuit[m] : addNode();
	node endNode = n < node_count ? circuit[n] : addNode();
	components[edge_count].id = edge_count;
	components[edge_count].current = i;
	components[edge_count].voltage = v;
	components[edge_count].impedance = z;
	components[edge_count].start = &circuit[m];
	components[edge_count].end = &circuit[n];
	if(components[edge_count].voltage.amplitude != 0) voltage_sources[vol_src_count++] = edge_count;
	if(components[edge_count].current.amplitude != 0) current_sources[curr_src_count++] = edge_count;
	startNode.out[startNode.out_count] = &components[edge_count];
	circuit[m].out_count++;
	endNode.in[endNode.in_count] = &components[edge_count];
	circuit[n].in_count++;
	return &components[edge_count++];
}

edge* getEdge(int m,int n){
	if(m >= node_count || n >= node_count || m < 0 || n < 0) return NULL;
	node startNode = circuit[m];
	int i;
	for(i=0;i<startNode.out_count;i++){
		if(((startNode.out[i])->end)->number == n) return startNode.out[i];
	}
	return NULL;
}

void print_edge(edge* e){
	if(e == NULL){
		printf("No component\n");
		return;
	}
	printf("%d:  %d ----> %d\n", e->id,(e->start)->number,(e->end)->number);
	printf("Impedance:\n");
	print_complex(e->impedance);
	printf("Voltage:\n");
	print_complex(e->voltage);
	printf("Current:\n");
	print_complex(e->current);
}

void dfs_routine(int start,int visited[]){
	int i;
	visited[start] = 1;
	for(i=0;i<circuit[start].out_count;i++){
		if(visited[((circuit[start].out[i])->end)->number] == 0){			
			dfs_routine(((circuit[start].out[i])->end)->number,visited);
		}
	}
}

void build_g_matrix(complex* c){
	int i,start,end,tmp;
	int n = node_count - 1;
	complex zero_complex = init_complex(0,0,0,0);
	complex unit_complex = init_complex(1,0,0,0);
	for(i=0;i<n*n;i++){
		c[i] = zero_complex;
	}
	complex value = init_complex(0,0,0,0);
	for(i=0;i<edge_count;i++){
		if(components[i].impedance.amplitude != 0){
			start = (components[i].start)->number - 1;
			end = (components[i].end)->number - 1;
			value = divide(&unit_complex,&(components[i].impedance));
			if(start == -1 || end == -1){
				tmp = start == -1 ? end : start;
				c[tmp*node_count] = add(&c[tmp*node_count],&value);
				continue;
			}
			c[start + end*n] = subtract(&c[start + end*n],&value);
			c[start*node_count] = add(&c[start*node_count],&value);
			c[start*n + end] = subtract(&c[start*n + end],&value);
			c[end*node_count] = add(&c[end*node_count],&value);
		}
	}
}

void build_b_matrix(complex* c){
	int i,start,end,tmp;
	int n = node_count - 1;
	complex zero_complex = init_complex(0,0,0,0);
	for(i=0;i<n*vol_src_count;i++){
		c[i] = zero_complex;
	}
	for(i=0;i<vol_src_count;i++){
		start = (components[voltage_sources[i]].start)->number - 1;
		end = (components[voltage_sources[i]].end)->number - 1;
		if(start != -1) c[start*vol_src_count + i] = init_complex(1,0,0,0);
		if(end != -1) c[end*vol_src_count + i] = init_complex(-1,0,0,0);
	}
}

void build_c_matrix(complex* c){
	int i,start,end,tmp;
	int n = node_count - 1;
	complex zero_complex = init_complex(0,0,0,0);
	for(i=0;i<n*vol_src_count;i++){
		c[i] = zero_complex;
	}
	for(i=0;i<vol_src_count;i++){
		start = (components[voltage_sources[i]].start)->number - 1;
		end = (components[voltage_sources[i]].end)->number - 1;
		if(start != -1) c[start + i*n] = init_complex(1,0,0,0);
		if(end != -1) c[end + i*n] = init_complex(-1,0,0,0);
	}
}

void build_d_matrix(complex* c){
	int i;
	complex zero_complex = init_complex(0,0,0,0);
	for(i=0;i<vol_src_count*vol_src_count;i++){
		c[i] = zero_complex;
	}
}

void build_z_matrix(complex* c){
	int i,start,end;
	int n = node_count - 1;
	complex zero_complex = init_complex(0,0,0,0);
	for(i=0;i<n + vol_src_count;i++){
		c[i] = zero_complex;
	}
	for(i=0;i<curr_src_count;i++){
		start = (components[current_sources[i]].start)->number - 1;
		end = (components[current_sources[i]].end)->number - 1;
		if(start != -1) c[start] = subtract(&c[start],&components[current_sources[i]].current);
		if(end != -1) c[end] = add(&c[end],&components[current_sources[i]].current);
	}
	for(i=0;i<vol_src_count;i++){
		c[n+i] = components[voltage_sources[i]].voltage;
	}
}

void build_eq_matrix(complex* g,complex* b,complex* c,complex* d,complex* z,complex* eq){
	int i,j;
	int size = node_count + vol_src_count;
	int n = node_count - 1;
	for(i=0;i<size-1;i++){
		for(j=0;j<size;j++){
			if(j < n){
				eq[i*size + j] = i < n ? g[i*n + j] : c[(i - n)*n + j];
			}
			else if(j == size-1){
				eq[i*size + j] = z[i];
			}
			else{
				eq[i*size + j] = i < n ? b[i*vol_src_count + (j - n)] : d[(i - n)*vol_src_count + (j - n)];
			}
		}
	}
}

void print_matrices(complex* g,complex* b,complex* c,complex* d,complex* z,complex* eq){
	print_matrix(g,node_count-1,node_count-1);
	printf("\n");
	print_matrix(b,node_count-1,vol_src_count);
	printf("\n");
	print_matrix(c,vol_src_count,node_count-1);
	printf("\n");
	print_matrix(d,vol_src_count,vol_src_count);
	printf("\n");
	print_matrix(z,node_count - 1 + vol_src_count,1);
	printf("\n");
	print_matrix(eq,node_count - 1 + vol_src_count,node_count + vol_src_count);
	printf("\n");
}

void solve_circuit(){
	complex* g_matrix = (complex*)malloc(sizeof(complex)*(node_count-1)*(node_count-1));
	build_g_matrix(g_matrix);
	complex* b_matrix = (complex*)malloc(sizeof(complex)*(node_count-1)*vol_src_count);
	build_b_matrix(b_matrix);
	complex* c_matrix = (complex*)malloc(sizeof(complex)*(node_count-1)*vol_src_count);
	build_c_matrix(c_matrix);
	complex* d_matrix = (complex*)malloc(sizeof(complex)*vol_src_count*vol_src_count);
	build_d_matrix(d_matrix);
	complex* z_matrix = (complex*)malloc(sizeof(complex)*(node_count - 1 + vol_src_count));
	build_z_matrix(z_matrix);
	complex* equation_matrix = (complex*)malloc(sizeof(complex)*(node_count - 1 + vol_src_count)*(node_count + vol_src_count));
	build_eq_matrix(g_matrix,b_matrix,c_matrix,d_matrix,z_matrix,equation_matrix);
	complex* solution_matrix = solve_matrix(equation_matrix,node_count - 1 + vol_src_count,node_count + vol_src_count);
	print_matrix(solution_matrix,node_count - 1 + vol_src_count,1);
}

void analyse_circuit(){
	
}

/********************************************************************************/

int main(){

	source_freq = 2*PI*60;

	complex c = init_complex(0,0,0,0);
	complex v = init_complex(0,0,120,0);
	complex z = init_complex(0,0,0,0);
	addEdge(0,1,c,v,z);

	c = init_complex(0,0,0,0);
	v = init_complex(0,0,0,0);
	z = init_complex(0,0,1000000/(4.7*source_freq),-90);
	addEdge(1,2,c,v,z);

	c = init_complex(0,0,0,0);
	v = init_complex(0,0,0,0);
	z = init_complex(0,0,470,0);
	addEdge(2,0,c,v,z);

	c = init_complex(0,0,0,0);
	v = init_complex(0,0,0,0);
	z = init_complex(0,0,650*source_freq/1000,90);
	addEdge(2,3,c,v,z);

	c = init_complex(0,0,0,0);
	v = init_complex(0,0,0,0);
	z = init_complex(0,0,1000000/(1.5*source_freq),-90);
	addEdge(3,0,c,v,z);

	solve_circuit();

	return 0;
}