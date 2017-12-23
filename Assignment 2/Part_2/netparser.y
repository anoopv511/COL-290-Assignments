%{

#include <stdio.h>
#include <string.h>
#include "funcs.h"
#include "solver.h"

char circuit[20000000]="";
nets allnets[100000];
cordi allc[1000000];
int no[1000000];
double freq[1000000];
int fs=0;

char temp[10000];
int size=0;
  void yyerror(const char *str){
    
    fprintf(stderr,"ERROR: %s \n",str);
    
  }
   int yylex(void);
    extern FILE* yyin;
    FILE* out;
    FILE* results;
net v[100000];
element e[1000000];
int vs=0;
int es=0;    



     
%}
%token COMMENT
%union {

  
  char *string;
  int   value;
  float fval;
}

%token <string> RESISTOR

%token <string> NAME
%token <string> SINE
%token <string> CAPACITOR
%token <string> INDUCTOR
%token <string> vol
%token <string> isrc
%token <string> LP
%token <string> RP
%token <string> FREQ
%token <string> TIME



%%



valid_entries:/*empty*/
| valid_entries valid_entry
//printf("10\n");}

;


valid_entry:


voltage_source |
current_source |
resistor |
capacitor |
inductor |
comment
;



voltage_source:
vol NAME NAME SINE LP RESISTOR RESISTOR FREQ TIME  RP
                                              {

                                                        //printf("fdgafadgshad\n");
                                                      if(size==0){
                                                        cordi ctemp;
                                                        ctemp.x=width/2;
                                                        ctemp.y=width/2;

                                                        cordi temp2;
                                                        temp2.x=width/2+length;
                                                        temp2.y=width/2;
                                                        allc[0]=ctemp;
                                                        allc[1]=temp2;
                                                        addnet($2,allnets,&size);
                                                        addnet($3,allnets,&size);
                                                        pvol(circuit,$1,$4);
                                                      }

                                                      else{
                                                      char n[100000];
                                                      strcat(n,$4);
                                                      strcat(n,$5);
                                                      strcat(n,$6);
                                                      strcat(n,$7);
                                                      strcat(n,$8);
                                                      strcat(n,$9);
                                                      strcat(n,$10);
                                                      pvol(temp,$1,n);

                                                      addcomponent(circuit,temp,$2,$3,allnets,allc,&size);
                                                      strcpy(temp,"");
                                                      //printf("%s\n",temp );
                                                                                                          strcpy(temp,"");
                                                     // //printf("%s\n",temp );

                                                      }
                                                      no[getnet($2,allnets,&size)]=no[getnet($2,allnets,&size)]+1;
                                                      no[getnet($3,allnets,&size)]=no[getnet($3,allnets,&size)]+1;
                                                      
                                                                  element temp;
                                                                  temp.type='V';
                                                                  strcpy(temp.name,$1);
                                                                  gaddnet($2,v,&vs);
                                                                  gaddnet($3,v,&vs);                                                                  
                                                                  char zero[2]="0";
                                                                  if(strcmp($2,zero)!=0){
                                                                    temp.net1=netpos($2,v,vs);
                                                                    v[netpos($2,v,vs)].outsize++;
                                                                    v[netpos($2,v,vs)].outgoing[v[netpos($2,v,vs)].outsize-1]=es;
                                                                    
                                                                  }

                                                                  if(strcmp($3,zero)!=0){
                                                                    temp.net2=netpos($3,v,vs); 
                                                                    v[netpos($3,v,vs)].insize++;
                                                                    v[netpos($3,v,vs)].ingoing[v[netpos($3,v,vs)].insize-1]=es;
                                                                    
                                                                  }
                                                                  
                                                                  
                                                                  temp.valdc=getval($6);

                                                                 // //printf("check =%s",$7);
                                                                  temp.value=getval($7);
                                                                  reduce($8,2);

                                                                  temp.freq=getval($8);
                                                                  addfreq(temp.freq,freq,&fs);
                                                                  reduce($9,1);
                                                                  if(temp.valdc!=0){
                                                                    addfreq(0,freq,&fs);
                                                                  }
                                                                  temp.delay=getval($9);
                                                                  e[es]=temp; 

                                                                  es++;
                                                                  //printf("es=%d",es);


                                              }
;

