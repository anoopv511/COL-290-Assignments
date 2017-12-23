#include <stdio.h>
#include <stdlib.h>

typedef struct component{
	char type;
	int start;
	int end;
	char* value;
}component;

FILE* svg;
int* nets_start;
int* nets_end;
int* closed;
int total_nets;
int scale = 2;
component* comps;
int level;

void print_line(float x1,float y1,float x2,float y2){
	float rad = 2*scale;
	float thickness = 1*scale;
	x1*=scale;
	y1*=scale;
	x2*=scale;
	y2*=scale;
	fprintf(svg,"<circle fill=\"black\" stroke-width=\"%0.3f\" cx=\"%0.3f\" cy=\"%0.3f\" r=\"%0.3f\"/>\n",thickness,x1,y1,rad);
	fprintf(svg,"<line fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" x1=\"%0.3f\" y1=\"%0.3f\" x2=\"%0.3f\" y2=\"%0.3f\"/>\n",thickness,x1,y1,x2,y2);
	fprintf(svg,"<circle fill=\"black\" stroke-width=\"%0.3f\" cx=\"%0.3f\" cy=\"%0.3f\" r=\"%0.3f\"/>\n",thickness,x2,y2,rad);
}

void print_resistor(float x1,float y1,float x2,float y2){
	float rad = 2*scale;
	float thickness = 1*scale;
	x1*=scale;
	y1*=scale;
	x2*=scale;
	y2*=scale;
	fprintf(svg,"<circle fill=\"black\" stroke-width=\"%0.3f\" cx=\"%0.3f\" cy=\"%0.3f\" r=\"%0.3f\"/>\n",thickness,x1,y1,rad);
	fprintf(svg,"<polyline fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" points=\"%0.3f,%0.3f %0.3f,%0.3f %0.3f,%0.3f ",thickness,x1,y1,x1+20*scale,y1,x1+25*scale,y1-5*scale);
	int i;
	for(i=1;i<6;i++){
		if(i%2 == 1)fprintf(svg,"%0.3f,%0.3f ",x1+(10*i+25)*scale,y1+5*scale);
		if(i%2 == 0)fprintf(svg,"%0.3f,%0.3f ",x1+(10*i+25)*scale,y1-5*scale);
	}
	fprintf(svg,"%0.3f,%0.3f %0.3f,%0.3f\"/>",x1+80*scale,y1,x2,y2);
	fprintf(svg,"<circle fill=\"black\" stroke-width=\"%0.3f\" cx=\"%0.3f\" cy=\"%0.3f\" r=\"%0.3f\"/>\n",thickness,x2,y2,rad);
}

void print_capacitor(float x1,float y1,float x2,float y2){
	float rad = 2*scale;
	float thickness = 1*scale;
	x1*=scale;
	y1*=scale;
	x2*=scale;
	y2*=scale;
	fprintf(svg,"<circle fill=\"black\" stroke-width=\"%0.3f\" cx=\"%0.3f\" cy=\"%0.3f\" r=\"%0.3f\"/>\n",thickness,x1,y1,rad);
	fprintf(svg,"<polyline fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" points=\"%0.3f,%0.3f %0.3f,%0.3f %0.3f,%0.3f %0.3f,%0.3f\"/>\n",thickness,x1,y1,x1+45*scale,y1,x1+45*scale,y1-10*scale,x1+45*scale,y1+10*scale);
	fprintf(svg,"<polyline fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" points=\"%0.3f,%0.3f %0.3f,%0.3f %0.3f,%0.3f %0.3f,%0.3f\"/>\n",thickness,x1+55*scale,y1-10*scale,x1+55*scale,y1+10*scale,x1+55*scale,y1,x2,y2);
	fprintf(svg,"<circle fill=\"black\" stroke-width=\"%0.3f\" cx=\"%0.3f\" cy=\"%0.3f\" r=\"%0.3f\"/>\n",thickness,x2,y2,rad);
}

void print_inductor(float x1,float y1,float x2,float y2){
	float rad = 2*scale;
	float thickness = 1*scale;
	x1*=scale;
	y1*=scale;
	x2*=scale;
	y2*=scale;
	fprintf(svg,"<circle fill=\"black\" stroke-width=\"%0.3f\" cx=\"%0.3f\" cy=\"%0.3f\" r=\"%0.3f\"/>\n",thickness,x1,y1,rad);
	fprintf(svg,"<line fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" x1=\"%0.3f\" y1=\"%0.3f\" x2=\"%0.3f\" y2=\"%0.3f\"/>\n",thickness,x1,y1,x1+20*scale,y1);
	int i;
	for(i=0;i<6;i++){
		fprintf(svg,"<path fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" d=\"M %0.3f,%0.3f C %0.3f,%0.3f %0.3f,%0.3f %0.3f,%0.3f\"/>\n",thickness,x1+(20+10*i)*scale,y1,x1+(20+10*i)*scale,y1-10*scale,x1+(20+10*(i+1))*scale,y1-10*scale,x1+(20+10*(i+1))*scale,y1);
	}
	fprintf(svg,"<line fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" x1=\"%0.3f\" y1=\"%0.3f\" x2=\"%0.3f\" y2=\"%0.3f\"/>\n",thickness,x1+80*scale,y1,x2,y2);
	fprintf(svg,"<circle fill=\"black\" stroke-width=\"%0.3f\" cx=\"%0.3f\" cy=\"%0.3f\" r=\"%0.3f\"/>\n",thickness,x2,y2,rad);
}

