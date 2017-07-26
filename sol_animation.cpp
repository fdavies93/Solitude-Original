#include <vector>
#include <string>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "sol_animation.h"
#include "genericFunctions.h"
#include "sol_dimensions.h"
using namespace std;

bool sol_animation::LoadFromCsv(string filename){
    al_init_image_addon();
    vector <string> csvStrings = LoadCsvToVector(filename);
    string myName;
    if(csvStrings.size() >= 6 && (csvStrings.size()-2)%4 == 0){//guarantees it has the right number of elements if not the right type
        ALLEGRO_BITMAP* animationBitmap;
        myName = csvStrings[0];
        animationBitmap = al_load_bitmap(csvStrings[1].c_str());
        if(animationBitmap != NULL){
            ALLEGRO_COLOR transparencyColor;
            transparencyColor = al_get_pixel(animationBitmap,0,0);
            al_convert_mask_to_alpha(animationBitmap,transparencyColor);//makes top-left pixel the transparency color of the bitmap
            int entryType;
            sol_dimensions curDimensions;
            sol_frame curFrame;
            for(int entryCounter = 2; entryCounter < csvStrings.size(); entryCounter++){
                entryType = ((entryCounter - 2)%4);
                switch (entryType){
                    case 0:
                        curDimensions.x = atoi(csvStrings[entryCounter].c_str());//note: if you put a string in the wrong place it will just read as 0
                    break;
                    case 1:
                        curDimensions.y = atoi(csvStrings[entryCounter].c_str());
                    break;
                    case 2:
                        curDimensions.width = atoi(csvStrings[entryCounter].c_str());
                        if(curDimensions.width > width){width = curDimensions.width;}
                    break;
                    case 3:
                        curDimensions.height = atoi(csvStrings[entryCounter].c_str());
                        if(curDimensions.height > height){height = curDimensions.height;}
                        curFrame.frameBitmap = al_clone_bitmap(al_create_sub_bitmap(animationBitmap,curDimensions.x,curDimensions.y,curDimensions.width,curDimensions.height));
                        al_lock_bitmap(curFrame.frameBitmap,al_get_bitmap_format(curFrame.frameBitmap),ALLEGRO_LOCK_READONLY);
                        frames.push_back(curFrame);
                    break;
                    default:
                        cout << "Some kind of overflow error? In sol_animation::LoadFromCsv\n";
                        return false;
                    break;
                }
            }
            al_destroy_bitmap(animationBitmap);
            name = myName;
            //animationTicks = newAnimationTicks;
            al_shutdown_image_addon();
            return true;
        }
        else{
            cout << "Could not load " << csvStrings[1] << " in animation " << filename << ".\n";
        }
    }
    else{
        cout << "Wrong number of entries for valid animation in " << filename << ".\n";
    }
    return false;
}

sol_frame* sol_animation::getFrame(int frameIndex){
    return &frames[frameIndex];
}

int sol_animation::getNumberOfFrames(){
    return frames.size();
}

int sol_animation::getWidth(){
    return width;
}

int sol_animation::getHeight(){
    return height;
}

string sol_animation::getName(){
    return name;
}

sol_animation::sol_animation(){
    width = 0;
    height = 0;
}

sol_animation::sol_animation(string filename){
    width = 0;
    height = 0;
    if(!LoadFromCsv(filename)){
        cout << "Animation load failed in sol_animation constructor.\n";
    }
}
