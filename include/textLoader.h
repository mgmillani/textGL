#ifndef TEXTLOADER_H
#define TEXTLOADER_H

#define surface2image(surface) surface2texture(surface)

#include <textGL/textBase.h>

/**
  * carrega o alfabeto especificado pelo arquivo de imagem e o de traducao
  * o arquivo de traducao deve estar no seguinte formato (usando apenas bytes, notacao little-endian)
  * <tamanho dos caracteres de entrada (em bytes)><numero de indices>
  * [<entrada><indice correspondente>...]
  * na imagem, o pixel da posicao (0,0) é considerado como cor de fundo
  * cada celula da imagem tera a mesma aspect-ratio da imagem
  * spaceProportion indica a largura de espacos em branco em relacao a largura das celulas do alfabeto
  */
t_alphabet* textLoadAlphabet(const char *imageFile, const char *translationFile,double spaceProportion, unsigned int rows);

/**
  * determina a largura de cada letra na imagem
  * retorna um tupla onde a primeira componente eh o menor x da letra (em relacao ao inicio da celula)
  * e a segunda componente eh a largura da letra
  */
t_uintTuple *textGetLetterWidth(SDL_Surface *image, unsigned int cellHeight, unsigned int cellWidth, unsigned int numRows);

/**
  * carrega o mapa de traducao, retornando-o
  * escreve o numero de posicoes do mapa em mapSize
  * o arquivo de traducao deve estar no seguinte formato:
  * <source size><index size>
  * [<source><index>...]
  * onde <source size> e <index size> sao bytes;
  * <source> e <index> estao em notacao big-endian e possuem o numero de bytes indicado pelo seu respectivo size
  * retorna 0 em caso de sucesso
  * escreve o mapa em *map
  * isEmpty sera 1 nas posicoes que nao foram definidas pelo arquivo de traducao, e 0 caso contrario
  */
int textLoadTranslation(const char *translationFile,unsigned int *mapSize, t_textChar **map, char **isEmpty);

#endif // TEXTLOADER_H


















