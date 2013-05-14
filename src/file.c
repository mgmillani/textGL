/**
    This file is part of textGL.

    textGL is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    textGL is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with textGL.  If not, see <http://www.gnu.org/licenses/>.
*/

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

