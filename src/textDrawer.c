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

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "textBase.h"

/**
  * desenha o texto a partir do ponto (x,y), crescendo em ambos os eixos
  */
void drawText(t_text *text, t_alphabet *ab, int x, int y)
{

	//necessario por causa do alpha channel
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER,0.1f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);

	//faz o bind da textura do alphabeto
	glBindTexture(GL_TEXTURE_2D,ab->alphabet);
	glColor3f(1.0,1.0,0);

	//a distancia entre uma linha e outra
	int dy = text->lineHeight + text->lineSpacing;
	//onde cada linha comeca
	int lineX = x;
	//numero de linhas do alfabeto
	double dRows = ab->rows;
	//altura de cada linha
	unsigned int h = text->lineHeight;
	//largura de cada caractere
	unsigned int w = ab->cellW * ((double)h/ab->cellH);
	//o texto em si
	t_textChar *string = text->text;
	//itera pelas linhas
	unsigned int l;
	unsigned int c = 0;
	double scale = text->lineHeight/(double)ab->cellH;
	//printf("Lines: %d\n",text->numLines);
	for(l=0 ; l<text->numLines ; l++, y+=dy)
	{
		//itera pelos caracteres da linha
		if(text->lineOffset!=NULL)
			x = lineX + text->lineOffset[l];
		else
			x = lineX;
		for(; c<text->lineIndex[l] ; c++)
		{
			if(ab->isEmpty[string[c]])
				x+=ab->spaceWidth*scale;
			else
			{
				t_textChar pos = ab->translation[string[c]];
				unsigned int cellX = pos%ab->rows;
				unsigned int cellY = pos/ab->rows;
				//coordenadas da textura
				double minX = cellX/dRows;
				double maxX = (cellX+1)/dRows;
				double minY = cellY/dRows;
				double maxY = (cellY+1)/dRows;

				glBegin(GL_QUADS);

				glTexCoord2d(minX,maxY); //top-left
				glVertex2i(x,y+h);
				glTexCoord2d(maxX,maxY); //top-right
				glVertex2i(x+w,y+h);
				glTexCoord2d(maxX,minY); //bottom-right
				glVertex2i(x+w,y);
				glTexCoord2d(minX,minY); //bottom-left
				glVertex2i(x,y);

				glEnd();
				x+= scale*ab->width[pos].second + text->letterSpacing;
			}
		}
	}
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}















