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
