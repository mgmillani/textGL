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

#include "textBase.h"
#include "textOrganizer.h"


/**
  * transforma de unsigned char * para t_textChar *
  */
t_textChar *textConvertChar(unsigned char *string,unsigned int len)
{
	unsigned int i;
	t_textChar *text = malloc(len*sizeof(*text));
	for(i=0 ; i<len ; i++)
		text[i] = string[i];
	return text;
}

/**
  * cria a estrutura do texto
  * nao divide em linhas
  * o ponteiro para a string eh copiado para a estrutura
  * ele nao sera alterado e nao deve ser liberado pelo caller
  */
t_text *textInit(t_textChar *string,unsigned int textLen, int letterSpacing,int lineSpacing, unsigned int lineHeight)
{
	t_text *text = malloc(sizeof(*text));
	text->text = string;
	text->length = textLen;
	text->numLines = 0;
	text->lineIndex = NULL;
	text->lineOffset = NULL;

	text->letterSpacing = letterSpacing;
	text->lineHeight = lineHeight;
	text->lineSpacing = lineSpacing;

	text->alignment = AlignLeft;

	return text;
}
/**
  * quebra o texto em linhas de forma que nenhuma delas tenha mais de maxWidth pixels
  * nao quebra as palavras
  * se lineOffset e lineIndex forem NULL, primeiro calcula quantas linhas haverao, e depois atualiza-as
  * caso contrario, assume que o numero de linhas esta correto e atualiza os pontos de quebra
  */
void textArrangeAux(t_text *text, unsigned int maxWidth, int *lineOffset, unsigned int *lineIndex,t_alphabet *ab)
{
	typedef enum {StateWord, StateSpace} e_states;
	double scale = text->lineHeight/(double)ab->cellH;
	t_textChar *string = text->text;

	unsigned int lines = 1;
	unsigned int lineWidth = 0;
	unsigned int wordWidth = 0;
	unsigned int wordBegin = 0;
	unsigned int i;

	e_states state = StateSpace;

	for(i=0 ; i<text->length ; i++)
	{
		t_textChar c = string[i];
		switch(state)
		{
			//estamos lendo caracteres dentro de uma palavra
			//nao podemos quebrar a linha no meio da palavra
			case StateWord:
				//se for um espaco
				if(ab->isEmpty[c])
				{
					lineWidth += ab->spaceWidth*scale;
					state = StateSpace;
				}
				else
				{
					t_textChar index = ab->translation[c];
					unsigned int width = scale*ab->width[index].second + text->letterSpacing;
					wordWidth += width;
					//se a palavra estourar a largura maxima, quebra a linha antes daquela
					if(lineWidth + width > maxWidth)
					{
						//se estamos quebrando as linhas, adiciona o ponto de quebra
						if(lineOffset!=NULL)
							lineIndex[lines-1] = wordBegin;

						lines++;
						lineWidth = wordWidth;
					}
					else
						lineWidth += width;

				}
				break;
			case StateSpace:
				//se for um espaco
				if(ab->isEmpty[c])
					lineWidth += ab->spaceWidth*scale;
				else
				{
					//inicio de uma palavra
					state = StateWord;
					wordWidth = 0;
					wordBegin = i;
					t_textChar index = ab->translation[c];
					unsigned int width = scale*ab->width[index].second + text->letterSpacing;
					//quebra-se a linha se o caracter for deixa-la muito grande
					if(lineWidth + width > maxWidth)
					{
						//se estamos quebrando as linhas, adiciona o ponto de quebra
						if(lineOffset!=NULL)
							lineIndex[lines-1] = i;

						lines++;
						lineWidth = width;
					}
					else
					{
						lineWidth+=width;
					}
				}
				break;
		}
	}
	//se apenas foi contado o numero de linhas
	if(lineOffset==NULL)
	{
		//verifica se o numero de linhas foi alterado
		//determina se eh necessario mudar o numero de linhas
		if(lines != text->numLines)
		{
			//libera o vetor de indices caso ele tenha sido alocado
			if(text->lineIndex != NULL)
			{
				free(text->lineIndex);
				free(text->lineOffset);
			}
			text->lineIndex = malloc(sizeof(*(text->lineIndex))*lines);
			text->lineOffset = malloc(sizeof(*(text->lineOffset))*lines);
			text->numLines = lines;
		}
		//se chama recursivamente, agora calculando os pontos de quebra
		textArrangeAux(text,maxWidth,text->lineOffset,text->lineIndex,ab);
	}
	//se estamos quebrando as linhas, adiciona o ponto de quebra
	else
		lineIndex[lines-1] = i;

}

/**
  * quebra o texto em linhas de forma que nenhuma delas tenha mais de maxWidth pixels
  * nao quebra as palavras
  */
void textArrange(t_text *text, unsigned int maxWidth, t_alphabet *ab)
{

	textArrangeAux(text,maxWidth,NULL,NULL,ab);

}

/**
  * alinha o texto a esquerda
  */
void textAlignLeft(t_text *text)
{

	unsigned int i;
	for(i=0 ; i<text->numLines ; i++)
		text->lineOffset[i] = 0;
	text->alignment = AlignLeft;
}

/**
  * alinha o texto a direita
  */
void textAlignRight(t_text *text)
{

	unsigned int i;
	for(i=0 ; i<text->numLines ; i++)
		text->lineOffset[i] = 0;
	text->alignment = AlignRight;
}

void textAlignCenter(t_text *text, const t_alphabet *ab)
{
	unsigned int l,i;
	t_textChar *string = text->text;
	double scale = text->lineHeight / (double)ab->cellH;
	//determina o tamanho de cada linha
	for(l=0,i=0 ; l<text->numLines ; l++)
	{
		int lineWidth = 0;
		for(; i <text->lineIndex[l] ; i++)
		{
			if(ab->isEmpty[string[i]])
				lineWidth += ab->spaceWidth*scale;
			else
			{
				t_textChar c = ab->translation[string[i]];
				lineWidth += scale*ab->width[c].second + text->letterSpacing;
			}
		}

		text->lineOffset[l] = -lineWidth/2;
	}
}

/**
  * alinha o texto conforme o parametro align
  */
void textAlign(t_text *text, const t_alphabet *ab, e_alignment align)
{
	switch(align)
	{
		case AlignLeft:
			textAlignLeft(text);
			break;
		case AlignRight:
			textAlignRight(text);
			break;
		case AlignCenter:
			textAlignCenter(text,ab);
			break;
	}
}













