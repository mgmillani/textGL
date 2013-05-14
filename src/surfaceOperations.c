

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "surfaceOperations.h"

/**
  * converte uma SDL_Surface para uma textura do OpenGL
  */
GLuint surface2texture(SDL_Surface *surface)
{
	GLuint texture,width,height;
	if(surface->w == 0 || surface->h ==0)
		return 0;
	width = surface->w;
	height = surface->h;

	GLint ncolors,internalFormat;
	GLenum textureFormat;

	//determina o numero de canais da surface
	ncolors = surface->format->BytesPerPixel;

	switch(ncolors)
	{
		//com alpha channel
		case 4:
			internalFormat = GL_RGBA;
			if (surface->format->Rmask == 0xff00)
				textureFormat = GL_RGBA;
			else
				textureFormat = GL_BGRA;
			break;

		//sem alpha channel
		case 3:
			internalFormat = GL_RGB;
			if (surface->format->Rmask == 0xff)
				textureFormat = GL_RGB;
			else
				textureFormat = GL_BGR;
			break;
		default:
			fprintf(stderr,"Wrong number of colors :%d\n",ncolors);
			return 0;
	}

	//gera o handle da textura
	glGenTextures(1,&texture);

	//faz o binding da textura criada
	glBindTexture(GL_TEXTURE_2D,texture);

	//determina as propriedades de stretching da textura
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	//usa a surface para criar a textura
	glTexImage2D(GL_TEXTURE_2D,0,internalFormat,width,height,0,textureFormat,
								GL_UNSIGNED_BYTE,surface->pixels);

	SDL_FreeSurface(surface);

	return texture;
}

/**
  * usa a cor do pixel (0,0) como colorkey
  * adiciona um alphachannel a surface com base nessa colorkey
  */
SDL_Surface *surfaceRemoveBackground(SDL_Surface *surface)
{
	//determina a cor do pixel (0,0)
	Uint8 r,g,b;
	SDL_GetRGB(0,surface->format,&r,&g,&b);
	Uint32 rgb[3] = {r,g,b};
	Uint32 mask[3];
	mask[0] = surface->format->Rmask;
	mask[0] = surface->format->Gmask;
	mask[0] = surface->format->Bmask;
	Uint32 key = 0;

	//determina a chave
	unsigned int i;
	for(i=0 ; i<sizeof(key) ; i++)
	{
		int j;
		for(j=0 ; j<3 ; j++)
		{
			key |= rgb[j]&mask[j];
			rgb[j]<<=8;
		}
	}

	SDL_SetColorKey(surface, SDL_SRCCOLORKEY,key);
	//cria o alpha channel
	SDL_Surface *result = SDL_DisplayFormatAlpha(surface);
	//destroi a surface anterior
	SDL_FreeSurface(surface);

	return result;
}


























