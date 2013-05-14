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

#ifndef TEXTDRAWER_H
#define TEXTDRAWER_H

#include <SDL/SDL_opengl.h>

#include <textGL/textBase.h>

/**
  * desenha o texto a partir do ponto (x,y), crescendo em ambos os eixos
  */
void drawText(t_text *text, t_alphabet *ab, int x, int y);

#endif // TEXTDRAWER_H
