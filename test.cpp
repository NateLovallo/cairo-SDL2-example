#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cairo/cairo.h>

int main(int argc, char* args[])
{
	SDL_Surface* screenSurface = NULL;
   
   if (SDL_Init(SDL_INIT_VIDEO) < 0) 
   {
      fprintf(stderr,"ERROR in SDL_Init(): %s\n",SDL_GetError());
      return -1;
   }
   
   SDL_ShowCursor(SDL_DISABLE);
   
   SDL_Window* window = window = SDL_CreateWindow( "SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 400, SDL_WINDOW_SHOWN );
   if (window == NULL)
   {
      fprintf(stderr,"ERROR in SDL_CreateWindow(): %s\n",SDL_GetError());
      return -1;
   }

   SDL_Renderer* myRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
   if( myRenderer == NULL )
   {
      fprintf(stderr,"Coudln't make renderino %s\n",SDL_GetError());
      return -1;
   }

   /////////////////////////////////////////////////////////////////////
   SDL_Texture* myTex = NULL;

   int stride= 400 * 4;
   unsigned char *image = (unsigned char*)calloc(stride*400, 1);
   Uint32 rmask, gmask, bmask, amask;

   rmask = 0x00ff0000;
   gmask = 0x0000ff00;
   bmask = 0x000000ff;
   amask = 0xff000000;

   double rotate = 0.0;
   
   /////////////////////////////////////////////////////////////////////
   bool run = true;
   
   while (run)
   {
      SDL_Event e;
      // something is happen!
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
      
      SDL_SetRenderDrawColor(myRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
      SDL_RenderClear( myRenderer );
      
      // This can almost certainly be optimized
      // because i wrote it
      // :(
      
      // draw an arc in cairo
      {
         cairo_surface_t *cairo_surface;
         
         cairo_surface = cairo_image_surface_create_for_data (image,
               CAIRO_FORMAT_ARGB32,
               400, 400, stride);

         cairo_t *cr=cairo_create(cairo_surface);
         
         // probably dont need this
         // wait wtf i do
         cairo_set_source_rgb (cr, 0, 0, 0);
         cairo_paint (cr);
         
         cairo_set_source_rgba (cr, 0, 1, 0, 0.5);
         cairo_set_line_width (cr, 10.0);
         cairo_arc (cr, 200, 200, 100, (rotate)*(M_PI/180.0), (rotate+270.0)*(M_PI/180.0));
         cairo_stroke (cr);

         cairo_surface_destroy (cairo_surface);
         cairo_destroy (cr);
      }
      
      // render the cairo data to a texture
      {
         SDL_Surface* img = SDL_CreateRGBSurfaceFrom( (void *) image, 400, 400, 32, stride, rmask, gmask, bmask, amask);
         SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat( img, SDL_PIXELFORMAT_RGBA8888, 0 );
         SDL_FreeSurface( img );

         myTex = SDL_CreateTextureFromSurface( myRenderer, formattedSurface );
         
         SDL_FreeSurface( formattedSurface );
      }


      // draw to screen
      SDL_RenderCopy( myRenderer, myTex, NULL, NULL);
      
      
      // flip buffer
      SDL_RenderPresent(myRenderer);
      
      SDL_DestroyTexture( myTex );
      
      memset(image, 0, sizeof(image));
      
      rotate += 1.0;
      if (rotate >= 360.0)
      {
         rotate = 0.0;
      }
      
      // TODO frame timer?
      SDL_Delay(20);
   }
   
   SDL_DestroyTexture( myTex );
   SDL_DestroyRenderer(myRenderer);
   SDL_DestroyWindow(window);

   SDL_Quit();
   return 0;
}

