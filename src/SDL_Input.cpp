
#include <SDL2/SDL_events.h>

#include "../include/SDL_Input.hpp"

SDL_Input::SDL_Input(void)
: _finished(false) {
    return;
}

SDL_Input::~SDL_Input(void) {
    return;
}

bool                    SDL_Input::isFinished(void) const {
    return this->_finished;
}

void                    SDL_Input::updateEvent() {
    while (SDL_PollEvent(&_event)) {
        if (_event.type) {
            if (_event.type == SDL_WINDOWEVENT) {
                if (_event.window.event == SDL_WINDOWEVENT_CLOSE)
                    this->_finished = true;
            }
        }
    }
}