void print_voltagesrc(float x1,float y1,float x2,float y2){
	float rad = 2*scale;
	float thickness = 1*scale;
	x1*=scale;
	y1*=scale;
	x2*=scale;
	y2*=scale;
	fprintf(svg,"<circle fill=\"black\" stroke-width=\"%0.3f\" cx=\"%0.3f\" cy=\"%0.3f\" r=\"%0.3f\"/>\n",thickness,x1,y1,rad);
	fprintf(svg,"<line fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" x1=\"%0.3f\" y1=\"%0.3f\" x2=\"%0.3f\" y2=\"%0.3f\"/>\n",thickness,x1,y1,x1+35*scale,y1);
	fprintf(svg,"<circle fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" cx=\"%0.3f\" cy=\"%0.3f\" r=\"%0.3f\"/>\n",thickness,x1+50*scale,y1,15.0*scale);
	fprintf(svg,"<path fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" d=\"M %0.3f,%0.3f C %0.3f,%0.3f %0.3f,%0.3f %0.3f,%0.3f S %0.3f,%0.3f %0.3f,%0.3f \"/>\n",thickness,x1+40*scale,y1,x1+40*scale,y1-10*scale,x1+50*scale,y1-10*scale,x1+50*scale,y1,x1+60*scale,y1+10*scale,x1+60*scale,y1);
	fprintf(svg,"<line fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" x1=\"%0.3f\" y1=\"%0.3f\" x2=\"%0.3f\" y2=\"%0.3f\"/>\n",thickness,x1+65*scale,y1,x2,y2);
	fprintf(svg,"<circle fill=\"black\" stroke-width=\"%0.3f\" cx=\"%0.3f\" cy=\"%0.3f\" r=\"%0.3f\"/>\n",thickness,x2,y2,rad);
}

void print_currentsrc(float x1,float y1,float x2,float y2){
	float rad = 2*scale;
	float thickness = 1*scale;
	x1*=scale;
	y1*=scale;
	x2*=scale;
	y2*=scale;
	fprintf(svg,"<circle fill=\"black\" stroke-width=\"%0.3f\" cx=\"%0.3f\" cy=\"%0.3f\" r=\"%0.3f\"/>\n",thickness,x1,y1,rad);
	fprintf(svg,"<line fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" x1=\"%0.3f\" y1=\"%0.3f\" x2=\"%0.3f\" y2=\"%0.3f\"/>\n",thickness,x1,y1,x1+35*scale,y1);
	fprintf(svg,"<circle fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" cx=\"%0.3f\" cy=\"%0.3f\" r=\"%0.3f\"/>\n",thickness,x1+50*scale,y1,15.0*scale);
	fprintf(svg,"<line fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" x1=\"%0.3f\" y1=\"%0.3f\" x2=\"%0.3f\" y2=\"%0.3f\"/>\n",thickness,x1+40*scale,y1,x1+60*scale,y1);
	fprintf(svg,"<polyline fill=\"black\" stroke=\"black\" stroke-width=\"%0.3f\" points=\"%0.3f,%0.3f %0.3f,%0.3f %0.3f,%0.3f\"/>\n",thickness,x1+60*scale,y1,x1+55*scale,y1-5*scale,x1+55*scale,y1+5*scale);
	fprintf(svg,"<line fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" x1=\"%0.3f\" y1=\"%0.3f\" x2=\"%0.3f\" y2=\"%0.3f\"/>\n",thickness,x1+65*scale,y1,x2,y2);
	fprintf(svg,"<circle fill=\"black\" stroke-width=\"%0.3f\" cx=\"%0.3f\" cy=\"%0.3f\" r=\"%0.3f\"/>\n",thickness,x2,y2,rad);
}

/*void print_text(char* netX,char* netY,char* value){
	fprintf(svg,"<text stroke-width=\"%0.3f\" font-size=\"%0.3fpx\">",);
}*/

