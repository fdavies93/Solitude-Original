#include "sol_masterController.h"
#include "sol_logicConstants.h"
#include "graphicsCache.h"
#include <allegro5/allegro.h>
using namespace std;

sol_masterController::sol_masterController(unsigned int displayWidth, unsigned int displayHeight, unsigned int framesPerSecond, unsigned int pixelsPerMetre){
    al_init();
    al_init_image_addon();
    al_add_new_bitmap_flag(ALLEGRO_VIDEO_BITMAP);
    display = al_create_display(displayWidth,displayHeight);
    timer = al_create_timer(1.0/framesPerSecond);
    queue = al_create_event_queue();
    graphicsController = new sol_graphicsControl("settings/animationLoadList.csv","settings/bitmapLoadList.csv");
    logicController = new sol_logicController(timer);
    renderPipeline = new sol_logicToGraphicsConverter(graphicsController,pixelsPerMetre,timer);
}

void sol_masterController::startGameLoop(){
    quit = false;
    redraw = true;
    assert(al_install_keyboard());
    al_register_event_source(queue,al_get_display_event_source(display));
    al_register_event_source(queue,al_get_timer_event_source(timer));
    al_register_event_source(queue,al_get_keyboard_event_source());

	/*
	-------------------------------------
	GRAPHICS PRESET - FEEL FREE TO CHANGE
	-------------------------------------
	*/

	logicController->addStaticBitmapTemplate("sky", "sky", 800, 600);
	logicController->addStaticBitmapTemplate("grass", "grass", 800, 280);
	logicController->addStaticBitmapTemplate("clouds", "clouds", 800, 421);
	logicController->addStaticBitmapTemplate("forest", "forest", 800, 373);
	logicController->addStaticBitmapTemplate("grasstile1", "grasstile1", 32, 32);
	logicController->addStaticBitmapTemplate("grasstile2", "grasstile2", 32, 32);
	logicController->addStaticBitmapTemplate("bighut", "bighut", 208, 128);
	logicController->addStaticBitmapTemplate("roundhut", "roundhut", 208, 128);
	logicController->addStaticBitmapTemplate("middlehut", "middlehut", 144, 80);
	logicController->addStaticBitmapTemplate("towerhut", "towerhut", 148, 128);
	logicController->addStaticBitmapTemplate("minihut", "minihut", 80, 63);

	logicController->addStaticAnimationTemplate("boyidle", "boyidle", 44,64);

	logicController->activeScene->addLayer(0,"foreground",1.0,0.0);//vertical scroll normally lower to prevent layer separation
	logicController->activeScene->addLayer(1, "characters", 1.0, 0.0);
	logicController->activeScene->addLayer(-10,"sky",0.0,0.0);
	logicController->activeScene->addLayer(-9, "clouds", 0.25, 0.0);
	logicController->activeScene->addLayer(-8, "forest", 0.5, 0.0);
	
	logicController->addObjectToActiveScene("sky", GAME_OBJECT_STATIC_BITMAP, 0, 0, "sky");
	
	//NO OVERLAPPING BITMAPS
	for(int i = -1; i <= 1; i++) logicController->addObjectToActiveScene("clouds", GAME_OBJECT_STATIC_BITMAP, (3200*i), 179, "clouds");
	for(int i = -1; i <= 1; i++) logicController->addObjectToActiveScene("forest", GAME_OBJECT_STATIC_BITMAP, (1600 * i), 227, "forest");
	for(int i = -50; i <= 50; i++) logicController->addObjectToActiveScene("grasstile1", GAME_OBJECT_STATIC_BITMAP, (32 * i), 504, "foreground");
	for (int i = -50; i <= 50; i++) logicController->addObjectToActiveScene("grasstile2", GAME_OBJECT_STATIC_BITMAP, (32 * i), 536, "foreground");
	for (int i = -50; i <= 50; i++) logicController->addObjectToActiveScene("grasstile2", GAME_OBJECT_STATIC_BITMAP, (32 * i), 568, "foreground");
	logicController->addObjectToActiveScene("bighut", GAME_OBJECT_STATIC_BITMAP, 0, 376, "foreground");
	logicController->addObjectToActiveScene("towerhut", GAME_OBJECT_STATIC_BITMAP, -600, 376, "foreground");
	logicController->addObjectToActiveScene("towerhut", GAME_OBJECT_STATIC_BITMAP, 500, 376, "foreground");
	logicController->addObjectToActiveScene("boyidle", GAME_OBJECT_STATIC_ANIMATION, 50, 440, "characters");



    sol_logicCamera* newCamera = new sol_logicCamera;
    newCamera->x = -600;
    newCamera->y = 0;
    newCamera->width = 800;
    newCamera->height = 600;
    logicController->activeScene->changeActiveCamera(newCamera);
    //----------------------
    al_start_timer(timer);
    gameLoop();
}

void sol_masterController::gameLoop(){
    double xSpeed = 0;
	double moveSpeed = 5;
    double ySpeed = 0;
	double xLowBound = -800;
	double xHighBound = 0;
    while(!quit){
        al_wait_for_event(queue, &curEvent);
        if(curEvent.type == ALLEGRO_EVENT_TIMER){
            redraw = true;
        }
        else if(curEvent.type == ALLEGRO_EVENT_KEY_DOWN){
            switch (curEvent.keyboard.keycode){
                case ALLEGRO_KEY_RIGHT:
                    xSpeed += moveSpeed;
                break;
                case ALLEGRO_KEY_LEFT:
                    xSpeed -= moveSpeed;
                break;
                case ALLEGRO_KEY_UP:
                    ySpeed -= moveSpeed;
                break;
                case ALLEGRO_KEY_DOWN:
                    ySpeed += moveSpeed;
                break;
            }
        }
        else if(curEvent.type == ALLEGRO_EVENT_KEY_UP){
            switch (curEvent.keyboard.keycode){
                case ALLEGRO_KEY_RIGHT:
                    xSpeed -= moveSpeed;
                break;
                case ALLEGRO_KEY_LEFT:
                    xSpeed += moveSpeed;
                break;
                case ALLEGRO_KEY_UP:
                    ySpeed += moveSpeed;
                break;
                case ALLEGRO_KEY_DOWN:
                    ySpeed -= moveSpeed;
                break;
            }
        }
        else if(curEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            quit = true;
        }

		//make running boy run around

        if(redraw == true){
			if(logicController->activeScene->getActiveCamera()->x + xSpeed < xHighBound 
				&& logicController->activeScene->getActiveCamera()->x + xSpeed > xLowBound)
            logicController->activeScene->getActiveCamera()->x += xSpeed;
            //logicController->activeScene->getActiveCamera()->y += ySpeed;
            renderPipeline->buildGraphics(logicController->activeScene);//THIS IS LEAKING MEMORY
            al_clear_to_color(al_map_rgb(29,106,173));
            graphicsController->printFrame();
            al_flip_display();
            redraw = false;
        }
    }
    endGameLoop();
}

void sol_masterController::endGameLoop(){

}
