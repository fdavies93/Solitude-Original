#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_memfile.h>
#include "sol_graphicsStorage.h"
#include "sol_graphicsControl.h"
#include "sol_graphicsLayer.h"
#include "genericFunctions.h"
#include "sol_masterController.h"

using namespace std;

//LOADING COMPRESSED BITMAP DATA - SUPPORTS TRANSPARENCY
/*
    ALLEGRO_FILE* newFile = al_fopen("runAnim.png","rb");
    int64_t size = al_fsize(newFile);
    void* newFilePointer = al_malloc(size);
    al_fread(newFile,newFilePointer,al_fsize(newFile));//copies data of newFile into newFilePointer
    al_fclose(newFile);

    ALLEGRO_FILE* newMemFile = al_open_memfile(newFilePointer,size,"rb");
    ALLEGRO_BITMAP* newBitmap = al_load_bitmap_f(newMemFile,".png");
    al_fclose(newMemFile);
    free(newFilePointer);
*/
// ^ SAVED FOR LATER - WILL BE IMPORTANT IN GRAPHICS OPTIMISATION

//NOTE: up to about 10 million operations per second the speed is fairly constant; AT 10 million it will still run at 30fps
//above this it begins to slow down
int main(){
    sol_masterController controller(800,600,60,1);
    controller.startGameLoop();
    /*sol_graphicsStorage testStorage("settings/animationLoadList.csv","settings/bitmapLoadList.csv");
    testStorage.loadBitmapDataFromCSV("settings/bitmapLoadList.csv");
    bitmapData* theBitmap = testStorage.getBitmapData("bentPalmTree");
    cout << theBitmap->fileName << "\n";
    cout << theBitmap->x << "\n";
    cout << theBitmap->y << "\n";
    cout << theBitmap->width << "\n";
    cout << theBitmap->height << "\n";*/
    /*al_init();
    al_init_image_addon();
    al_install_keyboard();
    al_add_new_bitmap_flag(ALLEGRO_VIDEO_BITMAP);*/



  //ALLEGRO_DISPLAY* display = al_create_display(800, 600);

  /*ALLEGRO_FILE* file = al_fopen("walksequence_spritesheet.png", "rb");
  assert(file);

  int64_t size = al_fsize(file);
  assert(size > 0);

  void* data = malloc(size);
  al_fread(file, data, size);

  ALLEGRO_FILE* memfile = al_open_memfile(data, size, "rb");

  ALLEGRO_BITMAP* bitmap2 = al_load_bitmap_f(memfile, ".png");
  assert(bitmap2);

    al_draw_bitmap(bitmap2, 0, 0, 0);
   al_flip_display();
    return 0;*/


    /*sol_animation* newAnimation = new sol_animation("test.txt");
    sol_screenAnimation* theAnimation = new sol_screenAnimation(newAnimation, 0, 0);
    theAnimation->curFrame = 0;
    sol_graphicsQueue theQueue;
    sol_graphicsEventAnimationNextFrame* theEvent = new sol_graphicsEventAnimationNextFrame(theAnimation, &theQueue);
    theQueue.addEvent(10,(sol_graphicsEventVirtual*) theEvent);
    theQueue.addEvent(11,(sol_graphicsEventVirtual*) theEvent);
    theQueue.addEvent(12,(sol_graphicsEventVirtual*) theEvent);
    theQueue.addEvent(13,(sol_graphicsEventVirtual*) theEvent);
    theQueue.addEvent(14,(sol_graphicsEventVirtual*) theEvent);
    theQueue.addEvent(15,(sol_graphicsEventVirtual*) theEvent);
    theQueue.addEvent(16,(sol_graphicsEventVirtual*) theEvent);
    theQueue.addEvent(17,(sol_graphicsEventVirtual*) theEvent);
    theQueue.addEvent(18,(sol_graphicsEventVirtual*) theEvent);
    theQueue.printTree();*/
    //GameLoop();
    return 0;
}
