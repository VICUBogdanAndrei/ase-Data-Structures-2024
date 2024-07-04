#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>


void main()
{
	unsigned char* valoare;
	unsigned char buffer[10];
	printf("Unsigned char = ");
	scanf("%s", buffer);
	valoare = (unsigned char*)malloc((strlen(buffer) + 1) * sizeof(unsigned char));
	strcpy(valoare, buffer);
	printf("\n\n Valoare initiala = %s", valoare);

}