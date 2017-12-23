#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define length 100.000

#define width 20.0000

typedef struct 
{
	float x,y;
	
}cordi;


typedef struct 
{
	char name[50];
	int pos;
	
}nets;

float max(float a,float b){
	if(a>b){
		return a;
	}
	else
		return b;
}
float min(float a,float b){
	if(a<b){
		return a;
	}
	else
		return b;
}
void update(cordi c[],float dx,float dy,int a){
	for (int i = 0; i < a; i++)
	{
		c[i].x=c[i].x+dx;
		
		c[i].y=c[i].y+dy;
	}


	return;

}

void drawline(char* x,cordi a,cordi b){
	//printf("x\n");
	char s[2000];
	char s1[2000];
	sprintf(s,"<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"2\" stroke=\"black\" />\n",a.x,a.y,b.x,b.y);
	//printf("reached2%s\n",x);
	strcat(x,s);
	
	return ;
}


void translate(char* x,float dx,float dy){
	char* t1;
	t1=(char *)malloc(sizeof(x));
	sprintf(t1,"<g transform=\"translate(%f,%f)\">\n",dx,dy);
	char t2[10] = "\n</g>";
	strcat(t1,x);
	strcat(t1,t2);
	strcpy(x,t1);
	return ;
}
void rotate90c(char* x){
	char* t1;
	t1=(char *)malloc(sizeof(x));
	sprintf(t1,"<g transform=\"rotate(90,%f,%f)\">\n",width/2,width/2);
	char t2[10] = "\n</g>";
	strcat(t1,x);
	strcat(t1,t2);
	strcpy(x,t1);
	return ;
}



void rotate180c(char* x){
	translate(x,length,0);
	char* t1;
	t1=(char *)malloc(sizeof(x));
	sprintf(t1,"<g transform=\"rotate(180,%f,%f)\">\n",length+width/2,width/2);
	char t2[10] = "\n</g>";
	strcat(t1,x);
	strcat(t1,t2);
	strcpy(x,t1);
	return ;
}


void putup(char* comp,char* blackbox,cordi toput){
	rotate90c(comp);
	translate(blackbox,0,length);
	translate(comp,toput.x-width/2,0);


	strcat(blackbox,comp);
	return;

}

void putdr(char* comp,char* blackbox,cordi toput){
	translate(comp,toput.x-width/2,toput.y-width/2);
	
	strcat(blackbox,comp);
	return;

}


void putleft(char* comp,char* blackbox,cordi toput){
	translate(blackbox,length,0);
	translate(comp,0,toput.y-width/2);


	strcat(blackbox,comp);
	return;


}



void drawdown(char* x,cordi a,cordi b){
	
	cordi temp;
	
		temp.x=a.x;
		temp.y=max(b.y,a.y)+length;
		drawline(x,a,temp);
		//printf("dsads%s\n", x);
		temp.x=b.x;
		
		//printf("dsadadaffdafhsvk\n");
		drawline(x,b,temp);

		cordi temp2;
		temp2.y=temp.y;
		temp2.x =temp.x+(a.x-b.x)+length;
		drawline(x,temp,temp2);
		return;
	

}

void drawup(char* x,cordi a,cordi b){
	//printf("%f %f %f %f\n",a.x,a.y,b.x,b.y );
			
	translate(x,0,length);
	a.y=a.y+length;
	b.y=b.y+length;
	cordi temp;
		temp.x=a.x;
		temp.y=min(b.y,a.y)-length;
		drawline(x,a,temp);
		//printf("dsads%s\n", x);
		temp.x=b.x;
		temp.y=min(b.y,a.y)-length;
		//printf("dsadadaffdafhsvk\n");
		drawline(x,b,temp);
		
		cordi temp2;
		temp2.y=temp.y;
		temp2.x =temp.x+(a.x-b.x)+length;
		drawline(x,temp,temp2);
		return;

	

}



