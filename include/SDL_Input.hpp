
#ifndef SDL_INPUT_H
#define	SDL_INPUT_H

#include <SDL2/SDL.h>

class SDL_Input {
public:
    SDL_Input(void);
    virtual ~SDL_Input(void);

    bool                isFinished(void) const;
    void                updateEvent(void);
    bool                isKey(const SDL_Scancode) const;
    bool                isClick(const Uint8) const;
    int                 getX(void) const;
    int                 getY(void) const;
    int                 getXRel(void) const;
    int                 getYRel(void) const;
    void                showCursor(bool) const;
    bool				isMovementMouse(void) const;


private:
    bool                _finished;
    SDL_Event           _event;
    bool				_keys[SDL_NUM_SCANCODES];
    bool				_click[8];
    int					_x;
    int					_y;
    int					_xRel;
    int					_yRel;

    SDL_Input(SDL_Input const & rhs);
    SDL_Input &         operator=(SDL_Input const & rhs);

};

#endif	/* SDL_INPUT_H */

