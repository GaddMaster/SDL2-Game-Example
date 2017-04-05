#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>
#include <vector>

class GameState
{
	public://///////////////////////////////////////
		
		virtual ~GameState() {}
    
		//PURE VIRTUAL FUNCTIONS MUST BE IMPLEMENTED IN ALL INHERITED CLASSES
		virtual void update() = 0;
		virtual void render() = 0;
		virtual bool onEnter() = 0;
		virtual bool onExit() = 0;
		virtual std::string getStateID() const = 0;

		//RESUME CURRENT GAME STATE
		virtual void resume(){}
    
	protected://///////////////////////////////////////
    
		GameState() : m_loadingComplete(false), m_exiting(false){}
		bool m_loadingComplete;
		bool m_exiting;
		
		//VECTOR OF STRINGS - TEXTURE ID's
		std::vector<std::string> m_textureIDList;
};

#endif//DEFINE GAME_STATE_H
