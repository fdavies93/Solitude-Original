#include "genericFunctions.h"
#include <string>
#include <vector>
#include <iostream>
#include <allegro5/allegro.h>
using namespace std;

vector <string> LoadCsvToVector(string filename){
    //al_set_standard_file_interface();
    vector <string> csvValues;
    ALLEGRO_FILE* stringFile = al_fopen(filename.c_str(),"r");
    if(stringFile != NULL){
        char curChar;
        string curWord;
        while(!al_feof(stringFile)){
            while(curChar != ',' && !al_feof(stringFile)){
                curChar = al_fgetc(stringFile);
                if(!al_feof(stringFile)){
                    if(curChar != '\n' && curChar != ' ' && curChar != ','){
                        curWord += curChar;
                    }
                }
            }
            if(curWord.length() > 0){
                csvValues.push_back(curWord);
                curWord.clear();
            }
            curChar = 'a';
        }
    }
    else{
        cout << "Load of " << filename.c_str() << " failed!\n";
    }
    al_fclose(stringFile);
    return csvValues;
}
