#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_SIZE 5
#define MIN_SIZE 3

int memcpy1() {
//    char str1[MAX_SIZE] = {8,8,8,8,8};
//    char str2[MAX_SIZE] = {1,1,1,1,1};        /* “r’†‚É‹ó•¶Žš‚Ì‚ ‚é•¶Žš—ñ */

    char* str1 = new char[MAX_SIZE];
    char* str2 = new char[MAX_SIZE];        /* “r’†‚É‹ó•¶Žš‚Ì‚ ‚é•¶Žš—ñ */

    int i;
    
    printf("src:\n");
    for (i=0; i<MAX_SIZE; i++)
            printf("%#x ",str1[i]);
    printf("\n");
    
    memcpy(str1, str2, MAX_SIZE);

    printf("dst:\n");
    for (i=0; i<MAX_SIZE; i++)
            printf("%#x ",str1[i]);
    printf("\n");

	return 0;
}

int memcpy2() {
//    char str1[MIN_SIZE] = {8,8,8};
//    char str2[MAX_SIZE] = {1,1,1,1,1};        /* “r’†‚É‹ó•¶Žš‚Ì‚ ‚é•¶Žš—ñ */

    char* str1 = new char[MAX_SIZE];
    char* str2 = new char[MIN_SIZE];        /* “r’†‚É‹ó•¶Žš‚Ì‚ ‚é•¶Žš—ñ */

    int i;
    
    printf("src:\n");
    for (i=0; i<MAX_SIZE; i++)
            printf("%#x ",str1[i]);
    printf("\n");
    
    memcpy(str1, str2, MAX_SIZE);

    printf("dst:\n");
    for (i=0; i<MAX_SIZE; i++)
            printf("%#x ",str1[i]);
    printf("\n");

	return 0;
}

int memcpy3() {

//    char str1[MAX_SIZE] = {8,8,8,8,8};
//    char str2[MIN_SIZE] = {1,1,1};        /* “r’†‚É‹ó•¶Žš‚Ì‚ ‚é•¶Žš—ñ */

    char* str1 = new char[MIN_SIZE];
    char* str2 = new char[MAX_SIZE];        /* “r’†‚É‹ó•¶Žš‚Ì‚ ‚é•¶Žš—ñ */


    int i;
    
    printf("src:\n");
    for (i=0; i<MAX_SIZE; i++)
            printf("%#x ",str1[i]);
    printf("\n");
    
    memcpy(str1, str2, MAX_SIZE);

    printf("dst:\n");
    for (i=0; i<MAX_SIZE; i++)
            printf("%#x ",str1[i]);
    printf("\n");

	return 0;
}

void f0(char *s1, const char *s2) { strncpy(s1, s2, 9); }
void f1(char *s1, const char *s2) { strncpy(s1, s2, 9); s1[9] = '\0'; }
void f2(char *s1, const char *s2) { s1[0] = '\0'; strncat(s1, s2, 9); }
void f3(char *s1, const char *s2) { sprintf(s1, "%.9s", s2); }
void f4(char *s1, const char *s2) { sscanf(s2, "%9s", s1); }

void set(char *s) { memset(s, 0x23, 10); }

void dump(const char *s)
{
    int i;
    for (i = 0; i < 10; i++) printf(" %02x", s[i]);
    puts("");
}

int memcpy4(void)
{
    char s[10];

    set(s); f0(s, "abc"); dump(s);
    set(s); f1(s, "abc"); dump(s);
    set(s); f2(s, "abc"); dump(s);
    set(s); f3(s, "abc"); dump(s);
    set(s); f4(s, "abc"); dump(s);
    puts("---");
    set(s); f0(s, "abcdefghijklm"); dump(s);
    set(s); f1(s, "abcdefghijklm"); dump(s);
    set(s); f2(s, "abcdefghijklm"); dump(s);
    set(s); f3(s, "abcdefghijklm"); dump(s);
    set(s); f4(s, "abcdefghijklm"); dump(s);

    return 0;
}


#define MAX 10

struct temp {
    int en;
    int one[MAX];
    int two[MAX];
 };

int memcpy5(void)
{
/*
    struct temp *cpy;
    int *buffer, i;

    for(i=0; i<MAX; i++) {
            cpy->one[i] = i;
            cpy->two[i] = i * i;
     }

   buffer = malloc(3 * MAX * sizeof(int));
   memcpy(buffer, cpy, sizeof(struct temp));
*/

    struct temp cpy;
    int *buffer, i;

    for(i=0; i<MAX; i++) {
            cpy.one[i] = i;
            cpy.two[i] = i * i;
    }

   	buffer = (int*)malloc(sizeof(int) * 12 * MAX);

   	//if (cpy) {
        printf("buffer size  :%d \n",sizeof(buffer));
        printf("buffer size  :%d \n",malloc_usable_size(buffer));
        printf("buffer       :%s \n",buffer);
        printf("cpy size     :%d \n",sizeof(cpy));
        //printf("cpy size     :%d \n",malloc_usable_size(cpy));
        printf("cpy          :%s \n",cpy);
        printf("size         :%d \n",sizeof(struct temp));
   		memcpy(buffer, &cpy, sizeof(100));
	//}

     free(buffer);

    return 0;
}

void reverseSubString(char* str);

int memcpy6(void)
{
    char* line = "AAAAAAAAAAAAAAAAAAAAAAAAA";
	int start = 0;
    int end = 10;

    char str[end-start];

    printf("dst:%s src:%s size:%d \n",str,line+start,end-start);
    memcpy ( str , line + start , end-start );

    reverseSubString ( str );

    printf("dst:%s src:%s size:%d \n",line+start,str,end-start);
    memcpy ( line + start, str , end-start );

    return 0;
}

void reverseSubString(char* str){

    int i, j, len;
    char temp;

    i=j=len=temp=0;

    len=strlen(str);

    for (i=0, j=len-1; i<=j; i++, j--)
    {
        temp=str[i];
        str[i]=str[j];
        str[j]=temp;
    }
}

int memcpy7(void)
{
	int  i  = 0;
	char *d = (char*) malloc ((sizeof(char)) * 50);
	
    printf("dst:%s src:%s size:%d \n",d,"anisha",6);
	memcpy ((void*) d, "anisha", 6);
	
    printf("dst:%s src:%s size:%d \n",(void*)(d + 6),i,4);
    if(i) {
		memcpy ((void*)(d + 6), (const void*)i, 4);
	}

	return 0;
}


int memcpy8(void)
{
	int array[10];
	array[15] = 20;

	return 0;
}
