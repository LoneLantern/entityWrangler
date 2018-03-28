#ifndef MISSIONCONTROL_H_INCLUDED
#define MISSIONCONTROL_H_INCLUDED
#include <SDL/SDL.h>
#include <vector>
#include <iostream>
#include <algorithm>
#define VECTOR_CONTAINS(v,x) (std::find(v.begin(), v.end(), x) != v.end())
#define VECTOR_FIND(v,x) std::find(v.begin(), v.end(), x)
class InputHandler{
private:
    SDL_Event *lastEvent;
    std::vector<SDL_Keycode> downKeys;
    int mouseX;
    int mouseY;
public:
    bool keyIsDown(SDL_Keycode code){
        return VECTOR_CONTAINS(this->downKeys,code);
    }
    std::vector<SDL_Keycode> &getDown(){
        return this->downKeys;
    }

    bool operator()(SDL_Event *event){
        switch(event->type){
            case(SDL_KEYUP):
                std::cout<<"key up"<<"\n";
                if(VECTOR_CONTAINS(this->downKeys,event->key.keysym.sym)){
                    this->downKeys.erase(VECTOR_FIND(this->downKeys,event->key.keysym.sym));
                }
                break;
            case(SDL_KEYDOWN):
                std::cout<<"key down"<<"\n";
                if(!VECTOR_CONTAINS(this->downKeys,event->key.keysym.sym)){
                    this->downKeys.push_back(event->key.keysym.sym);
                }
                break;
            case(SDL_MOUSEMOTION):
                if(event->type==SDL_MOUSEMOTION){
                    this->mouseX = event->motion.x;
                    this->mouseY = event->motion.y;
                }
                break;

        }
    }
};

class missionControl{
private:
    friend class InputHandler;
    bool running;
    bool threadRunning;
    SDL_Thread *thread;

    int returnThreads(bool wait = true);
public:
    missionControl();
    bool isRunning();
    void changeRunningState(bool state){
        this->running = state;
    }
    bool threadStatus(){
        return this->threadRunning;
    }
    InputHandler input;
    ~missionControl();
};

#endif // MISSIONCONTROL_H_INCLUDED
