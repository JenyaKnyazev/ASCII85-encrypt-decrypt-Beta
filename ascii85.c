#include <stdlib.h>
#include <stdio.h>
typedef struct { const char *data; int n; } block;
int* char_to_binary_int_array(char ch){
    int *arr = (int*)malloc(sizeof(int)*8);
    int index = 7; 
    while(index>=0){
        arr[index] = ch%2;
        ch/=2;
        index--;
    }
    return arr;
}
int *concat_arr(int *a,int *b,int length_a){
    int *arr=(int*)malloc(sizeof(int)*(length_a+8));
    int i;
    for(i=0;i<length_a;i++)
        arr[i]=a[i];
    for(i=length_a;i<length_a+8;i++)
        arr[i]=b[i-length_a];
    //free(a);
    free(b);
    return arr;
}
long long array_binary_to_sum(int *a,int length){
    long long sum = 0;
    int i;
    long long mul=1;
    for(i=length-1;i>=0;i--,mul*=2)
        sum+=a[i]*mul;
    return sum;
}
char * sum_to_encode(long long sum){
    char *res = (char*)malloc(sizeof(char)*5);
    int index = 4;
    while(index>=0){
        res[index] = sum%85+33;
        sum-=sum%85;
        sum/=85;
        index--;
    }
    return res;
}
char *concat_encoded(char * a,char *b,int length_a){
    char *arr = (char*)malloc(sizeof(char)*length_a+5);
    int i;
    for(i=0;i<length_a;i++)
        arr[i]=a[i];
    for(i=length_a;i<length_a+5;i++)
        arr[i]=b[i-length_a];
    //free(a);
    free(b);
    return arr;
}
char *concat_char(char *a,char ch,int length){
    char *arr = (char*)malloc(sizeof(char)*(length+1));
    int i;
    for(i=0;i<length;i++)
        arr[i]=a[i];
    arr[length]=ch;
    return arr;
}
char * add_arrows(char *a,int length){
    char *arr = (char*)malloc(sizeof(char)*(length+5));
    int i;
    arr[0]='<';
    arr[1]='~';
    for(i=2;i<length+2;i++)
        arr[i]=a[i-2];
    arr[length+2]='~';
    arr[length+3]='>';
    arr[length+4]='\0';
  return arr;
}
char *add_to_4(char *a,int length){
    int len=length+(4-length%4)%4;
    char *arr=(char*)malloc(sizeof(char)*len);
    int i;
    for(i=0;i<length;i++)
        arr[i]=a[i];
    for(i=length;i<len;i++)
        arr[i]=0;
    return arr;
}
char *add_to_5(char *a,int length){
    int len=length+(5-length%5)%5;
    char *arr=(char*)malloc(sizeof(char)*len);
    int i;
    for(i=0;i<length;i++)
        arr[i]=a[i];
    for(i=length;i<len;i++)
        arr[i]=117;
    return arr;
}
int count_whitespace(char *a,int length){
    int count = 0;
    int i;
    for(i=0;i<length;i++)
        if(a[i]>0&&a[i]<' '||a[i]>0x7f)
            count++;
    return count;
}
char *remove_whitespace(char *a,int *length){
    int len=*length-count_whitespace(a,*length);
    int i,r;
    char *arr = (char*)malloc(sizeof(char)*len);
    for(i=0,r=0;i<*length;i++)
        if(!(a[i]>0x7f || a[i]>0&&a[i]<' ')){
            arr[r]=a[i];
            r++;
        }
    *length=len;
    return arr;
}
int len_str(char *p){
    int count = 0;
    p+=2;
    while(*p!='~'||*(p+1)!='>'){
        p++;
        count++;
    }
    return count;
}
char *remove_arrows(char *s,int *length){
    int len = len_str(s);
    char *arr = (char*)malloc(sizeof(char)*(len));
    s+=2;
    int i = 0;
    *length = len;
    while(len>0){
        arr[i]=*s;
        s++;
        i++;
        len--;
    }
    //arr[i]='\0';
    return arr;
}
long long chars_to_sum(char *p){
    long long sum = 0;
    sum+=(*p-33)*85*85*85*85;
    p++;
    sum+=(*p-33)*85*85*85;
    p++;
    sum+=(*p-33)*85*85;
    p++;
    sum+=(*p-33)*85;
    p++;
    sum+=*p-33;
    return sum;
}
int *sum_to_binary_arr(long long sum){
    int *arr =(int*)malloc(sizeof(int)*32);
    int i = 31;
    while(i>=0){
        arr[i]=sum%2;
        sum/=2;
        i--;
    }
    return arr;
}
char *replace_z(char *s,int *length){
    int i,r;
    char *arr;
    int len = 0;
    for(i=0;i<*length;i++){
        if(s[i]=='z'){
           for(r=0;r<5;r++){
              arr=concat_char(arr,33,len);
              len++;
           }
        }else{
            arr=concat_char(arr,s[i],len);
            len++;
        }
    }
    *length=len;
    return arr;
}
char *toAscii85 (block b) {
  int i,r;
  int *binary=NULL;
  int *binary_char;
  long long sum = 0;
  char *result;
  char *run = add_to_4(b.data,b.n);
  int all_zero;
  int len_result=0;
  b.data=remove_whitespace(b.data,&b.n);
  for(i=0;i<b.n+(4-b.n%4)%4;i+=4){
      all_zero=0;
      for(r=i;r<i+4;r++){
          all_zero+=run[r];
          binary_char=char_to_binary_int_array(run[r]);
          binary=concat_arr(binary,binary_char,(r-i)*8);
      }
      sum = array_binary_to_sum(binary,32);
      if(all_zero==0&&i!=(b.n+((4-b.n%4)%4))/4*4-4||all_zero==0&&i==b.n/4*4-4&&b.n%4==0){
          result=concat_char(result,'z',len_result);
          len_result+=1;
      }else{
          result=concat_encoded(result,sum_to_encode(sum),len_result);
          len_result+=5;
      }
  }
  if(len_result>(4-b.n%4)%4)
      result=add_arrows(result,len_result-(4-b.n%4)%4);
  else
      result=add_arrows(result,len_result);
  return result;
}

