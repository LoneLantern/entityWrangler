#include <iostream>
#include <string>
#include "node.h"
#include "list.h"
#include "component.h"
#include <unordered_map>
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <random>
#include "systemCTypes.h"
#include "texture.h"
#include "window.h"
#include "font.h"
#include "testSystem.h"
#include <UnitTest++.h>
#include "userInput.h"
#include "bulletSystem.h"
<<<<<<< HEAD
=======
#include "action.h"
>>>>>>> Improved entity system. Some basic cleanup. Physics test
#include "texAnim.h"
#define STRMAP_TEMP_ARGS std::string,List<std::string>


using namespace std;
using namespace component;
typedef typename  std::unordered_map<STRMAP_TEMP_ARGS> stringMap;

template<class t>
void printList(List<t> &list){
    Node<t> *h = list.getHead();
    while(h){
        cout<<"\t*"<<h->getData()<<"\n";
        h=h->getNext();
    }
}

<<<<<<< HEAD
=======

>>>>>>> Improved entity system. Some basic cleanup. Physics test
template<class t>
void printComponentTableEnt(Component<t> &table, Entity &ent){
    cout<<"Entity "<<ent()<<" contains:\n";
    printList(table.getList(ent));

}



template<class t>
void printComponentTable(Component<t> &table){
    for(typename Component<t>::iterator begin = table.begin(), end = table.end();begin!=end;begin++){
        cout<<"Entity "<<begin->first<<" contains:\n";
        printList(begin->second);
    }
}

template <class t>
void printMap(stringMap &nodeMap,const t &name)
{
    cout<<name<<" contains:\n";
    Node<t> *h = nodeMap.at(name).getHead();
    while(h)
    {
        std::cout<<"\t*"<<h->getData()->c_str()<<"\n";
        h=h->getNext();
    }
}

void printLogo(){
    cout<<" ..............................................................................."<<"\n";
    cout<<" ................................................................ . . . . . . . "<<"\n";
    cout<<" .....................................................MMMNMMMMMMMM .. ... ... .."<<"\n";
    cout<<"....................................................=MMMMMMM8.MMMMMMMMM........."<<"\n";
    cout<<"..................................................,MMM...........  .MMMMM ... .."<<"\n";
    cout<<".................................................MMMM............ ... .MMM... .."<<"\n";
    cout<<"................................................MMM..........   ........MMM....."<<"\n";
    cout<<"...............................................MMMMMMMMMMMMMMMMM.........MMM...."<<"\n";
    cout<<"....................... ... .. .............   ..MMMMMMM~   . MMMO        MMN   "<<"\n";
    cout<<"MM$MM,. .D7MMD.. MM .. MM...M+DMO..,MIM, ..MNZM..MM ..MN..M$MM..MMM.       MMM7."<<"\n";
    cout<<"7M ..MM.MM ..MM..MM....MM..MM..MM.MM...MM.MM.. ...M+.OM  M ....  MMMN.     MMMMM"<<"\n";
    cout<<"MM ..NN MM ..MM  MZM. MZM .MM .MM.MM   MM ZM8     MM MD .MM        MMM      MMMM"<<"\n";
    cout<<"MM .....MM ..MM  M M..M.M .MMMMM .MM...MM...MM, ...MIM ...ZMM ..  .MMM      MM.M"<<"\n";
    cout<<"MM ..   MM ..MM .M M.M..M..MM.....MM...MM....?MM...NMO......MM.. .MM,       MMM "<<"\n";
    cout<<"MM ..MM MM ..MM  M ,M...M..MM.....MM...MM..M...M ...M... M ..MM.,MM.        MMM "<<"\n";
    cout<<".M+. MM. M. .MM .M..M..=M..MM.....MM   M?..M  .M....M....MM..MM.MM          MMN "<<"\n";
    cout<<"..MMMD...,MMMD.. M..M...M .MM ..   7MMM,   ,MMM  .  M  .  MMMM.MM=         .MM. "<<"\n";
    cout<<"................. ... ... ... ..................MMMMMMMMMMMMMM..           MMI  "<<"\n";
    cout<<"................................ ... ... ... ....MMM.... ... ...         NMMM   "<<"\n";
    cout<<"................................................. MMMM..........      ~MMMM8    "<<"\n";
    cout<<"................................ ... ... ... ... . .MMMMM... ...   MMMMMM.      "<<"\n";
    cout<<"................................ ... ... ... ... ... ,MMMMMMMMMMMMMMMM,MMM.     "<<"\n";
    cout<<"................. ... ... ... .. ... ... ... ... ... ... .MMMMMMMM..    ,MMM    "<<"\n";
    cout<<"................. ... ... ... .. ... ... ... ... ... ... ... ...          MMMM, "<<"\n";
    cout<<"................................................................          MMMM"  <<"\n";
    cout<<"................................ ... ... ... ... ... ... ... ...             .MM"<<"\n";
    cout<<"................................ ... ... ... ... ... ... ... ...                "<<"\n";
}

