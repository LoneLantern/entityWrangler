#include "userInput.h"
#include <iostream>

static int missionControlPrimaryRoutine(void* dat)
{
    missionControl *control = static_cast<missionControl*>(dat);
    while(control->threadStatus())
    {
        SDL_Event event;
        while(SDL_PollEvent(&event)!=0)
        {
            if(event.type==SDL_QUIT)
            {
                control->changeRunningState(false);
            }
            else
            {
                control->input(&event);
            }
        }
        //std::cout<<"threading...\n";
    }
}
missionControl* missionControl::cur = nullptr;
double missionControl::timeLastFrame = 0.1;
missionControl::missionControl()
{
    this->running = this->threadRunning = true;
    this->thread = SDL_CreateThread(missionControlPrimaryRoutine,"missionControlPrimaryRoutine",(void*) this);
    missionControl::cur = this;
    this->startFrame();

}

missionControl::~missionControl()
{
    this->returnThreads();
}


int missionControl::returnThreads(bool wait)
{
    this->threadRunning = false;
    int returnVal = 0;
    if(wait)
        SDL_WaitThread(this->thread,&returnVal);
    return returnVal;
}


bool missionControl::isRunning()
{
    return this->running;
}

