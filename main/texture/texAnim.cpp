#include "texAnim.h"
#include <boost/filesystem.hpp>
#include <ctime>
#include <iostream>

using namespace boost::filesystem;
using namespace std;

void TexAnim::initFromFolder(const char* folder)
{
    directory_iterator end_itr;

    for (directory_iterator itr(folder); itr != end_itr; ++itr)
    {
        try
        {
            if (is_regular_file(itr->path()))
            {
                string current_file = itr->path().string();
                std::cout<<current_file.c_str()<<"\n";

                frames.push_back(std::make_shared<Texture>(current_file.c_str()));
            }
        }
        catch(...)
        {
        }
    }
}


TexAnim::TexAnim(const char* folder,float fps)
    :fps(fps),Texture()
{
    this->initFromFolder(folder);
    this->time_start = -1;
}

static float getTime()
{
    return clock()/(float)CLOCKS_PER_SEC;
}

Texture* TexAnim::get()
{
    return &*this->frames.at((int)((getTime()-this->time_start)*(this->fps))%this->frames.size());
}


SDL_Texture* TexAnim::use(GLenum channel)
{
//    std::cout<<"tex anim use called\n";
    if(this->time_start == -1)
    {
        this->time_start = getTime();
    }
    // std::cout<<(int)((getTime()-this->time_start)*(this->fps))%this->frames.size()<<"\t";
    return this->get()->use(channel);
}

SYSTEM_NAMESPACE::Vec2i TexAnim::getPxDimensions()
{
    return this->get()->getPxDimensions();
}

SYSTEM_NAMESPACE::Vec2i TexAnim::getPxDimensions(SYSTEM_NAMESPACE::Vec3f scale)
{
    return this->get()->getPxDimensions(scale);
}
