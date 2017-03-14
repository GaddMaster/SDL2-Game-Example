#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <iostream>
#include <vector>

#include "SDL.h"
#include "Vector2D.h"

//MOUSE INPUT VARIABLES
enum mouse_buttons
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler
{
	public://///////////////////////////////////////
    
		//SINGLETON POINTER TO INSTANCE
		static InputHandler* Instance()
		{
			if(s_pInstance == 0)
			{
				s_pInstance = new InputHandler();
			}
        
			return s_pInstance;
		}
    
		//INITIALIZE JOYSTICK
		void initialiseJoysticks();
		bool joysticksInitialised() const { return m_bJoysticksInitialised; }
    
		//?????
		void reset();
    
		//UPDATE & CLEAN THE INPUT HANDLER
		void update();
		void clean();
    
		//KEYBOARD EVENTS
		bool isKeyDown(SDL_Scancode key) const;
    
		//JOYSTICK EVENTS
		int getAxisX(int joy, int stick) const;
		int getAxisY(int joy, int stick) const;
		bool getButtonState(int joy, int buttonNumber) const;
    
		//MOUSE EVENTS
		bool getMouseButtonState(int buttonNumber) const;
		Vector2D* getMousePosition() const;
    
	private://///////////////////////////////////////
    
		//CONSTRUCTOR & DE-CONSTRUCTOR - PRIVATE - SINGLETON
		InputHandler();
		~InputHandler();
    
		//??????
		InputHandler(const InputHandler&);
		InputHandler& operator=(const InputHandler&);
    
		//PRIVATE FUNCTIONS TO HANDLE DIFFERENT EVENTS
		//HANDLE KEYBOARD EVENTS
		void onKeyDown();
		void onKeyUp();
    
		//HANDLE MOUSE EVENTS
		void onMouseMove(SDL_Event& event);
		void onMouseButtonDown(SDL_Event& event);
		void onMouseButtonUp(SDL_Event& event);
    
		//HANDLE JOYSTICK EVENTS
		void onJoystickAxisMove(SDL_Event& event);
		void onJoystickButtonDown(SDL_Event& event);
		void onJoystickButtonUp(SDL_Event& event);

		//MEMEBER VARIABLES
		//KEYBOARD SPECIFIC
		const Uint8* m_keystates;
    
		//JOYSTICK SPECIFIC
		std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
		std::vector<SDL_Joystick*> m_joysticks;
		std::vector<std::vector<bool>> m_buttonStates;
		bool m_bJoysticksInitialised;
		static const int m_joystickDeadZone = 10000;
    
		//MOUSE SPECIFIC
		std::vector<bool> m_mouseButtonStates;
		Vector2D* m_mousePosition;
    
		//SINGLETON INSTANCE POINTER
		static InputHandler* s_pInstance;
};

typedef InputHandler TheInputHandler;//SINGLETON INSTANCE TYPE DEFINITION

#endif//DEFINED INPUT_HANDLER_H
