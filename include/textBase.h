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

#ifndef TEXTBASE_H
#define TEXTBASE_H

#include <SDL/SDL_opengl.h>

#include <textGL/definitions.h>

typedef enum {AlignLeft, AlignCenter, AlignRight} e_alignment;

typedef GLuint t_image;

typedef struct s_alphabet
{
	t_image alphabet;          //imagem com os simbolos
	unsigned int cellW;        //largura de cada celula da imagem
	unsigned int cellH;        //altura de cada celula da imagem
	t_textChar *translation;   //translation[x] = y <=> input x deve ser mapeado para o simbolo de indice y
	char *isEmpty;             //determina se um dado caractere de entrada eh um espaco em branco
	unsigned int mapSize;      //tamanho do mapa de traducao
	t_uintTuple *width;        //largura de cada caractere. O primeiro elemento da tupla eh o x do inicio, e o segundo, o do final
	unsigned int rows;
	unsigned int spaceWidth;    //quantos porcento de cellW equivale um espaco em branco
}t_alphabet;

typedef struct s_text
{
	t_textChar *text;
	unsigned int length;        //numero de caracteres do texto
	unsigned int numLines;      //numero de linhas do texto
	unsigned int *lineIndex;    //a partir de qual indice do vetor do texto termina cada linha

	int *lineOffset;   //o offset no eixo x de cada linha

	int letterSpacing;	//quantos pixels em branco devem existir entre um caractere e outro
	int lineSpacing;   //idem para as linhas
	unsigned int lineHeight;    //se lineHeight = cellH, nenhum resize eh feito

	e_alignment alignment;

}t_text;

#endif // TEXTBASE_H

