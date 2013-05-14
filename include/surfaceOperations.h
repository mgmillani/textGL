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

#ifndef SURFACEOPERATIONS_H
#define SURFACEOPERATIONS_H

/**
  * converte uma SDL_Surface para uma textura do OpenGL
  */
GLuint surface2texture(SDL_Surface *surface);

/**
  * usa a cor do pixel (0,0) como colorkey
  * adiciona um alphachannel a surface com base nessa colorkey
  */
SDL_Surface *surfaceRemoveBackground(SDL_Surface *surface);

#endif // SURFACEOPERATIONS_H

