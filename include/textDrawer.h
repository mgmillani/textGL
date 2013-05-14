#ifndef TEXTDRAWER_H
#define TEXTDRAWER_H

#include <SDL/SDL_opengl.h>

#include <textGL/textBase.h>

/**
  * desenha o texto a partir do ponto (x,y), crescendo em ambos os eixos
  */
void drawText(t_text *text, t_alphabet *ab, int x, int y);

#endif // TEXTDRAWER_H