void drawright(char* x,cordi a,cordi b){

	
	cordi temp;
	
		temp.y=a.y;
		temp.x=max(b.x,a.x)+length;
		drawline(x,a,temp);
		temp.y=b.y;
		temp.x=max(b.x,a.x)+length;
		drawline(x,b,temp);
		cordi temp2;
		temp2.x=temp.x;
		temp2.y =temp.y+(a.y-b.y)+length;
		drawline(x,temp,temp2);
		
		return;

	

}



void drawleft(char* x,cordi a,cordi b){

	translate(x,length,0);	
	cordi temp;
	
		temp.y=a.y;
		temp.x=min(b.x,a.x)-length;
		drawline(x,a,temp);
		temp.y=b.y;
		temp.x=min(b.x,a.x)-length;
		drawline(x,b,temp);
				cordi temp2;
		temp2.x=temp.x;
		temp2.y =temp.y+(a.y-b.y)+length;
		drawline(x,temp,temp2);

		return;
	

}



void print_resistor(char *x,float start_x,float start_y,float end_x,float end_y,float height,float scale){
	char* temp;
	temp = (char *)malloc(2000);
	start_x*=scale;
	start_y*=scale;
	end_x*=scale;
	end_y*=scale;
	height*=scale;
	int horiz_check = start_x == end_x ? 0 : 1;
	int i;
	int len = horiz_check == 1 ? (end_x - start_x - 50*scale)/height : (end_y - start_y - 50*scale)/height;
	sprintf(temp,"<circle cx=\"%f\" cy=\"%f\" r=\"2\" fill=\"red\"/>",start_x,start_y);
	strcat(x,temp);
	
	strcat(x,"<polyline fill=\"none\" stroke=\"black\" points=\"");
	sprintf(temp,"%0.3f,%0.3f %0.3f,%0.3f %0.3f,%0.3f ",start_x,start_y,(start_x+height*2*horiz_check),(start_y+height*2*(1-horiz_check)),(start_x+height*2.5*horiz_check+(height/2)*(1-horiz_check)),(start_y+height*2.5*(1-horiz_check)-(height/2)*horiz_check));
	
	strcat(x,temp);
	for(i=1;i<=len;i++){
		if(i%2 == 1) {sprintf(temp,"%0.3f,%0.3f ",(start_x+height*(2.5+i)*horiz_check-(height/2)*(1-horiz_check)),(start_y+height*(2.5+i)*(1-horiz_check)+(height/2)*horiz_check));
		strcat(x,temp);}		
		if(i%2 == 0) {sprintf(temp,"%0.3f,%0.3f ",(start_x+height*(2.5+i)*horiz_check+(height/2)*(1-horiz_check)),(start_y+height*(2.5+i)*(1-horiz_check)-(height/2)*horiz_check));
		strcat(x,temp);}
	}
	sprintf(temp,"%0.3f,%0.3f %0.3f,%0.3f %0.3f,%0.3f",(end_x-height*2.5*horiz_check-(height/2)*(1-horiz_check)),(end_y-height*2.5*(1-horiz_check)+(height/2)*horiz_check),(end_x-height*2*horiz_check),(end_y-height*2*(1-horiz_check)),end_x,end_y);
	strcat(x,temp);
	strcat(x,"\"/>\n");
	sprintf(temp,"<circle cx=\"%f\" cy=\"%f\" r=\"2\" fill=\"red\"/>",end_x,end_y);
	strcat(x,temp);
	
	return;
}