| vol NAME NAME SINE LP RESISTOR RESISTOR FREQ TIME RESISTOR RP 
                                              {

                                                        ////printf("fdgafadgshad\n");
                                                      if(size==0){
                                                        cordi ctemp;
                                                        ctemp.x=width/2;
                                                        ctemp.y=width/2;

                                                        cordi temp2;
                                                        temp2.x=width/2+length;
                                                        temp2.y=width/2;
                                                        allc[0]=ctemp;
                                                        allc[1]=temp2;
                                                        addnet($2,allnets,&size);
                                                        addnet($3,allnets,&size);
                                                        pvol(circuit,$1,$4);
                                                      }
                                                      else{
                                                      char n[100000];
                                                      strcat(n,$4);
                                                      strcat(n,$5);
                                                      strcat(n,$6);
                                                      strcat(n,$7);
                                                      strcat(n,$8);
                                                      strcat(n,$9);
                                                      strcat(n,$10);
                                                      strcat(n,$11);
                                                      pvol(temp,$1,n);                                                      
                                                      addcomponent(circuit,temp,$2,$3,allnets,allc,&size);
                                                      strcpy(temp,"");
                                                      //printf("%s\n",temp );
                                                                                                          
                                                      strcpy(temp,"");
                                                     // //printf("%s\n",temp );

                                                      }
                                                      no[getnet($2,allnets,&size)]=no[getnet($2,allnets,&size)]+1;
                                                      no[getnet($3,allnets,&size)]=no[getnet($3,allnets,&size)]+1;
                                                      
                                                                  element temp;
                                                                  temp.type='V';
                                                                  strcpy(temp.name,$1);
                                                                  gaddnet($2,v,&vs);
                                                                  gaddnet($3,v,&vs);                                                                  
                                                                  char zero[2]="0";
                                                                  if(strcmp($2,zero)!=0){
                                                                    temp.net1=netpos($2,v,vs);
                                                                    v[netpos($2,v,vs)].outsize++;
                                                                    v[netpos($2,v,vs)].outgoing[v[netpos($2,v,vs)].outsize-1]=es;
                                                                    
                                                                  }

                                                                  if(strcmp($3,zero)!=0){
                                                                    temp.net2=netpos($3,v,vs); 
                                                                    v[netpos($3,v,vs)].insize++;
                                                                    v[netpos($3,v,vs)].ingoing[v[netpos($3,v,vs)].insize-1]=es;
                                                                    
                                                                  }
                                                                  
                                                                  
                                                                  temp.valdc=getval($6);
                                                                 // //printf("check =%s",$7);
                                                                  temp.value=getval($7);
                                                                  reduce($8,2);

                                                                  temp.freq=getval($8);
                                                                  addfreq(temp.freq,freq,&fs);
                                                                  reduce($9,1);
                                                                  if(temp.valdc!=0){
                                                                    addfreq(0,freq,&fs);
                                                                  }
                                                                  temp.delay=getval($9);
                                                                  e[es]=temp; 

                                                                  es++;
                                                                  //printf("es=%d",es);


                                              }
;


