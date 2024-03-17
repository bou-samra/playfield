/********************************************************
 ** FILENAME   : playfield.c                           **
 ** AUTHOR     : Jason Bou-Samra                       **
 **            : Paragon                               **
 ** DATE       : 09/01/2023                            **
 ** DESCRIPTION: amiga 1000 playfield example          **
 ** NOTES      : a recreation of the amiga 1000        **
 **              playfield example in C/SDL            **
 ** CHANGES    : see changes.txt                       **
 ********************************************************/
/* to compile: cc name.c -lSDL2 -lm */

#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>

int initSDL (void);
int shutdownSDL (void);
int do_playfield(void);

bool quit = false;                  /* quit flag */

SDL_Window *window = NULL;
SDL_Renderer *sr;
SDL_Event event;

int p1x, p2x, line;

/* window paramaters */
#define WIDTH 640					/* pixels */
#define HEIGHT 512					/* pixels */
#define TITLE "Playfield Example"	/* window title */

int main (void)
{
  initSDL ();
  SDL_RenderSetScale (sr, 2.0, 2.0);			/* scale x2 */

  while (quit == false)
    {

      while (SDL_PollEvent (&event))
	{
	  if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
	    {
	      quit = true;
	    }
	}
      if (quit)
	{
	  break;
	}

do_playfield();

 SDL_Delay(50);
    }
  shutdownSDL ();					/* bye */
}

/* initialise SDL */
int initSDL ()
{
  SDL_Init (SDL_INIT_EVERYTHING);

/* new window */
  window = SDL_CreateWindow (TITLE,			/* title */
			     SDL_WINDOWPOS_UNDEFINED,	/* x pos */
			     SDL_WINDOWPOS_UNDEFINED,	/* w pos */
			     WIDTH,			/* width */
			     HEIGHT,			/* height */
			     0);			/* Additional flag(s) */

  /* deal with error */
  if (window == NULL)
    {
      fprintf (stderr, "SDL window failed to initialise: %s\n",
	       SDL_GetError ());
      return 1;
    }

/* creater renderer */
  sr = SDL_CreateRenderer (window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

/* shutdown routine */
int shutdownSDL ()
{
  SDL_DestroyWindow (window);				/* free memory */
  SDL_Quit ();						/* shutdown entire sdl sub-systems */
  return 0;
}

int do_playfield()
{
  SDL_SetRenderDrawColor (sr, 0xFF, 0x00, 0x00, 0xFF); /* background */
  SDL_RenderClear (sr); 
  SDL_SetRenderDrawColor (sr, 0xFF, 0xFF, 0x00, 0xFF); /* set pen colour*/

line=0;
  for (int i=0; i<200; i++)  // 200 lines
{
  p1x=0; p2x=7;

for (int j=0; j<20; j++) // #FF00FF00 recreate pattern
{
  SDL_RenderDrawLine (sr, p1x, line, p2x, line);

      p2x=p2x+16;
      p1x=p1x+16;
//      printf("%i %i %i\n", line, p1x, p2x);
}
  line=line+1;
  }
    SDL_RenderPresent (sr);
}

/* author*/
char author[] = { "amiga 1000 playfield example" };
const char* text = "by commodore amiga inc.";