void print_capacitor(char* x,float x1,float y1,float x2,float y2,float scale){
	float rad = 2*scale;
	float thickness = 1*scale;
	x1*=scale;
	y1*=scale;
	x2*=scale;
	y2*=scale;
	char* temp;
	temp = (char *)malloc(2000);
	sprintf(temp,"<circle fill=\"red\" stroke-width=\"%0.3f\" cx=\"%0.3f\" cy=\"%0.3f\" r=\"%0.3f\"/>\n",thickness,x1,y1,rad);
	strcat(x,temp);
	sprintf(temp,"<polyline fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" points=\"%0.3f,%0.3f %0.3f,%0.3f %0.3f,%0.3f %0.3f,%0.3f\"/>\n",thickness,x1,y1,x1+45*scale,y1,x1+45*scale,y1-10*scale,x1+45*scale,y1+10*scale);
	strcat(x,temp);
	
	sprintf(temp,"<polyline fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" points=\"%0.3f,%0.3f %0.3f,%0.3f %0.3f,%0.3f %0.3f,%0.3f\"/>\n",thickness,x1+55*scale,y1-10*scale,x1+55*scale,y1+10*scale,x1+55*scale,y1,x2,y2);
	strcat(x,temp);
	
	sprintf(temp,"<circle fill=\"red\" stroke-width=\"%0.3f\" cx=\"%0.3f\" cy=\"%0.3f\" r=\"%0.3f\"/>\n",thickness,x2,y2,rad);
	strcat(x,temp);
	
}


void print_inductor(char* x,float x1,float y1,float x2,float y2,float scale){
	float rad = 2*scale;
	float thickness = 1*scale;
	x1*=scale;
	y1*=scale;
	x2*=scale;
	y2*=scale;
	char* temp;
	temp = (char *)malloc(2000);
	
	sprintf(temp,"<circle fill=\"red\" stroke-width=\"%0.3f\" cx=\"%0.3f\" cy=\"%0.3f\" r=\"%0.3f\"/>\n",thickness,x1,y1,rad);
	strcat(x,temp);
	sprintf(temp,"<line fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" x1=\"%0.3f\" y1=\"%0.3f\" x2=\"%0.3f\" y2=\"%0.3f\"/>\n",thickness,x1,y1,x1+20*scale,y1);
	strcat(x,temp);
	
	int i;
	for(i=0;i<6;i++){
		sprintf(temp,"<path fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" d=\"M %0.3f,%0.3f C %0.3f,%0.3f %0.3f,%0.3f %0.3f,%0.3f\"/>\n",thickness,x1+(20+10*i)*scale,y1,x1+(20+10*i)*scale,y1-10*scale,x1+(20+10*(i+1))*scale,y1-10*scale,x1+(20+10*(i+1))*scale,y1);
		strcat(x,temp);
	
	}
	sprintf(temp,"<line fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" x1=\"%0.3f\" y1=\"%0.3f\" x2=\"%0.3f\" y2=\"%0.3f\"/>\n",thickness,x1+80*scale,y1,x2,y2);
	strcat(x,temp);
	sprintf(temp,"<circle fill=\"red\" stroke-width=\"%0.3f\" cx=\"%0.3f\" cy=\"%0.3f\" r=\"%0.3f\"/>\n",thickness,x2,y2,rad);
	strcat(x,temp);
	
}

