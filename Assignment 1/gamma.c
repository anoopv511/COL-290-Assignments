#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int MAX_LENGTH;

typedef struct{
	int sign;
	int* integer;
	int* decimal;
}number;

void err(char* e){
	printf("%s\n", e);
	exit(0);
}

int* init(){
	int* n = (int*)malloc(sizeof(int)*MAX_LENGTH);
	int i;
	for(i=0;i<MAX_LENGTH;i++) n[i] = 0;
	return n;
}

void pad(int* n,int start){
	int i;
	for(i=start;i<MAX_LENGTH;i++) n[i] = 0;
}

number parseStr(char* s){
	number n;
	n.sign = 0;
	n.integer = init();
	n.decimal = init();
	int length = strlen(s);
	int decimalPoint,i;
	for(decimalPoint=0;decimalPoint<length;decimalPoint++) if(s[decimalPoint] == '.') break;
	if(decimalPoint == length && length > MAX_LENGTH) err("LowPrec");
	if(length > MAX_LENGTH + 1) err("LowPrec");
	for(i=0;i<decimalPoint;i++) n.integer[i] = s[decimalPoint - i - 1] - 48;
	for(i=0;i<length-decimalPoint-1;i++) n.decimal[i] = s[decimalPoint + i + 1] - 48;
	return n;
}

int zeroes(int* arr){
	int i;
	int x = MAX_LENGTH;
	if(arr[MAX_LENGTH - 1] != 0) return x;
	for(i=1;i<MAX_LENGTH;i++){
		x--;
		if(arr[MAX_LENGTH - i] == 0 && arr[MAX_LENGTH - 1 - i] != 0) return x;
	}
	return --x;
}

char* parseNum(number n){
	char* str = (char*)malloc(sizeof(char)*(MAX_LENGTH + 1));
	int indexInt = zeroes(n.integer);
	int i;
	for(i=0;i<indexInt;i++) str[i] = n.integer[indexInt - 1 - i] + 48;
	if(indexInt == MAX_LENGTH) goto negCheck;
	if(indexInt == 0) str[indexInt++] = '0';
	int indexDec = zeroes(n.decimal);
	if(indexDec == 0) goto negCheck;
	str[indexInt] = '.';
	for(i=indexInt+1;i<MAX_LENGTH+1 && i<indexInt+1+indexDec;i++) str[i] = n.decimal[i-indexInt-1] + 48;
	negCheck:if(n.sign == 1){
		int length = strlen(str);
		char* negstr = (char*)malloc(sizeof(char)*(length+1));
		negstr[0] = '-';
		for(i=0;i<length;i++) negstr[i+1] = str[i];
		return negstr;
	}
	return str;
}

void rnd(number n){
	int zeroesInt = zeroes(n.integer);
	if(zeroesInt == 0)  zeroesInt++;
	int zeroesDec = zeroes(n.decimal);
	if(zeroesInt + zeroesDec > MAX_LENGTH) pad(n.decimal,zeroesDec - (MAX_LENGTH - zeroesInt - zeroesDec));
}

number sub(number x,number y);

number add(number x,number y){
	if(x.sign > y.sign){
		x.sign = 0;
		return sub(y,x);
	}
	if(y.sign > x.sign){
		y.sign = 0;
		return sub(x,y);
	}
	number ans;
	ans.sign = x.sign;
	ans.integer = init();
	ans.decimal = init();
	int i;
	int zeroesIntX = zeroes(x.integer);
	int zeroesIntY = zeroes(y.integer);
	int zeroesDecX = zeroes(x.decimal);
	int zeroesDecY = zeroes(y.decimal);
	int maxInt = zeroesIntX > zeroesIntY ? zeroesIntX : zeroesIntY;
	int maxDec = zeroesDecX > zeroesDecY ? zeroesDecX : zeroesDecY;
 	ans.decimal[maxDec-1] = x.decimal[maxDec-1] + y.decimal[maxDec-1];
	for(i=1;i<maxDec;i++){
		ans.decimal[maxDec-1-i] = x.decimal[maxDec-i-1] + y.decimal[maxDec-i-1] + ans.decimal[maxDec-i]/10;
		ans.decimal[maxDec-i] %= 10;
	}
	ans.integer[0] = x.integer[0] + y.integer[0] + ans.decimal[0]/10;
	ans.decimal[0] %= 10;
	for(i=1;i<maxInt;i++){
		ans.integer[i] = x.integer[i] + y.integer[i] + ans.integer[i-1]/10;
		ans.integer[i-1] %= 10;
	}
	int overflow = ans.integer[MAX_LENGTH-1]/10;
	ans.integer[maxInt-1] %= 10;
	if(overflow == 1) err("LowPrec");
	rnd(ans);
	return ans;
}

