/*exists inside graphicsCache and is passed to the graphics loading thread as an argument.
its purpose is to carry out operations from the cache as regards graphics (un)loading.
for this purpose it exchanges messages with graphicsCache.*/
#ifndef _GRAPHICS_LOADER_INCLUDED_
#define _GRAPHICS_LOADER_INCLUDED_
#include <queue>
#include <allegro5/allegro.h>
#include "sol_logicConstants.h"
#include "graphicsThreadMessage.h"
#include "graphicsCache.h"
using namespace std;
//forward declaration to avoid awkward problems

static void* startGraphicsThread(ALLEGRO_THREAD*, void*);

class graphicsLoader{
    friend class graphicsCache;
    friend void* startGraphicsThread(ALLEGRO_THREAD*, void*);
    private:
        ALLEGRO_MUTEX* messageQueueMutex;//prevents messages being added/removed at same time
        //ALLEGRO_COND* messageQueueCondition;//fired when message is successfully added
        //bool messageQueueReady;
        ALLEGRO_COND* messaged;//wakes up thread when message is sent
        ALLEGRO_THREAD* loadThread;
        bool stopLoadThread;
        queue<graphicsThreadMessage*> messageQueue;
        bool activated;//same as above
        bool end;
        graphicsCache* myCache;

        void loadAnimation(animation*);
        void loadBitmap(sol_bitmap*);
        ALLEGRO_BITMAP* loadSpriteSheet(string);

        bool runMessage(graphicsThreadMessage*);

        bool shouldActivate;

        bool spriteActivated;
        ALLEGRO_COND* spriteCondition;
    public:
        graphicsLoader();

        void start(graphicsCache*);
        bool addMessage(sol_graphicsMessageTypes, void*);
        void activate();//wakes up thread to message
};

#endif