<<<<<<< HEAD
=======
void add(int x,int y){
    cout<<"Result:" << x+y<<"\n";
}
void printTime(float time){
    cout<<"Time: "<<time<<"\n";
}

>>>>>>> Improved entity system. Some basic cleanup. Physics test
bool randomBool(){
    srand(clock());
    return (bool)(rand()%10)/10;
}
<<<<<<< HEAD

=======
Uint64 artificialLag = 0;
>>>>>>> Improved entity system. Some basic cleanup. Physics test
int main(SDL_MAIN_PARAM)
{
    missionControl appC;
    UnitTest::RunAllTests();
    stringCT stringCTD;
    boolCT boolCTD;
    int16_tCT int16_tCTD;
    int32_tCT int32_tCTD;
    Window win("boy",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,700,700,0);
    TTF_Init();
    cout<<SDL_GetError()<<"\n";
    TTF_Font* font = TTF_OpenFont("./fonts/RobotoCondensed-Light.ttf",72);
    cout<<SDL_GetError()<<"\n";

//    REGISTERCOMP_TYPE(TestSystem,"TestSystem",TestSystem(textureCT&,transformCT&));
//    REGISTERCOMP_TYPE(Entity,"Entity",Entity());


    /*cTypes.new_usertype<Texture>("Texture",
                                 sol::constructors< Texture(const char*)>(),
                                 "use",&Texture::use);
    */
    CharSet characterSet(font);
    enid Man;
    enid TestEnt;
    Entity bullet;
    textureCT TexMgr;
    transformCT TransformMgr;
    tagCT TagMgr;
<<<<<<< HEAD
    BulletSystem sys(TagMgr,TransformMgr);

    TransformMgr.addTo(Man,-1.0f,-1.0f,0.0f);
    TransformMgr.addTo(TestEnt,-1.0f,1.0f,1.0f);
=======

    Man.setProtection(true);
    TestEnt.setProtection(true);

    TransformMgr.addTo(Man,-1.0f,-1.0f,0.0f);
    TransformMgr.addTo(TestEnt,0.0f,1.0f,1.0f);
>>>>>>> Improved entity system. Some basic cleanup. Physics test
    TexAnim *ptr = new TexAnim("./ship",24);
    cout<<"Giving TexAnim ptr with addr ("<<ptr<<")\n";

    cout<<"Test calling texAnim use pre insert\n";
    ptr->use();
<<<<<<< HEAD
    TexMgr.addTo(Man,ptr);

=======
    TagMgr.addTo(Man,"player");
>>>>>>> Improved entity system. Some basic cleanup. Physics test
    TestSystem system(TexMgr,TransformMgr);
    TagMgr.addTo(bullet,"bullet");
    TexMgr.addTo(bullet,new TexAnim("./bullet",24));
    TransformMgr.addTo(bullet,0.24f,0.6f,0.0f);
<<<<<<< HEAD

=======
    TexMgr.addTo(Man,ptr);
    Action testAct(&printLogo);
    testAct.act();

    Action addAct(&add,12,32);
    addAct.act();
    float time=0.0f;
    //Hook::add("update",&printTime);
>>>>>>> Improved entity system. Some basic cleanup. Physics test

  /*  for(char c=FONTRENDER_START;c<=FONTRENDER_END;c++){
        TexMgr.addTo(Man,characterSet.get(c));
    }*/
<<<<<<< HEAD
    TexMgr.addTo(TestEnt,"./demo.jpg");

=======
    //TexMgr.addTo(TestEnt,"./demo.jpg");

    BulletSystem sys(TagMgr,TransformMgr);
>>>>>>> Improved entity system. Some basic cleanup. Physics test

    cout<<"back to main..."<<"\n";
    try{
       // TestSystem& sys = Lua::getEnv()["sys"];

    cout<<"entering loop..."<<"\n";
<<<<<<< HEAD

    std::vector<std::shared_ptr<Entity>> bullets;
    time_t start = clock();
    int i = 0;
    while(appC.isRunning()){
=======
    cout<<"-";
    std::vector<std::shared_ptr<Entity>> bullets;
    cout<<"-";
    time_t start = clock();
    cout<<"-";
    int i = 0;
    cout<<"-";
    float conduct = 0.0f;
    bullet.setProtection(true);

    while(appC.isRunning()){
        //Hook::call("update",time);
        Vec3f playerPos = TransformMgr.get(Man).getData()->getPosition();
        Vec3f newPlayerPos;
        appC.startFrame();
>>>>>>> Improved entity system. Some basic cleanup. Physics test
        SDL_SetRenderDrawColor(Window::getActiveRenderer(),100,100,100,255);
        SDL_RenderClear(Window::getActiveRenderer());
        for(System& sys:System::getRegister()){
            sys.update();
        }
        if(appC.input.keyIsDown(SDLK_a)){
            Vec3f pos = TransformMgr.get(Man).getData()->getPosition();
<<<<<<< HEAD
            TransformMgr.get(Man).getData()->setPosition({pos.x+0.002f,pos.y,pos.z});
                        cout<<pos.x<<"|"<<pos.y<<"|"<<pos.z<<"\n";
=======
            TransformMgr.get(Man).getData()->setPosition({pos.x+2*missionControl::deltaTime(),pos.y,pos.z});
//cout<<pos.x<<"|"<<pos.y<<"|"<<pos.z<<"\n";
>>>>>>> Improved entity system. Some basic cleanup. Physics test

        }
        if(appC.input.keyIsDown(SDLK_d)){
            Vec3f pos = TransformMgr.get(Man).getData()->getPosition();
<<<<<<< HEAD
            TransformMgr.get(Man).getData()->setPosition({pos.x-0.002f,pos.y,pos.z});
            cout<<pos.x<<"|"<<pos.y<<"|"<<pos.z<<"\n";
=======
            TransformMgr.get(Man).getData()->setPosition({pos.x-2*missionControl::deltaTime(),pos.y,pos.z});
         //   cout<<pos.x<<"|"<<pos.y<<"|"<<pos.z<<"\n";
>>>>>>> Improved entity system. Some basic cleanup. Physics test
        }

        if(appC.input.keyIsDown(SDLK_w)){
            Vec3f pos = TransformMgr.get(Man).getData()->getPosition();
<<<<<<< HEAD
            TransformMgr.get(Man).getData()->setPosition({pos.x,pos.y+0.002,pos.z});
                        cout<<pos.x<<"|"<<pos.y<<"|"<<pos.z<<"\n";
=======
            TransformMgr.get(Man).getData()->setPosition({pos.x,pos.y+2*missionControl::deltaTime(),pos.z});
//cout<<pos.x<<"|"<<pos.y<<"|"<<pos.z<<"\n";
>>>>>>> Improved entity system. Some basic cleanup. Physics test

        }
        if(appC.input.keyIsDown(SDLK_s)){
            Vec3f pos = TransformMgr.get(Man).getData()->getPosition();
<<<<<<< HEAD
            TransformMgr.get(Man).getData()->setPosition({pos.x,pos.y-0.002f,pos.z});
            cout<<pos.x<<"|"<<pos.y<<"|"<<pos.z<<"\n";
=======
            TransformMgr.get(Man).getData()->setPosition({pos.x,pos.y-2*missionControl::deltaTime(),pos.z});
        //    cout<<pos.x<<"|"<<pos.y<<"|"<<pos.z<<"\n";
>>>>>>> Improved entity system. Some basic cleanup. Physics test
        }
        if(appC.input.keyIsDown(SDLK_LSHIFT)){
            Vec3f scale = TransformMgr.get(Man).getData()->getScale();
            TransformMgr.get(Man).getData()->setScale({scale.x+0.002f,scale.y+0.002f,scale.z});
<<<<<<< HEAD
            cout<<scale.x<<"|"<<scale.y<<"|"<<scale.z<<"\n";
=======
           // cout<<scale.x<<"|"<<scale.y<<"|"<<scale.z<<"\n";
>>>>>>> Improved entity system. Some basic cleanup. Physics test
        }
        if(appC.input.keyIsDown(SDLK_LCTRL)){
            Vec3f scale = TransformMgr.get(Man).getData()->getScale();
            TransformMgr.get(Man).getData()->setScale({scale.x-0.002f,scale.y-0.002f,scale.z});
<<<<<<< HEAD
            cout<<scale.x<<"|"<<scale.y<<"|"<<scale.z<<"\n";
        }
        if(true){
            Entity *newEnt = new Entity;
            //cout<<"size:"<<bullets.size();
            ComponentBase* arr[2];
            arr[0] = &TexMgr;
            arr[1] = &TagMgr;
          //  TagMgr.addTo(*newEnt,"bullet");
          //  cout<<*TagMgr[*newEnt].getHead()->getData()<<"\n";
           // TexMgr.addTo(*newEnt,new TexAnim("./bullet",24));            //cout<<"starting to copy";
=======
           // cout<<scale.x<<"|"<<scale.y<<"|"<<scale.z<<"\n";
        }
        newPlayerPos = TransformMgr.get(Man).getData()->getPosition();
        if(conduct>0.08f){
            Entity *newEnt = new Entity;
            //cout<<(*newEnt)()<<"\n";
            //cout<<"size:"<<bullets.size();
            ComponentBase* arr[2];
            arr[1] = &TexMgr;
            arr[0] = &TagMgr;
            //TagMgr.addTo(*newEnt,"bullet");
          //  cout<<*TagMgr[*newEnt].getHead()->getData()<<"\n";
            //TexMgr.addTo(*newEnt,new TexAnim("./bullet",24));            //cout<<"starting to copy";
>>>>>>> Improved entity system. Some basic cleanup. Physics test
            newEnt->copyComponents(bullet,arr,2);
            //cout<<"returned\n";
            TransformMgr.addTo(*newEnt,0,0,0);
            //cout<<"added\n";
            //cout<<"pushed\n";
<<<<<<< HEAD
        }
        if(appC.input.keyIsDown(SDLK_SPACE)){
            getchar();
        }
        SDL_PollEvent(NULL);
        win.swap();
        //cout<<(clock()-start)/(float)CLOCKS_PER_SEC<<"|"<<i<<"\n";
        start = clock();
        i++;
=======
            conduct = 0.0f;
        }


        win.swap();
        SDL_PollEvent(NULL);
       // std::cout<<"VX:\t"<<abs(newPlayerPos.x-playerPos.x)<<"\tVY:\t"<<abs(newPlayerPos.y-playerPos.y)<<"\tTime:\t"<<missionControl::deltaTime()<<"\n";
        start = clock();
        i++;
        conduct += appC.deltaTime();
        time += appC.deltaTime();
        TexMgr.clearCorpses();
        TagMgr.clearCorpses();
        TransformMgr.clearCorpses();
>>>>>>> Improved entity system. Some basic cleanup. Physics test
    }
    }catch(const std::exception &err){
        cout<<err.what()<<"\n";
    }
    /*stringCTD.addTo(Chest,"Sword");
    stringCTD.addTo(Chest,"Gold 100");

    stringCTD.addTo(Drawer,"Notes");
    stringCTD.addTo(Drawer,"Small First Aid");
    stringCTD.addTo(Drawer,"Needles");
    stringCTD.addTo(Drawer,"Blood vile");
    boolCTD.addTo(Drawer,false);
    boolCTD.addTo(Drawer,true);
    boolCTD.addTo(Drawer,true);
    boolCTD.addTo(Drawer,true);

    stringCTD.printTableContents();
    int16_tCTD.printTableContents();

    stringCTD.getList(Chest).printListContents();

    stringCTD.remove(Chest,0);
    stringCTD.printTableContents();
    system("pause");
    return 0;*/
    return 0;
}
