#include <stdio.h>
  int look(char *p,char t){
    int count = 0;
    int flag = -1;
    while(*p!='\0'){
        count++;
    	if(*p == t){
          	flag = count;
        	break ;
        }
      	p++;
    }
  	return flag;
  }
  int main(){
    char str[] = "abcc";
    char t = 'c';
  	int index = look(str,t);
    printf("%d",index);
  }