void print_voltagesrc(char* x,float x1,float y1,float x2,float y2,float scale){
	float rad = 2*scale;
	float thickness = 1*scale;
	x1*=scale;
	y1*=scale;
	x2*=scale;
	y2*=scale;
	char* temp;
	temp = (char *)malloc(2000);
	
	sprintf(temp,"<circle fill=\"red\" stroke-width=\"%0.3f\" cx=\"%0.3f\" cy=\"%0.3f\" r=\"%0.3f\"/>\n",thickness,x1,y1,rad);
	strcat(x,temp);
	
	sprintf(temp,"<line fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" x1=\"%0.3f\" y1=\"%0.3f\" x2=\"%0.3f\" y2=\"%0.3f\"/>\n",thickness,x1,y1,x1+35*scale,y1);
	strcat(x,temp);
	sprintf(temp,"<circle fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" cx=\"%0.3f\" cy=\"%0.3f\" r=\"%0.3f\"/>\n",thickness,x1+50*scale,y1,15.0*scale);
	strcat(x,temp);
	sprintf(temp,"<path fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" d=\"M %0.3f,%0.3f C %0.3f,%0.3f %0.3f,%0.3f %0.3f,%0.3f S %0.3f,%0.3f %0.3f,%0.3f \"/>\n",thickness,x1+40*scale,y1,x1+40*scale,y1-10*scale,x1+50*scale,y1-10*scale,x1+50*scale,y1,x1+60*scale,y1+10*scale,x1+60*scale,y1);
	strcat(x,temp);
	sprintf(temp,"<line fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" x1=\"%0.3f\" y1=\"%0.3f\" x2=\"%0.3f\" y2=\"%0.3f\"/>\n",thickness,x1+65*scale,y1,x2,y2);
	strcat(x,temp);
	sprintf(temp,"<circle fill=\"red\" stroke-width=\"%0.3f\" cx=\"%0.3f\" cy=\"%0.3f\" r=\"%0.3f\"/>\n",thickness,x2,y2,rad);
	strcat(x,temp);
	
}


void print_currentsrc(char* x,float x1,float y1,float x2,float y2,float scale){
	float rad = 2*scale;
	float thickness = 1*scale;
	x1*=scale;
	y1*=scale;
	x2*=scale;
	y2*=scale;
	char* temp;
	temp = (char *)malloc(2000);
	
	sprintf(temp,"<circle fill=\"red\" stroke-width=\"%0.3f\" cx=\"%0.3f\" cy=\"%0.3f\" r=\"%0.3f\"/>\n",thickness,x1,y1,rad);
	strcat(x,temp);
	sprintf(temp,"<line fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" x1=\"%0.3f\" y1=\"%0.3f\" x2=\"%0.3f\" y2=\"%0.3f\"/>\n",thickness,x1,y1,x1+35*scale,y1);
	strcat(x,temp);
	sprintf(temp,"<circle fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" cx=\"%0.3f\" cy=\"%0.3f\" r=\"%0.3f\"/>\n",thickness,x1+50*scale,y1,15.0*scale);
	strcat(x,temp);
	sprintf(temp,"<line fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" x1=\"%0.3f\" y1=\"%0.3f\" x2=\"%0.3f\" y2=\"%0.3f\"/>\n",thickness,x1+40*scale,y1,x1+60*scale,y1);
	strcat(x,temp);
	sprintf(temp,"<polyline fill=\"black\" stroke=\"black\" stroke-width=\"%0.3f\" points=\"%0.3f,%0.3f %0.3f,%0.3f %0.3f,%0.3f\"/>\n",thickness,x1+60*scale,y1,x1+55*scale,y1-5*scale,x1+55*scale,y1+5*scale);
	strcat(x,temp);
	sprintf(temp,"<line fill=\"none\" stroke=\"black\" stroke-width=\"%0.3f\" x1=\"%0.3f\" y1=\"%0.3f\" x2=\"%0.3f\" y2=\"%0.3f\"/>\n",thickness,x1+65*scale,y1,x2,y2);
	strcat(x,temp);
	sprintf(temp,"<circle fill=\"red\" stroke-width=\"%0.3f\" cx=\"%0.3f\" cy=\"%0.3f\" r=\"%0.3f\"/>\n",thickness,x2,y2,rad);
	strcat(x,temp);
	
}

void addetxt(char x[],char name[],char vals[]){
	char* temp;
	temp = (char *)malloc(2000);
	sprintf(temp,"<text x=\"%f\" y=\"%f\" font-size=\"10px\">\n<tspan>%s</tspan>\n<tspan>%s</tspan>\n</text>\n",(length-width)/2,2*width,name,vals);
	strcat(x,temp);

}

void pnets(char* x,nets n[],cordi c[],int size){
	for (int i = 0; i < size; i++)
	{
		char* temp;
		temp = (char *)malloc(2000);
		sprintf(temp,"<text x=\"%f\" y=\"%f\" font-size=\"10px\">\n<tspan>%s</tspan>\n</text>\n",c[i].x,c[i].y,n[i].name);
		strcat(x,temp);
	}
	
}

