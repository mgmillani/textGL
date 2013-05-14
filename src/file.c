#include <stdio.h>
#include <stdlib.h>

#include "file.h"

/**
	*	le um arquivo binario, escrevendo seu tamanho em size
	* retorna um ponteiro para o arquivo
	*/
char *readBinFile(const char *filename,unsigned int *size)
{

	FILE *fl = fopen(filename,"rb");
	if(fl == NULL)
		return NULL;

	fseek(fl,0,SEEK_END);
	*size = ftell(fl);
	fseek(fl,0,SEEK_SET);

	char *text = malloc(*size);
	*size = fread(text,1,*size,fl);
	fclose(fl);

	return text;
}

