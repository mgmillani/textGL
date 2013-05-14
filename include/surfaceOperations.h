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

