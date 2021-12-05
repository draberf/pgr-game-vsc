#include <iostream>
#include <SDL.h>
#include <geGL/geGL.h>
#include <geGL/StaticCalls.h>

using namespace ge::gl;

int main(int argc,char*argv[]){

  // initialize window

  SDL_Init(SDL_INIT_VIDEO);
  auto window = SDL_CreateWindow("pgr-game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1024,768,SDL_WINDOW_OPENGL);

  uint32_t version = 460;//context version
  uint32_t profile = SDL_GL_CONTEXT_PROFILE_CORE;//context profile
  uint32_t flags   = SDL_GL_CONTEXT_DEBUG_FLAG;//context flags
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, version/100 );
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,(version%100)/10);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK ,profile );
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS ,flags ); 

  auto context = SDL_GL_CreateContext(window);


  ge::gl::init();





  // loop

  bool running = true;
  while(running){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_QUIT)
        running = false;
    }  

    glClearColor(0,0.5,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
  
  }

  std::cout << "Done." << std::endl;




  return 0;
}