current_source:
isrc NAME NAME SINE LP RESISTOR RESISTOR FREQ TIME  RP
                                              {

                                                      if(size==0){
                                                        cordi ctemp;
                                                        ctemp.x=width/2;
                                                        ctemp.y=width/2;

                                                        cordi temp2;
                                                        temp2.x=width/2+length;
                                                        temp2.y=width/2;
                                                        allc[0]=ctemp;
                                                        allc[1]=temp2;
                                                        addnet($2,allnets,&size);
                                                        addnet($3,allnets,&size);
                                                        pcs(circuit,$1,$4);
                                                      }

                                                      else{

                                                      char n[100000];
                                                      strcat(n,$4);
                                                      strcat(n,$5);
                                                      strcat(n,$6);
                                                      strcat(n,$7);
                                                      strcat(n,$8);
                                                      strcat(n,$9);
                                                      strcat(n,$10);
                                                        pcs(temp,$1,n);
                                                        addcomponent(circuit,temp,$2,$3,allnets,allc,&size);
                                                                                                          strcpy(temp,"");
                                                     // //printf("%s\n",temp );
                                                      
                                                      }
                                                    //printf("current source %s %s %s %s %d\n",$1,$2,$3,$4,size);
                                              no[getnet($2,allnets,&size)]=no[getnet($2,allnets,&size)]+1;
                                                      no[getnet($3,allnets,&size)]=no[getnet($3,allnets,&size)]+1;


                                                                   element temp;
                                                                  temp.type='I';
                                                                  strcpy(temp.name,$1);
                                                                  gaddnet($2,v,&vs);
                                                                  gaddnet($3,v,&vs);                                                                  
                                                                  char zero[2]="0";
                                                                  if(strcmp($2,zero)!=0){
                                                                    temp.net1=netpos($2,v,vs);
                                                                    v[netpos($2,v,vs)].outsize++;
                                                                    v[netpos($2,v,vs)].outgoing[v[netpos($2,v,vs)].outsize-1]=es;
                                                                    
                                                                  }

                                                                  if(strcmp($3,zero)!=0){
                                                                    temp.net2=netpos($3,v,vs); 
                                                                    v[netpos($3,v,vs)].insize++;
                                                                    v[netpos($3,v,vs)].ingoing[v[netpos($3,v,vs)].insize-1]=es;
                                                                    
                                                                  }
                                                                   
                                                                  temp.valdc=getval($6);
                                                                  temp.value=getval($7);
                                                                  reduce($8,2);
                                                                  temp.freq=getval($8);

                                                                  addfreq(temp.freq,freq,&fs);
                                                                  reduce($9,1);
                                                                  if(temp.valdc!=0){
                                                                    addfreq(0,freq,&fs);
                                                                  }
                                                                  
                                                                  temp.delay=getval($9);
                                                                  e[es]=temp; 

                                                                  es++;
                                                                  //printf("es=%d",es);
                                                      
                                            }
;

| isrc NAME NAME SINE LP RESISTOR RESISTOR FREQ TIME RESISTOR RP 
                                              {

                                                      if(size==0){
                                                        cordi ctemp;
                                                        ctemp.x=width/2;
                                                        ctemp.y=width/2;

                                                        cordi temp2;
                                                        temp2.x=width/2+length;
                                                        temp2.y=width/2;
                                                        allc[0]=ctemp;
                                                        allc[1]=temp2;
                                                        addnet($2,allnets,&size);
                                                        addnet($3,allnets,&size);
                                                        pcs(circuit,$1,$4);
                                                      }

                                                      else{

                                                      char n[100000];
                                                      strcat(n,$4);
                                                      strcat(n,$5);
                                                      strcat(n,$6);
                                                      strcat(n,$7);
                                                      strcat(n,$8);
                                                      strcat(n,$9);
                                                      strcat(n,$10);
                                                      strcat(n,$11);
                                                        pcs(temp,$1,n);
                                                        addcomponent(circuit,temp,$2,$3,allnets,allc,&size);
                                                                                                          strcpy(temp,"");
                                                     // //printf("%s\n",temp );
                                                      
                                                      }
                                                    //printf("current source %s %s %s %s %d\n",$1,$2,$3,$4,size);
                                              no[getnet($2,allnets,&size)]=no[getnet($2,allnets,&size)]+1;
                                                      no[getnet($3,allnets,&size)]=no[getnet($3,allnets,&size)]+1;


                                                                   element temp;
                                                                  temp.type='I';
                                                                  strcpy(temp.name,$1);
                                                                  gaddnet($2,v,&vs);
                                                                  gaddnet($3,v,&vs);                                                                  
                                                                  char zero[2]="0";
                                                                  if(strcmp($2,zero)!=0){
                                                                    temp.net1=netpos($2,v,vs);
                                                                    v[netpos($2,v,vs)].outsize++;
                                                                    v[netpos($2,v,vs)].outgoing[v[netpos($2,v,vs)].outsize-1]=es;
                                                                    
                                                                  }

                                                                  if(strcmp($3,zero)!=0){
                                                                    temp.net2=netpos($3,v,vs); 
                                                                    v[netpos($3,v,vs)].insize++;
                                                                    v[netpos($3,v,vs)].ingoing[v[netpos($3,v,vs)].insize-1]=es;
                                                                    
                                                                  }
                                                                   
                                                                  temp.valdc=getval($6);
                                                                  temp.value=getval($7);
                                                                  reduce($8,2);
                                                                  temp.freq=getval($8);

                                                                  addfreq(temp.freq,freq,&fs);
                                                                  reduce($9,1);
                                                                  if(temp.valdc!=0){
                                                                    addfreq(0,freq,&fs);
                                                                  }
                                                                  
                                                                  temp.delay=getval($9);
                                                                  e[es]=temp; 

                                                                  es++;
                                                                  //printf("es=%d",es);
                                                      
                                            }