block fromAscii85 (const char *string) {
  block *b = (block*)malloc(sizeof(block));
  int length;
  char* run = remove_arrows(string,&length);
  run=remove_whitespace(run,&length);
  run=replace_z(run,&length);
  char* result=NULL;
  run = add_to_5(run,length);
  int i,r;
  int *binary_arr;
  long long sum;
  int result_len = 0;
  for(i=0;i<length;i+=5){
      sum=chars_to_sum(run+i);
      binary_arr=sum_to_binary_arr(sum);
      for(r=0;r<4;r++){
          result=concat_char(result,array_binary_to_sum(binary_arr+r*8,8),result_len);
          result_len+=1;
      }
  }
  b->n=(length+(5-length%5)%5)/5*4-(5-length%5)%5;
  result=concat_char(result,'\0',b->n);
  b->data = result;
  return *b;
}
void main(){
	char *text;
	char ch;
	int len;
	int chose;
	block *b = (block*)malloc(sizeof(block));
	do{
		puts("1 - encode\n2 - decode\nother exit\n");
		scanf("%d",&chose);
		if(chose==1||chose==2){
			puts("Enter text");
			text = NULL;
			len=0;
			while(getchar()!='\n');
			do{
				ch=getchar();
				text=concat_char(text,ch,len++);
			}while(ch!='\n');
			switch(chose){
				case 1:
					b->n=len;
					b->data=text;
					printf("Encoded : ");
					puts(toAscii85(*b));
					putchar('\n');
					break;
				case 2:
					printf("Decoded : ");
					puts(fromAscii85(text).data);
					putchar('\n');
					break;
			}
		}
		
	}while(chose>0&&chose<3);
	puts("Good Bye");
	while(getchar()!='\n');
}





































