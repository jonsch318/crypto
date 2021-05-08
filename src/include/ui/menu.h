#ifndef UI_MENU_H
#define UI_MENU_H
#include <stdint.h>

typedef struct menu menu;
typedef struct entry entry;


struct entry
{
    char title[50];    //Text written on the screen
    int foreground;    //foreground color
    int background;    //background color
    int s_foreground;  //foreground color -> selected
    int s_background;  //background color -> selected
    void (*run)(void); //Function to be executed when selected
};

struct menu
{
    struct entry entrys[5];
    //I don't think there will be more than 255 entries -> uint8_t 0-255
    uint8_t num_entrys; //Number of entrys
    uint8_t selected;   //Index of selected entry
};

#endif // UI_MENU_H