void pres(char* x,char* name,char* vals){

	print_resistor(x,width/2,width/2,width/2+length,width/2,width/2,1);
	addetxt(x,name,vals);

}



void pcap(char* x,char* name,char* vals){
	
	print_capacitor(x,width/2,width/2,width/2+length,width/2,1);
	addetxt(x,name,vals);
}

void pind(char* x,char* name,char* vals){
	print_inductor(x,width/2,width/2,width/2+length,width/2,1);
	addetxt(x,name,vals);
}


void pvol(char* x,char* name,char* vals){
	print_voltagesrc(x,width/2,width/2,width/2+length,width/2,1);
	addetxt(x,name,vals);
}

void pcs(char* x,char* name,char* vals){
	print_currentsrc(x,width/2,width/2,width/2+length,width/2,1);
	addetxt(x,name,vals);
}




int getnet(char* name,nets x[],int* size){
	int s=*size;
	for (int i = 0; i < s; i++)
	{
		if(strcmp(name,x[i].name)==0)
			return i;
	}

	
	return -1;

}


void addnet(char* name,nets x[],int* size){
	int s=*size;
	//printf("s1=%d\n",s);
	nets temp;
	strcpy(temp.name,name);
	temp.pos=s;
	x[s]=temp;
	s++;
	//printf("s2=%d\n",s);
	*size=*size+1;
	//printf("size=%d\n",*size);
	return;
}