int Ucomp(number x,number y){
	int comp = 0;
	int i;
	for(i=MAX_LENGTH-1;i>-1;i--){
		if(x.integer[i] > y.integer[i]) return 1;
		if(x.integer[i] < y.integer[i]) return -1;
	}
	for(i=0;i<MAX_LENGTH;i++){
		if(x.decimal[i] > y.decimal[i]) return 1;
		if(x.decimal[i] < y.decimal[i]) return -1;
	}
	return 0;
}

number sub(number x,number y){
	if(x.sign > y.sign){
		y.sign = 1;
		return add(x,y);
	}
	if(y.sign > x.sign){
		y.sign = 0;
		return add(x,y);
	}
	number ans,temp;
	ans.sign = 0;
	ans.integer = init();
	ans.decimal = init();
	int check = Ucomp(x,y);
	if(check == 0) return ans;
	if(check < 0){
		temp = x;
		x = y;
		y = temp;
	}
	int i,carry;
	int zeroesIntX = zeroes(x.integer);
	int zeroesIntY = zeroes(y.integer);
	int zeroesDecX = zeroes(x.decimal);
	int zeroesDecY = zeroes(y.decimal);
	int maxInt = zeroesIntX > zeroesIntY ? zeroesIntX : zeroesIntY;
	int maxDec = zeroesDecX > zeroesDecY ? zeroesDecX : zeroesDecY;
	ans.decimal[maxDec-1] = x.decimal[maxDec-1] - y.decimal[maxDec-1];
	for(i=1;i<maxDec;i++){
		carry = ans.decimal[maxDec-i] < 0 ? 1 : 0;
		ans.decimal[maxDec-i-1] = x.decimal[maxDec-i-1] - y.decimal[maxDec-i-1] - carry;
		ans.decimal[maxDec-i] += carry > 0 ? 10 : 0;
	}
	carry = ans.decimal[0] < 0 ? 1 : 0;
	ans.integer[0] = x.integer[0] - y.integer[0] - carry;
	ans.decimal[0] += carry > 0 ? 10 : 0;
	for(i=1;i<maxInt;i++){
		carry = ans.integer[i-1] < 0 ? 1 : 0;
		ans.integer[i] = x.integer[i] - y.integer[i] - carry;
		ans.integer[i-1] += carry > 0 ? 10 : 0;
	}
	rnd(ans);
	ans.sign = (check < 0)^(x.sign == 1) ? 1 : 0;
	return ans;
}

/*number mul(number x,number y){
	number ans;
	ans.sign = x.sign == y.sign ? 0 : 1;
	ans.integer = init();
	ans.decimal = init();
	int i,j;
	for(i=0;i<MAX_LENGTH;i++){
		for(j=0;j<MAX_LENGTH;j++){

		}
	}
}*/

int main(){
	MAX_LENGTH = 3;
	char m[] = "99.9";
	char n[] = "1";
	number numN = parseStr(n);
	number numM = parseStr(m);
	printf("%s + %s\n", parseNum(numN), parseNum(numM));
	char* ans = parseNum(add(numN,numM));
	printf("%s\n", ans);
	return 0;
}