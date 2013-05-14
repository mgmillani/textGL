#include <stdio.h>
#include <stdlib.h>

#include <SDL/SDL_image.h>

#include "textLoader.h"
#include "file.h"
#include "textBase.h"
#include "surfaceOperations.h"

/**
  * carrega o alfabeto especificado pelo arquivo de imagem e o de traducao
  * o arquivo de traducao deve estar no seguinte formato (usando apenas bytes, notacao little-endian)
  * <tamanho dos caracteres de entrada (em bytes)><numero de indices>
  * [<entrada><indice correspondente>...]
  * na imagem, o pixel da posicao (0,0) é considerado como cor de fundo
  * cada celula da imagem tera a mesma aspect-ratio da imagem
  * spaceProportion indica a largura de espacos em branco em relacao a largura das celulas do alfabeto
  */
t_alphabet* textLoadAlphabet(const char *imageFile, const char *translationFile,double spaceProportion, unsigned int rows)
{
	//carrega o mapa de traducao
	unsigned int mapSize;
	t_textChar *map;
	char *isEmpty;
	if(textLoadTranslation(translationFile,&mapSize,&map,&isEmpty)!=0)
		return NULL;

	//carrega a imagem
	SDL_Surface *raw = IMG_Load(imageFile);
	if(raw==NULL)
	{
		free(map);
		return NULL;
	}
	//determina o tamanho das celulas
	unsigned int ch = raw->h/rows;
	unsigned int cw = raw->w/rows;
	//faz com que o fundo fique transparente
	raw = surfaceRemoveBackground(raw);
	//determina a largura de cada letra
	t_uintTuple *width = textGetLetterWidth(raw,ch,cw,rows);
	//converte a surface para uma imagem
	t_image img = surface2image(raw);

	//cria o alfabeto
	t_alphabet *ab = malloc(sizeof(*ab));
	ab->alphabet = img;
	ab->cellW = cw;
	ab->cellH = ch;
	ab->spaceWidth = spaceProportion*cw;
	ab->translation = map;
	ab->isEmpty = isEmpty;
	ab->mapSize = mapSize;
	ab->width = width;
	ab->rows = rows;

	return ab;
}

/**
  * determina a largura de cada letra na imagem
  * retorna um tupla onde a primeira componente eh o menor x da letra (em relacao ao inicio da celula)
  * e a segunda componente eh a largura da letra
  */
t_uintTuple *textGetLetterWidth(SDL_Surface *image, unsigned int cellHeight, unsigned int cellWidth, unsigned int numRows)
{

	t_uintTuple *width = (t_uintTuple *)malloc(numRows*numRows*(sizeof(*width)));
	unsigned int cells = numRows * numRows;

	//dummy: retorna o tamanho da celula
	unsigned int i;
	for(i=0 ; i<cells ; i++)
	{
		width[i].first = 0;
		width[i].second = cellWidth-1;
	}

	return width;

}

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
int textLoadTranslation(const char *translationFile,unsigned int *mapSize, t_textChar **map, char **isEmpty)
{
	unsigned int fileSize;
	unsigned char *data = (unsigned char *)readBinFile(translationFile,&fileSize);
	if(data==NULL)
		return 1;

	unsigned int i=0;
	//le a largura de source
	unsigned char sourceSize = data[i++];
	//le a largura do indice
	unsigned char indexSize = data[i++];
	//calcula a largura do mapa
	//o mapa deve suportar qualquer valor de entrada
	*mapSize = 1<<(sourceSize*8);
	*map = malloc(sizeof(*map)*(*mapSize));
	*isEmpty = malloc(sizeof(*isEmpty)*(*mapSize));
	//todos os caracteres nao definidos serao empty
	unsigned int j;
	for(j=0 ; j<*mapSize ; j++)
		(*isEmpty)[j] = 1;


	//le o mapa
	while(i<fileSize)
	{
		unsigned int r;
		//le source
		unsigned int source = data[i++];
		for(r=1 ; r<sourceSize ; r++,i++)
		{
			source <<= 8;
			source |= data[i];
		}
		//le index
		unsigned int index = data[i++];
		for(r=1 ; r<indexSize ; r++,i++)
		{
			index <<= 8;
			index |= data[i];
		}

		(*map)[source] = index;
		(*isEmpty)[source] = 0;

	}

	free(data);

	return 0;
}

