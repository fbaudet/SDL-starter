
#ifndef SDL_INPUT_H
#define	SDL_INPUT_H

#include <SDL2/SDL.h>

class SDL_Input {
public:
    SDL_Input(void);
    virtual ~SDL_Input(void);

    bool                isFinished(void) const;
    void                updateEvent(void);

private:
    SDL_Event           _event;
    bool                _finished;

    SDL_Input(SDL_Input const & rhs);
    SDL_Input &         operator=(SDL_Input const & rhs);

};

#endif	/* SDL_INPUT_H */

