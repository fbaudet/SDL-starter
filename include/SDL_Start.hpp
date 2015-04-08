
#ifndef SDL_START_H
#define SDL_START_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class SDL_Start {
public:
    SDL_Start(int width, int height, std::string title);
    virtual ~SDL_Start(void);

    bool                initSDL();
    void                mainLoop();

    int                 getHeight(void) const;
    std::string         getTitle(void) const;
    int                 getWidth(void) const;
    SDL_Window *        getWindow(void) const;
    bool                getFullScreen(void) const;

    void                setHeight(int);
    void                setTitle(std::string);
    void                setWidth(int);
    void                setWindow(SDL_Window*);
    void                setFullScreen(bool);

    void                swapFullScreen(void);
    void				showDisplayModes(void);

    class SDLException : public std::exception {
    public:
        virtual const char* what() const throw ();
    };

    const Uint8 *       state;

    static std::string  errorText;

protected:
    int                 _width;
    int                 _height;
    std::string         _title;
    bool                _fullscreen;
    bool                _continue;

    SDL_Window *        _window;
    SDL_Event           _event;

private:
    SDL_Start();
    SDL_Start(SDL_Start const & rhs);
    SDL_Start &         operator=(SDL_Start const & rhs);

};

std::ostream &          operator<<(std::ostream & o, SDL_Start const & rhs);

#endif	/* SDL_START_H */
