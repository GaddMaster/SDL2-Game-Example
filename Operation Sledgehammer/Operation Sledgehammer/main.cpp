//MAIN INCLUDES LIMITED LIBRARIES SO AS GOOD FRO CROSS PLATEFORM
#include "Game.h"
#include "windows.h"
#include <iostream>

//FRAMES PER SECOND AND TIME DELAY VARIABLES
const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

//OUR MAIN FUNCTION
int main(int argc, char **argv)
{
	AllocConsole();
	FILE* myFile;
	freopen_s(&myFile, "CON", "w", stdout);
    Uint32 frameStart, frameTime;
    
    std::cout << "GAME INITIALIZATION ATTEMPT...\n";
    if(TheGame::Instance()->init("ALIEN ATTACK", 100, 100, 640, 480, false))//INITIALIZE THE GAME
    {
        std::cout << "GAME INITIALIZATION - SUCCESS!\n";
        while(TheGame::Instance()->running())//WHILE RUNNING IS TRUE LOOP
        {
			float ticks = SDL_GetTicks();
            frameStart = SDL_GetTicks();//WE MEASURE HOW LONG GAME IS RUNNING AND USE THAT FOR A OUR UPDATE FUNCTIONALITY 
            
			//THEGAME::INSTANCE IS A POINTER FOR OUR SINGLETON GAME CLASS
            TheGame::Instance()->handleEvents();
            TheGame::Instance()->update();
            TheGame::Instance()->render();
            
            frameTime = SDL_GetTicks() - frameStart;//TIMER
            
            if(frameTime < DELAY_TIME)
            {
                SDL_Delay((int)(DELAY_TIME - frameTime));
            }
        }
    }
    else
    {
        std::cout << "GAME INITIALIZE - FAILED - " << SDL_GetError() << "\n";//GAME FAILED TO INITILAIZE AND SDL ERROR IS PRINTED
        return -1;
    }
    
    std::cout << "GAME SHUTTING DOWN......\n";
    TheGame::Instance()->clean();//WE CLEAN UP ALL SDL AND HANDLES BEFORE EXITING
    
    return 0;
}
