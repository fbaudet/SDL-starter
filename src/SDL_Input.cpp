
#include <SDL2/SDL_events.h>

#include "../include/SDL_Input.hpp"

/**
 *********************  CONSTRUCTORS / DESTRUCTORS  ********************
 */

SDL_Input::SDL_Input(void)
	: _finished(false), _x(0), _y(0), _xRel(0), _yRel(0)
{
	for (int i = 0; i < SDL_NUM_SCANCODES; ++i)
		_keys[i] = false;
	for (int i = 0; i < 8; ++i)
		_click[i] = false;
	return;
}

SDL_Input::~SDL_Input(void)
{
	return;
}

/**
 ********************  METHODS  ********************
 */

void					SDL_Input::updateEvent(void)
{
	_xRel = 0;
	_yRel = 0;

	while (SDL_PollEvent(&_event))
	{
		if (this->_event.type)
		{
			if (this->_event.type == SDL_WINDOWEVENT)
			{
				if (this->_event.window.event == SDL_WINDOWEVENT_CLOSE)
					this->_finished = true;
			}
			else if (this->_event.type == SDL_KEYUP)
				this->_keys[_event.key.keysym.scancode] = false;
			else if (this->_event.type == SDL_KEYDOWN)
				this->_keys[_event.key.keysym.scancode] = true;
			else if (this->_event.type == SDL_MOUSEBUTTONUP)
				this->_click[_event.button.button] = false;
			else if (this->_event.type == SDL_MOUSEBUTTONDOWN)
				this->_click[_event.button.button] = true;
			else if (this->_event.type == SDL_MOUSEMOTION)
			{
				this->_x = this->_event.motion.x;
				this->_y = this->_event.motion.y;
				this->_xRel = this->_event.motion.xrel;
				this->_yRel = this->_event.motion.yrel;
			}
		}
	}
}

void					SDL_Input::showCursor(bool b) const
{
	if (b)
		SDL_ShowCursor(SDL_ENABLE);
	else
		SDL_ShowCursor(SDL_DISABLE);
}

bool					SDL_Input::isMovementMouse(void) const
{
	if (this->getXRel() == 0 && this->getYRel() == 0)
		return false;
	else
		return true;
}

/**
 *******************  GETTERS  *******************
 */

bool					SDL_Input::isFinished(void) const
{
	return this->_finished;
}

bool					SDL_Input::isKey(const SDL_Scancode key) const
{
	return this->_keys[key];
}

bool					SDL_Input::isClick(const Uint8 click) const
{
	return this->_click[click];
}

int						SDL_Input::getX(void) const
{
	return this->_x;
}

int						SDL_Input::getY(void) const
{
	return this->_y;
}

int						SDL_Input::getXRel(void) const
{
	return this->_xRel;
}

int						SDL_Input::getYRel(void) const
{
	return this->_yRel;
}
