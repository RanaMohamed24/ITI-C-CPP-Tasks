#include "./picture.h"
#include <SDL2/SDL.h>

int main() {
    Picture myPic;
    
   
    Circle cArr[1] = {
        Circle(320, 275, 25)   
    };
    
  
    Rect rArr[2];
    
 
    rArr[0] = Rect(280, 380, 360, 420); 
    
  
    Point myP1(310, 300);
    Point myP2(330, 380);
    rArr[1] = Rect(myP1, myP2); 
  
 
    Line* lArr = new Line[4];
    lArr[0] = Line(Point(320, 140), Point(240, 300));
    lArr[1] = Line(Point(320, 140), Point(400, 300));
    lArr[2] = Line(240, 300, 280, 300);
    lArr[3] = Line(360, 300, 400, 300);
  
    myPic.setCircles(1, cArr);
    myPic.setRects(2, rArr);
    myPic.setLines(4, lArr);
    
    myPic.print();
 
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return 1;
    }
    
    SDL_Window* window = SDL_CreateWindow("Draw- OOP C++",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          640, 480,
                                          SDL_WINDOW_SHOWN);
    if (window == NULL) {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    bool quit = false;
    SDL_Event e;
    
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        myPic.draw(renderer);
        
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    delete[] lArr;
    
    cout << "\nProgram ended successfully!" << endl;
    
    return 0;
}
