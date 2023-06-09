#include "overlay.h"
#include <iostream>
#include "../home/homescreen.h"
#include "../../../utils/utils.h"

Overlay::Overlay()
{
    skip = Button{"skip", false, false};

    demo.title = "Demo Mode";
    demo.content =
        " In this mode the user controls the agent.\n Agent is allowed six buttons to press where\n each button carries a unique weight.\n The weight in question being hid.\n You're allowed five button hits.\n Your weight hits at the end of the episode\n shouldn't be less than twenty ;).\n Good Luck!";

    custom.title = "Custom Mode";
    custom.content = " In this mode the agent is automatic.\n Agent is allowed six buttons to press where\n each button carries a unique weight.\n The weight in question being hid.\n Agent is allowed five button hits.\n Total weight hits at the end of the episode\n shouldn't be less than twenty. \n Good Game!";

    best.title = "Best Mode";
    best.content = " In this mode the agent is automatic.\n Agent is allowed six buttons to press where\n each button carries a unique weight.\n The weight in question being hid.\n Agent is allowed five button hits.\n Total weight hits at the end of the episode\n shouldn't be less than twenty. \n Good Game!";
}
Overlay::~Overlay() {}

void Overlay::render(SDL_Renderer *r)
{

    while (ismounted)
    {
        SDL_RenderClear(r);

        eventChecker();

        // render containers

        SDL_SetRenderDrawColor(r, 42, 49, 54, SDL_ALPHA_OPAQUE);

        SDL_RenderFillRectF(r, &container);

        // render title
        SDL_RenderCopyF(r, current->titleT, nullptr, &titleCon);

        // render content
        SDL_RenderCopyF(r, current->contentT, nullptr, &contentCon);

        // render skipbutton
        if (skip.isActive)
        {
            SDL_RenderCopyF(r, skip.hovertext, nullptr, &skip.rect);
        }
        else
        {
            SDL_RenderCopyF(r, skip.text, nullptr, &skip.rect);
        }

        SDL_SetRenderDrawColor(r, 10, 10, 10, SDL_ALPHA_OPAQUE);

        SDL_RenderPresent(r);
    }
}
void Overlay::eventChecker()
{
    while (SDL_PollEvent(&events))
    {
        switch (events.type)
        {
        case SDL_QUIT:
            ismounted = false;
            HomeScreen::quit = true;
            HomeScreen::ismounted = false;

            break;

        case SDL_MOUSEMOTION:
            mx = events.motion.x;
            my = events.motion.y;
            skipTrigger(false);

        case SDL_MOUSEBUTTONDOWN:
            if (events.button.button == SDL_BUTTON_LEFT)
            {
                // std::cout << "Mouse click event" << std::endl;
                skipTrigger(true);

                // mc.inButton(true, mousex, mousey);
            }
        }
    }
}

bool Overlay::mouseinplay(int mx, int my, SDL_FRect r)
{
    return (mx >= r.x) && (my >= r.y) &&
           (mx < r.x + r.w) && (my < r.y + r.h);
}

void Overlay::skipTrigger(bool isClicked)
{
    skip.isActive = false;
    if (mouseinplay(mx, my, skip.rect))
    {
        skip.isActive = true;

        if (isClicked)
        {
            // unmount overlay
            // unmount overlay and homescreen and move to actual game loop
            ismounted = false;
            HomeScreen::ismounted = false;
        }
    }
}

void Overlay::setOverlay(std::string title)
{
    if (title == demo.title)
    {
        current = &demo;
    }
    else if (title == custom.title)
    {
        current = &custom;
    }
    else if (title == best.title)
    {
        current = &best;
    }
    ismounted = true;
}

void Overlay::setStructure(int sW, int sH, SDL_Renderer *r)
{
    float cx, cy;
    cx = (float)sW / 2;
    cy = (float)sH / 2;

    // set main overlay
    container.x = cx - width / 2;
    container.y = cy - height / 2;
    container.w = width;
    container.h = height;

    // set overlay title
    titleCon.w = 140;
    titleCon.h = 25;
    titleCon.x = cx - titleCon.w / 2;
    titleCon.y = container.y + 10;

    // set overlay content
    contentCon.w = container.w - 10;
    contentCon.h = container.h - titleCon.h - 80;
    contentCon.x = container.x + 5;
    contentCon.y = container.y + titleCon.h + 20;
    // set overlay skip button
    // button right
    skip.rect.w = 100;
    skip.rect.h = 20;
    skip.rect.x = container.x + container.w - 5 - skip.rect.w;
    skip.rect.y = container.y + container.h - 5 - skip.rect.h;

    std::pair<SDL_Texture *, SDL_Texture *> res = Util::getTextPairR(r, skip.name, skip.rect);
    skip.rect.x = cx - skip.rect.w / 2;

    skip.text = res.first;
    skip.hovertext = res.second;

    // produce texts for each overlay
    // demo
    std::pair<SDL_Texture *, SDL_Texture *> resd = Util::getTextPairR(r, demo.title, titleCon);
    titleCon.x = cx - titleCon.w / 2;
    demo.titleT = resd.first;
    demo.contentT = Util::getBlockText(r, demo.content, contentCon);

    // custom
    resd = Util::getTextPairR(r, custom.title, titleCon);
    custom.titleT = resd.first;
    custom.contentT = Util::getBlockText(r, custom.content, contentCon);

    // best
    resd = Util::getTextPairR(r, best.title, titleCon);
    best.titleT = resd.first;
    best.contentT = Util::getBlockText(r, best.content, contentCon);

    // content text
}