int addcomponent(char* blackbox,char* comp,char* a,char* b,nets ns[],cordi vals[],int* size){
	
	//printf("a is %s\n", a);
	//printf("a is %s\n", b);
	int s=*size;
	int ap=1;
	int bp=1;
	int ax,bx;
	cordi atemp;
	cordi btemp;
	if(getnet(a,ns,size)==-1){
		ap=0;
		addnet(a,ns,size);
		ax=s;
	}
	else{
		atemp=vals[getnet(a,ns,size)];
		ax=getnet(a,ns,size);
	}
	if(getnet(b,ns,size)==-1){
		bp=0;
		addnet(b,ns,size);
	
	}
	else{
		btemp=vals[getnet(b,ns,size)];
		bx=getnet(b,ns,size);
	}

	if(ap==1 && bp ==1){
		if(atemp.x>btemp.x || atemp.y<btemp.y){
			rotate180c(comp);
			cordi temp=atemp;
			atemp=btemp;
			btemp=temp;
			int ti=ax;
			ax=bx;
			bx=ti;
		}
		if(atemp.x>width/2 && atemp.y>width/2 && btemp.y>width/2 && btemp.x>width/2){
			//printf("reached4\n");
			drawdown(blackbox,atemp,btemp);
			atemp.y=max(atemp.y,btemp.y)+length;
			btemp.y=atemp.y;
			vals[ax]=atemp;
			vals[bx]=btemp;
			putdr(comp,blackbox,atemp);
			
			return 1;/* drawdown/right*/
		}

		if(atemp.x==width/2 && btemp.x==width/2){
			drawleft(blackbox,atemp,btemp);
			update(vals,length,0,*size);
			//printf("reached3\n");
			
				rotate90c(comp);
				translate(comp,0,atemp.y-width/2);
				strcat(blackbox,comp);
				atemp.x=width/2;
				btemp.x=atemp.x;
				vals[ax]=atemp;
				vals[bx]=btemp;

			
			

			return 2;/*drawleft*/
		}
		if(atemp.y==width/2 && btemp.y==width/2){
			//printf("reached\n");
			drawup(blackbox,atemp,btemp);
			update(vals,0,length,*size);

			
				//rotate90c(comp);
			//printf("%f %f %f %f\n",atemp.x,atemp.y,btemp.x,btemp.y );
			
				atemp.y=width/2;
				btemp.y=atemp.y;
				vals[ax]=atemp;
				vals[bx]=btemp;
				translate(comp,atemp.x-width/2,0);
				strcat(blackbox,comp);

			
			return 3; /*drawup*/
		}


		if(atemp.x==width/2 && btemp.x>width/2){
			//printf("reached2\n");
			drawdown(blackbox,atemp,btemp);
			translate(comp,0,atemp.y+length-width/2);
			strcat(blackbox,comp);
			atemp.y=max(atemp.y,btemp.y)+length;
			btemp.y=atemp.y;
			vals[ax]=atemp;
			vals[bx]=btemp;

			
			return 7;
		}


		if(btemp.x==width/2 && atemp.x>width/2){
			//printf("reached1\n");
			rotate180c(comp);
			drawdown(blackbox,atemp,btemp);
			translate(comp,0,atemp.y-width/2);
			strcat(blackbox,comp);
			atemp.y=max(atemp.y,btemp.y)+length;
			btemp.y=atemp.y;
			vals[ax]=atemp;
			vals[bx]=btemp;

			return 8;
			

		}

		
		if(atemp.y==width/2 && btemp.y>width/2){
			//printf("reached6\n");
			drawup(blackbox,atemp,btemp);
			atemp.y=width/2;
			btemp.y=atemp.y;
			update(vals,0,length,s);
			vals[ax]=atemp;
			vals[bx]=btemp;

			//rotate90c(comp);
			//printf("%f %f %f %f\n",atemp.x,atemp.y,btemp.x,btemp.y );
			translate(comp,atemp.x-width/2,atemp.y-width/2);
			strcat(blackbox,comp);
			
			return 9; /*drawup*/
		}

		if(btemp.y==width/2 && atemp.y>width/2){
			//printf("reached7\n");
			rotate180c(comp);
			drawright(blackbox,atemp,btemp);
			rotate90c(comp);
			translate(comp,atemp.x-width/2,0);
			strcat(blackbox,comp);
			atemp.y=max(atemp.y,btemp.y)+length;
			btemp.y=atemp.y;
			vals[ax]=atemp;
			vals[bx]=btemp;

			return 9; /*drawup*/
		}

	}

	if(ap==0){
		if(btemp.x==width/2){
			//printf("reached15\n");
		
			putleft(comp,blackbox,btemp);
			update(vals,length,0,*size);
			atemp.x=btemp.x;
			atemp.y=btemp.y;
			vals[s]=atemp;
			
			return 4;/*putleft*/

			
		}

		if(btemp.y==width/2){
			//rotate90c(comp);

			//printf("reached13\n");
			update(vals,0,length,*size);
			atemp.x=btemp.x;
			atemp.y=width/2;
			vals[s]=atemp;
			
			putup(comp,blackbox,btemp);
			return 5;/*puttop*/
		}

		//printf("reached14\n");
		rotate180c(comp);
		cordi temp=btemp;
		temp.y=temp.y+length;
		drawline(blackbox,temp,btemp);
		
		putdr(comp,blackbox,temp);
		//printf("dsa%s\n", comp);
		//printf("%s\n", blackbox);
		
		atemp=temp;
		atemp.x=temp.x+length;
		vals[bx]=temp;
		vals[s]=atemp;
		
		return 10;
	}

	if(bp==0){
		//printf("fdhsiuafh\n");
		//rotate180c(comp);	
		if(atemp.y==width/2){
			//printf("reached12\n");
			//atemp=atemp;
			cordi temp=atemp;
			temp.y=atemp.y+length;
			translate(blackbox,0,length);
			drawline(blackbox,atemp,temp);
			strcat(blackbox,comp);
			update(vals,0,length,*size);
			btemp.x=atemp.x+length;
			atemp.y=width/2;
			btemp.y=atemp.y;
			//vals[s]=btemp;
			
			vals[ax]=atemp;
			vals[s]=btemp;
			return 4;/*putleft*/

			
		}

		if(atemp.x==width/2){
			rotate90c(comp);
			//printf("reached13\n");
			//atemp=atemp;
			btemp.x=atemp.x;
			btemp.y=atemp.y+length;
			cordi temp=atemp;
			temp.x=atemp.x+length;
			translate(blackbox,length,0);
			drawline(blackbox,atemp,temp);
			update(vals,length,0,*size);
			vals[ax]=atemp;
			vals[s]=btemp;
			return 4;/*putleft*/

			
		}

		cordi temp=atemp;
		temp.y=temp.y+length;
		drawline(blackbox,temp,atemp);
	

		
		putdr(comp,blackbox,temp);
		btemp=temp;
		btemp.x=atemp.x+length;
		vals[s]=btemp;
		vals[ax]=temp;
		return 10;
	}


	


}
/*
void addcomponent(char* x,int code)
**/


