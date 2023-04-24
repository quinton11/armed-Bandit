#include "menu.h"
#include "../../../utils/utils.h"
#include "../../env/env.h"
#include <iostream>

MenuController::MenuController()
{
    // Create menus
    // main menu
    Button *demo = new Button{"demo", false, false};
    Button *cust = new Button{"custom", false, false};
    Button *best = new Button{"best", false, false};
    mmain = Menu{
        "main-menu", {demo, cust, best}, true, false};

    // custom menu
    Button *newAgent = new Button{"create", false, false};
    Button *selectAgent = new Button{"select", false, false};
    Button *back = new Button{"back", false, false};
    custom = Menu{"custom-menu", {newAgent, selectAgent, back}, false, false};

    ol = Overlay();
}
MenuController::~MenuController() {}

void MenuController::setActiveMenu(std::string n)
{
    if (n == mmain.name)
    {
        activeMenu = mmain;
        return;
    }
    activeMenu = custom;
    return;
}

void MenuController::setMenus(int sW, int sH, SDL_Renderer *r)
{
    float cP = 0.7;
    float bsy = 0.6;

    // using screen width and height
    // draw and populate button rects

    // right side of screen or from 70% of screen width to screen width
    // will hold the menu
    float cx = cP * sW;
    float cw = sW - cx;
    SDL_FRect c = {cx, 0, cw, (float)sH};

    //
    float bstarty = bsy * sH;

    // set each menu
    setMain(c, bstarty, r);
    setCustom(c, bstarty, r);

    setActiveMenu("main-menu");
    ol.setStructure(sW, sH, r);
}

void MenuController::setMain(SDL_FRect c, float bs, SDL_Renderer *r)
{
    float cx = c.x + c.w / 2;
    float bx = cx - bwidth;
    // main menu buttons
    // demo button
    SDL_FRect drect = {bx, bs, bwidth, bheight};

    // cust button
    SDL_FRect crect = {bx, drect.y + bheight + yspacing, bwidth, bheight};

    // best button
    SDL_FRect brect = {bx, crect.y + bheight + yspacing, bwidth, bheight};

    std::pair<SDL_Texture *, SDL_Texture *> txtPair;

    for (std::list<Button *>::iterator b = mmain.buttons.begin(); b != mmain.buttons.end();)
    {
        if ((*b)->name == "demo")
        {
            (*b)->rect = drect;
        }
        else if ((*b)->name == "custom")
        {
            (*b)->rect = crect;
        }
        else if ((*b)->name == "best")
        {
            (*b)->rect = brect;
        }

        // textures
        std::cout << "In get text pair" << std::endl;
        txtPair = Util::getTextPairR(r, (*b)->name, (*b)->rect);

        (*b)->rect.x = cx - (*b)->rect.w / 2;
        (*b)->text = txtPair.first;
        (*b)->hovertext = txtPair.second;

        b++;
    }
}
void MenuController::setCustom(SDL_FRect c, float bs, SDL_Renderer *r)
{
    float cx = c.x + c.w / 2;
    float bx = cx - bwidth;
    // custom menu buttons
    // new agent button
    SDL_FRect narect = {bx, bs, bwidth, bheight};

    // select agent button
    SDL_FRect sarect = {bx, narect.y + bheight + yspacing, bwidth, bheight};

    // back button
    SDL_FRect brect = {bx, sarect.y + bheight + yspacing, bwidth, bheight};

    std::pair<SDL_Texture *, SDL_Texture *> txtPair;

    for (std::list<Button *>::iterator b = custom.buttons.begin(); b != custom.buttons.end();)
    {
        if ((*b)->name == "create")
        {
            (*b)->rect = narect;
        }
        else if ((*b)->name == "select")
        {
            (*b)->rect = sarect;
        }
        else if ((*b)->name == "back")
        {
            (*b)->rect = brect;
        }

        // textures
        txtPair = Util::getTextPairR(r, (*b)->name, (*b)->rect);

        (*b)->rect.x = cx - (*b)->rect.w / 2;
        (*b)->text = txtPair.first;
        (*b)->hovertext = txtPair.second;

        b++;
    }
}

void MenuController::renderMenu(SDL_Renderer *r)
{
    int s;

    for (std::list<Button *>::iterator b = activeMenu.buttons.begin(); b != activeMenu.buttons.end();)
    {
        SDL_SetRenderDrawColor(r, 255, 255, 0, SDL_ALPHA_OPAQUE);
        if ((*b)->isActive)
        {
            SDL_RenderCopyF(r, (*b)->hovertext, nullptr, &(*b)->rect);
            // std::cout << "Is Active" << std::endl;
        }
        else
        {
            SDL_RenderCopyF(r, (*b)->text, nullptr, &(*b)->rect);
        }

        b++;
    }

    // render ol
    ol.render(r);
}

void MenuController::inButton(bool isClicked, int mx, int my)
{
    std::list<Button *>::iterator b;
    if (activeMenu.name == mmain.name)
    {
        // main menu
        for (b = activeMenu.buttons.begin(); b != activeMenu.buttons.end();)
        {
            (*b)->isActive = false;
            if (mouseinplay(mx, my, (*b)->rect))
            {
                (*b)->isActive = true;
                if (isClicked)
                {
                    if ((*b)->name == "demo")
                    {
                        std::cout << "Demo button" << std::endl;
                        ol.setOverlay("Demo Mode");
                        // set game mode
                        Env::gMode = GameMode::Demo;
                    }
                    else if ((*b)->name == "custom")
                    {
                        std::cout << "Custom button" << std::endl;
                        activeMenu = custom;
                        Env::gMode = GameMode::Custom;
                    }
                    else if ((*b)->name == "best")
                    {
                        std::cout << "Best button" << std::endl;
                        Env::gMode = GameMode::Best;
                    }
                }
                break;
            }
            b++;
        }
    }
    else if (activeMenu.name == custom.name)
    {
        // custom menu
        for (b = activeMenu.buttons.begin(); b != activeMenu.buttons.end();)
        {
            // b->isActive = false;
            (*b)->isActive = false;

            if (mouseinplay(mx, my, (*b)->rect))
            {
                (*b)->isActive = true;

                if (isClicked)
                {
                    if ((*b)->name == "create")
                    {
                        std::cout << "New Agent button" << std::endl;
                    }
                    else if ((*b)->name == "select")
                    {
                        std::cout << "Select Agent button" << std::endl;
                    }
                    else if ((*b)->name == "back")
                    {
                        std::cout << "Back button" << std::endl;
                        activeMenu = mmain;
                    }
                }
                break;
            }
            b++;
        }
    }
}

bool MenuController::mouseinplay(int mx, int my, SDL_FRect r)
{
    return (mx >= r.x) && (my >= r.y) &&
           (mx < r.x + r.w) && (my < r.y + r.h);
}