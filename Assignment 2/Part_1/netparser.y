%{

#include <stdio.h>
#include <string.h>
#include "funcs.h"

char circuit[2000000]="";
nets allnets[10000];
cordi allc[10000];
int no[10000];

char temp[10000];
int size=0;
  void yyerror(const char *str){
    
    fprintf(stderr,"ERROR: %s \n",str);
    
  }
   int yylex(void);
    extern FILE* yyin;
    FILE* out;



     
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
vol NAME NAME SINE 
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
                                                      pvol(temp,$1,$4);
                                                      addcomponent(circuit,temp,$2,$3,allnets,allc,&size);
                                                      strcpy(temp,"");
                                                      printf("%s\n",temp );
                                                                                                          strcpy(temp,"");
                                                     // printf("%s\n",temp );

                                                      }
                                                      no[getnet($2,allnets,&size)]=no[getnet($2,allnets,&size)]+1;
                                                      no[getnet($3,allnets,&size)]=no[getnet($3,allnets,&size)]+1;
                                                      
                                                        printf("voltage source %s %s %s %s %d\n",$1,$2,$3,$4,size);

                                              }
;


current_source: 
isrc NAME NAME SINE 
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
                                                        pcs(temp,$1,$4);
                                                        addcomponent(circuit,temp,$2,$3,allnets,allc,&size);
                                                                                                          strcpy(temp,"");
                                                     // printf("%s\n",temp );
                                                      
                                                      }
                                                    printf("current source %s %s %s %s %d\n",$1,$2,$3,$4,size);
                                              no[getnet($2,allnets,&size)]=no[getnet($2,allnets,&size)]+1;
                                                      no[getnet($3,allnets,&size)]=no[getnet($3,allnets,&size)]+1;
                                                      
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
                                                    //printf("str is%s\n", $2);

                                                    //printf("%s\n", $2);
                                                    addnet($2,allnets,&size);
                                                    addnet($3,allnets,&size);
                                                    pres(circuit,$1,$4);
                                                  }
                                                  else{
                                                    pres(temp,$1,$4);
                                                    addcomponent(circuit,temp,$2,$3,allnets,allc,&size);
                                                                                                          strcpy(temp,"");
                                                     // printf("%s\n",temp );
                                            }
                                              printf("resistor: %s %s %s %s %d\n",$1,$2,$3,$4,size);
                                              no[getnet($2,allnets,&size)]=no[getnet($2,allnets,&size)]+1;
                                                      no[getnet($3,allnets,&size)]=no[getnet($3,allnets,&size)]+1;
                                                      

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
                                                     // printf("%s\n",temp );
                                                    
                                                    }
                                                    no[getnet($2,allnets,&size)]=no[getnet($2,allnets,&size)]+1;
                                                      no[getnet($3,allnets,&size)]=no[getnet($3,allnets,&size)]+1;
                                                      
                                                      printf("capacitor: %s %s %s %s %d\n",$1,$2,$3,$4,size);

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
                                                     // printf("%s\n",temp );
                                                    
                                                      }

                                                        printf("inductor: %s %s %s %s\n",$1,$2,$3,$4);
                                                        no[getnet($2,allnets,&size)]=no[getnet($2,allnets,&size)]+1;
                                                      no[getnet($3,allnets,&size)]=no[getnet($3,allnets,&size)]+1;
                                                      
                                            }
;




comment:
COMMENT
{
//printf("1\n");



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
  //printf("fhsagj\n");
    yyin = fopen(argv[1], "r");
    out = fopen(argv[2],"w");
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
   
    fclose(yyin);
    return 0;
}