/*
int main(){

	cordi temp;
	temp.x=width/2;
	temp.y=width/2;

	cordi temp2;
	temp2.x=width/2+length;
	temp2.y=width/2;

	char x[200000]="";
	char res1[1000]="";
	char res2[1000]="";
	char res3[1000]="";
	char res4[1000]="";
	char res5[1000]="";
	char res6[1000]="";
	char res7[1000]="";
	char res8[1000]="";
	char res9[1000]="";
	char res10[1000]="";
	
	pres(res1);
	pres(res2);
	pcap(res3);
	pcap(res4);
	pvol(res5);

	pcs(res6);
	pind(res7);
	pcap(res8);
	pcs(res9);
	pres(res10);
	cordi temp3;
	temp3.x=20;
	temp3.y=20;
	nets tn[10];
	cordi cs[10];
	pres(x);

	char y[2000]="";
	//printf("%s\n", y);
	char n1[10]="net1";
	char n2[10]="net2";
	char n3[10]="net3";
	char n4[10]="net4";
	char n5[10]="net5";
	char n6[10]="net6";
	char n7[10]="net7";
	char n8[10]="net8";
	char n9[10]="net9";
	char n0[10]="net0";
	
	
	int size=0;
	cs[0]=temp;
	cs[1]=temp2;
	addnet(n3,tn,&size);
	addnet(n9,tn,&size);
	//printf("%d\n",getnet(n2,tn,&size) );

	printf("<svg xmlns=\"http://www.w3.org/2000/svg\" height=\"1000\" width=\"1000\">\n");
	//printf("%s\n",drawline(x,temp,temp2) );
	//drawline(x,temp,temp2);
	//drawright(x,temp,temp2);
	//addcomponent(x,res2,n1,n2,tn,cs,&size);
	//addcomponent(x,res1,n3,n9,tn,cs,&size);
	
	addcomponent(x,res4,n2,n3,tn,cs,&size);
	addcomponent(x,res2,n1,n2,tn,cs,&size);
	addcomponent(x,res3,n1,n0,tn,cs,&size);
	//printf("bdha%d\n",getnet(n9,tn,&size) );

	addcomponent(x,res5,n9,n4,tn,cs,&size);
	addcomponent(x,res6,n4,n5,tn,cs,&size);
	addcomponent(x,res8,n5,n8,tn,cs,&size);
	addcomponent(x,res9,n8,n6,tn,cs,&size);
	addcomponent(x,res10,n6,n0,tn,cs,&size);
	addcomponent(x,res7,n7,n0,tn,cs,&size);

	
	//pres(x);
	//rotate90c(x);
	//translate(x,length,0);
	//drawleft(x,temp,temp2);
	//pres(y);
	//addcomponent();
	//rota90c(y);
	//strcat(x,y);
	//translate(x,length,0);
	//pres(x);
	//drawline(y,)
	printf("%s\n",x);
	printf("</svg>\n");


}

*/