;

resistor: 
NAME NAME NAME RESISTOR  

                                            {
                                              
                                                  if(size==0){
                                                    cordi ctemp;
                                                    ctemp.x=width/2;
                                                    ctemp.y=width/2;

                                                    cordi temp2;
                                                    temp2.x=width/2+length;
                                                    temp2.y=width/2;
                                                    allc[0]=ctemp;
                                                    allc[1]=temp2;
                                                    ////printf("str is%s\n", $2);

                                                    ////printf("%s\n", $2);
                                                    addnet($2,allnets,&size);
                                                    addnet($3,allnets,&size);
                                                    pres(circuit,$1,$4);
                                                  }
                                                  else{
                                                    pres(temp,$1,$4);
                                                    addcomponent(circuit,temp,$2,$3,allnets,allc,&size);
                                                                                                          strcpy(temp,"");
                                                     // //printf("%s\n",temp );
                                            }
                                              //printf("resistor: %s %s %s %s %d\n",$1,$2,$3,$4,size);
                                              no[getnet($2,allnets,&size)]=no[getnet($2,allnets,&size)]+1;
                                                      no[getnet($3,allnets,&size)]=no[getnet($3,allnets,&size)]+1;



                                                                  element temp;
                                                                  temp.type='R';
                                                                  strcpy(temp.name,$1);
                                                                   gaddnet($2,v,&vs);
                                                                  gaddnet($3,v,&vs);
                                                                  char zero[2]="0";
                                                                  if(strcmp($2,zero)!=0){
                                                                    temp.net1=netpos($2,v,vs);
                                                                    v[netpos($2,v,vs)].outsize++;
                                                                    v[netpos($2,v,vs)].outgoing[v[netpos($2,v,vs)].outsize-1]=es;
                                                                    
                                                                  }

                                                                  if(strcmp($3,zero)!=0){
                                                                    temp.net2=netpos($3,v,vs); 
                                                                    v[netpos($3,v,vs)].insize++;
                                                                    v[netpos($3,v,vs)].ingoing[v[netpos($3,v,vs)].insize-1]=es;
                                                                    
                                                                  }
                                                                  
                                                                  temp.value=getval($4);
                                                                  e[es]=temp; 

                                                                  es++;
                                                                  //printf("es=%d",es);
                                                      

                                            }
;


capacitor: 
NAME NAME NAME CAPACITOR 

                                            {

                                                    
                                                    if(size==0){
                                                      cordi ctemp;
                                                      ctemp.x=width/2;
                                                      ctemp.y=width/2;

                                                      cordi temp2;
                                                      temp2.x=width/2+length;
                                                      temp2.y=width/2;
                                                      allc[0]=ctemp;
                                                      allc[1]=temp2;
                                                      addnet($2,allnets,&size);
                                                      addnet($3,allnets,&size);
                                                      pcap(circuit,$1,$4);
                                                    }
                                                    else{
                                                      pcap(temp,$1,$4);
                                                      addcomponent(circuit,temp,$2,$3,allnets,allc,&size);
                                                                                                          strcpy(temp,"");
                                                     // //printf("%s\n",temp );
                                                    
                                                    }
                                                    no[getnet($2,allnets,&size)]=no[getnet($2,allnets,&size)]+1;
                                                      no[getnet($3,allnets,&size)]=no[getnet($3,allnets,&size)]+1;
                                                      
                                                     // printf("capacitor: %s %s %s %s %d\n",$1,$2,$3,$4,size);

                                                                  element temp;
                                                                  temp.type='C';
                                                                  strcpy(temp.name,$1);
                                                                  gaddnet($2,v,&vs);
                                                                  gaddnet($3,v,&vs);                                                                 
                                                                  char zero[2]="0";
                                                                  if(strcmp($2,zero)!=0){
                                                                    temp.net1=netpos($2,v,vs);
                                                                    v[netpos($2,v,vs)].outsize++;
                                                                    v[netpos($2,v,vs)].outgoing[v[netpos($2,v,vs)].outsize-1]=es;
                                                                    
                                                                  }

                                                                  if(strcmp($3,zero)!=0){
                                                                    temp.net2=netpos($3,v,vs); 
                                                                    v[netpos($3,v,vs)].insize++;
                                                                    v[netpos($3,v,vs)].ingoing[v[netpos($3,v,vs)].insize-1]=es;
                                                                    
                                                                  }
                                                                  ////printf("capacitor=%s\n",$4);
                                                                  reduce($4,1);
                                                                  temp.value=getval($4);
                                                                  e[es]=temp; 

                                                                  es++;
                                                                  //printf("es=%d",es);

                                            }
