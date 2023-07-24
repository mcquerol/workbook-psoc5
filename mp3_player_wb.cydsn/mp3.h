#ifndef MP3_H_
#define MP3_H_
    
#include "global.h"
    
enum eFlags
{
    __flag_nextSong,
    __flag_prevSong,
    __flag_skipSong,
    __flag_playSong,
    __flag_pauseSong,
    __flag_increaseVolume,
    __flag_decreaseVolume
};

enum eStates
{
    __state_PLAYING,
    __state_STANDBY
};

typedef enum eFlags flag_t;
typedef enum eStates states_t;

flag_t btnFlag; //flag for button isr
states_t currState; //variable to know the current state


    
#endif //MP3_H_
/* [] END OF FILE */
