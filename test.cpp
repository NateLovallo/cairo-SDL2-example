/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include <cairo/cairo.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] )
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}

   window = SDL_CreateWindow( "SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 400, SDL_WINDOW_SHOWN );
   if( window == NULL )
   {
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
   }


   screenSurface = SDL_GetWindowSurface( window );


   SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0, 0, 0 ) );
   
   SDL_Surface *img = NULL;
   
   {
      int stride=600 * 4;
      unsigned char *image = (unsigned char*)calloc(stride*400, 1);

      cairo_surface_t *cairo_surface;
      cairo_surface = cairo_image_surface_create_for_data (image,
                      CAIRO_FORMAT_ARGB32,
                      600, 400, stride);

      cairo_t *cr=cairo_create(cairo_surface);
      
      cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
      cairo_set_line_width (cr, 10.0);
      cairo_arc (cr, 200, 200, 100, 45.0*(M_PI/180.0), 180.0*(M_PI/180.0));
      cairo_stroke (cr);

      /* Cleanup cairo */
      cairo_surface_destroy (cairo_surface);
      cairo_destroy (cr);
      Uint32 rmask, gmask, bmask, amask;

      rmask = 0x00ff0000;
      gmask = 0x0000ff00;
      bmask = 0x000000ff;
      amask = 0xff000000;

      img=SDL_CreateRGBSurfaceFrom( (void *) image, 600, 400, 32, stride, rmask, gmask, bmask, amask);
   }
   
   
   
   SDL_BlitSurface (img, NULL, screenSurface, NULL);

   bool run = true;
   
   while (run)
   {
      SDL_Event e;
      while( SDL_PollEvent( &e ) != 0 )
      {
         if(e.type == SDL_KEYDOWN)
         {
            run = false;
         }
         else if(e.type == SDL_QUIT)
         {
            run = false;
         }
      }
      
      
      
     

		//Update the surface
      SDL_UpdateWindowSurface( window );
	
   }

	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}
