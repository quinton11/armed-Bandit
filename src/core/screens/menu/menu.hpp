#pragma once
#include "SDL.h"
#include "../../../utils/components.hpp"

class MenuController
{
public:
    MenuController();
    ~MenuController();

    /* Holds all menus */
    /* Switches menus based on which is active */
    /*  */
    Menu mmain;  /* demo button custom button and best button */
    Menu custom; /* new model button and choose model button */
    Menu activeMenu;

    float bwidth = 140;
    float bheight = 25;
    float yspacing = 10;

    void setActiveMenu(std::string n);
    void setMenus(int sW, int sH,SDL_Renderer* r);
    void setMain(SDL_FRect c, float bs,SDL_Renderer* r);
    void setCustom(SDL_FRect c, float bs,SDL_Renderer* r);
    void renderMenu(SDL_Renderer *r);
    void inButton(bool isClicked, int mx, int my);
    bool mouseinplay(int mx, int my, SDL_FRect r);
};