void add_comp(char type,int start,int end,char* value){
	nets_start[start] = nets_start[start] == -1 ? level : nets_start[start];
	nets_start[end] = nets_start[end] == -1 ? level : nets_start[end];
	nets_end[start] = level;
	nets_end[end] = level;
	level++;
	switch(type){
		case 'R':
			print_resistor(40+start*100,level*50,40+end*100,level*50);
			break;
		case 'C':
			print_capacitor(40+start*100,level*50,40+end*100,level*50);
			break;
		case 'L':
			print_inductor(40+start*100,level*50,40+end*100,level*50);
			break;
		case 'I':
			print_currentsrc(40+start*100,level*50,40+end*100,level*50);
			break;
		case 'V':
			print_voltagesrc(40+start*100,level*50,40+end*100,level*50);
			break;
		default:
			print_line(40+start*100,level*50,40+end*100,level*50);
			break;
	}
}

void build_net(){
	int i;
	for(i=0;i<total_nets;i++){
		print_line(40+i*100,50+nets_start[i]*50,40+i*100,50+nets_end[i]*50);
		closed[i] = nets_start[i] == nets_end[i] ? 0 : 1;
	}
}

int main(){
	remove("svg_output.svg");
	level = 0;
	svg = fopen("svg_output.svg","a");
	nets_start = (int*)malloc(sizeof(int)*100);
	nets_end = (int*)malloc(sizeof(int)*100);
	closed = (int*)malloc(sizeof(int)*100);
	comps = (component*)malloc(sizeof(component)*1000);
	int i;
	for(i=0;i<100;i++){
		nets_end[i] = 0;
		nets_start[i] = -1;
		closed[i] = 0;
	}
	fprintf(svg,"<svg xmlns=\"http://www.w3.org/2000/svg\" height=\"%d\" width=\"%d\">\n",5000,5000);
	comps[0].type = 'R';
	comps[0].start = 0;
	comps[0].end = 1;
	comps[0].value = "100";
	add_comp(comps[0].type,comps[0].start,comps[0].end,comps[0].value);
	comps[1].type = 'C';
	comps[1].start = 0;
	comps[1].end = 2;
	comps[1].value = "100";
	add_comp(comps[1].type,comps[1].start,comps[1].end,comps[1].value);
	comps[2].type = 'L';
	comps[2].start = 2;
	comps[2].end = 3;
	comps[2].value = "100";
	//printf("%d -- %d,%d - %d,%d\n",level,nets_start[2],nets_start[3],nets_end[2],nets_end[3]);
	add_comp(comps[2].type,comps[2].start,comps[2].end,comps[2].value);
	//printf("%d -- %d,%d - %d,%d\n",level,nets_start[2],nets_start[3],nets_end[2],nets_end[3]);
	comps[3].type = 'V';
	comps[3].start = 3;
	comps[3].end = 4;
	comps[3].value = "100";
	add_comp(comps[3].type,comps[3].start,comps[3].end,comps[3].value);
	comps[4].type = 'R';
	comps[4].start = 1;
	comps[4].end = 5;
	comps[4].value = "100";
	add_comp(comps[4].type,comps[4].start,comps[4].end,comps[4].value);
	comps[5].type = 'R';
	comps[5].start = 5;
	comps[5].end = 6;
	comps[5].value = "100";
	add_comp(comps[5].type,comps[5].start,comps[5].end,comps[5].value);
	comps[6].type = 'C';
	comps[6].start = 6;
	comps[6].end = 7;
	comps[6].value = "100";
	add_comp(comps[6].type,comps[6].start,comps[6].end,comps[6].value);
	comps[7].type = 'L';
	comps[7].start = 7;
	comps[7].end = 8;
	comps[7].value = "100";
	add_comp(comps[7].type,comps[7].start,comps[7].end,comps[7].value);
	comps[8].type = 'I';
	comps[8].start = 4;
	comps[8].end = 8;
	comps[8].value = "100";
	add_comp(comps[8].type,comps[8].start,comps[8].end,comps[8].value);
	/*comps[9].type = 'R';
	comps[9].start = 0;
	comps[9].end = 1;
	comps[9].value = "100";
	add_comp(comps[9].type,comps[9].start,comps[9].end,comps[9].value);
	comps[10].type = 'R';
	comps[10].start = 0;
	comps[10].end = 1;
	comps[10].value = "100";
	add_comp(comps[10].type,comps[10].start,comps[10].end,comps[10].value);
	comps[11].type = 'R';
	comps[11].start = 0;
	comps[11].end = 1;
	comps[11].value = "100";
	add_comp(comps[11].type,comps[11].start,comps[11].end,comps[11].value);*/
	total_nets = 9;
	build_net();
	for(i=0;i<total_nets;i++) if(closed[i] == 0) printf("Open circuit\n");
	fprintf(svg,"</svg>\n");
	return 0;
}