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

#ifndef TEXTORGANIZER_H
#define TEXTORGANIZER_H

#include <textGL/textBase.h>

/**
  * transforma de unsigned char * para t_textChar *
  */
t_textChar *textConvertChar(unsigned char *string,unsigned int len);

/**
  * cria a estrutura do texto
  * nao divide em linhas
  * o ponteiro para a string eh copiado para a estrutura
  * ele nao sera alterado e nao deve ser liberado pelo caller
  */
t_text *textInit(t_textChar *string,unsigned int textLen, int letterSpacing,int lineSpacing, unsigned int lineHeight);

/**
  * quebra o texto em linhas de forma que nenhuma delas tenha mais de maxWidth pixels
  */
void textArrange(t_text *text, unsigned int maxWidth, t_alphabet *ab);

/**
  * alinha o texto conforme o parametro align
  */
void textAlign(t_text *text, const t_alphabet *ab, e_alignment align);

#endif // TEXTORGANIZER_H