;



inductor: 
NAME NAME NAME INDUCTOR  

                                            {

                                                     
                                                      if(size==0){
                                                        cordi ctemp;
                                                        ctemp.x=width/2;
                                                        ctemp.y=width/2;

                                                        cordi temp2;
                                                        temp2.x=width/2+length;
                                                        temp2.y=width/2;
                                                        allc[0]=ctemp;
                                                        allc[1]=temp2;
                                                        addnet($2,allnets,&size);
                                                        addnet($3,allnets,&size);
                                                        pind(circuit,$1,$4);
                                                      }
                                                      else{
                                                        pind(temp,$1,$4);
                                                        addcomponent(circuit,temp,$2,$3,allnets,allc,&size);
                                                                                                          strcpy(temp,"");
                                                     // //printf("%s\n",temp );
                                                    
                                                      }

                                                        //printf("inductor: %s %s %s %s\n",$1,$2,$3,$4);
                                                        no[getnet($2,allnets,&size)]=no[getnet($2,allnets,&size)]+1;
                                                      no[getnet($3,allnets,&size)]=no[getnet($3,allnets,&size)]+1;


                                                                   element temp;
                                                                  temp.type='L';
                                                                  strcpy(temp.name,$1);
                                                                  gaddnet($2,v,&vs);
                                                                  gaddnet($3,v,&vs);
                                                                  char zero[2]="0";
                                                                  if(strcmp($2,zero)!=0){
                                                                    temp.net1=netpos($2,v,vs);
                                                                    v[netpos($2,v,vs)].outsize++;
                                                                    v[netpos($2,v,vs)].outgoing[v[netpos($2,v,vs)].outsize-1]=es;
                                                                    
                                                                  }

                                                                  if(strcmp($3,zero)!=0){
                                                                    temp.net2=netpos($3,v,vs); 
                                                                    v[netpos($3,v,vs)].insize++;
                                                                    v[netpos($3,v,vs)].ingoing[v[netpos($3,v,vs)].insize-1]=es;
                                                                    
                                                                  }
                                                                  reduce($4,1);
                                                                  temp.value=getval($4);
                                                                  e[es]=temp; 

                                                                  es++;
                                                                  //printf("es=%d",es);
                                                      
                                            }
;




comment:
COMMENT
{
////printf("1\n");



}
;

%%
int check(int a[],int size){
  for (int i = 0; i < size; i++)
  {
    if(a[i]<2)
      return 0;
  }
  return 1;
}

int main(int argc, char* argv[]){

  ////printf("fhsagj\n");
    yyin = fopen(argv[1], "r");
    out = fopen(argv[2],"w");
   results = fopen(argv[3],"w");
    yyparse();
    if(check(no,size)==0){
      printf("Error:Open Circuit\n");
    }
    fprintf(out,"<svg xmlns=\"http://www.w3.org/2000/svg\" height=\"1000\" width=\"1000\">\n");
    translate(circuit,(-width)/2,width/2);
    pnets(circuit,allnets,allc,size);
    translate(circuit,(5*width)/2,3*width/2);
    
    fprintf(out,"%s\n", circuit);
    fprintf(out, "</svg>\n" );
    //yylex();
    //printf("vs=%d",vs);
    //printf("es=%d",es);

    arraysort(freq,fs);
  for(int i=0;i<fs;i++){
    fprintf(results,"FREQ=%.3lfKhz\n",freq[i]/1000);
    printsoln(results,getsoln(v,e,es,vs,freq[i]),e,es);
    
  }  
   
    fclose(yyin);
    return 0;
}


