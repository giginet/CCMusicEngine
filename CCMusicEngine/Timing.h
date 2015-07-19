//
//  Timing.h
//  CCMusicEngine
//
//  Created by giginet on 7/20/15.
//
//

#ifndef __CCMusicEngine__Timing__
#define __CCMusicEngine__Timing__

#include "Macros.h"

NS_MUSIC_ENGINE_BEGIN

class Timing {
public:
    int bar;
    int beat;
    int unit;
    Timing();
    Timing(int bar, int beat, int unit);
    Timing(const Timing& other);
    static Timing createByUnit(int unitCount, int unitPerBar, int unitPerBeat);
    
    int unitCount(int unitPerBar, int unitPerBeat);
    
    bool isZero();
    
    Timing next(int unitPerBar, int unitPerBeat);
    Timing prev(int unitPerBar, int unitPerBeat);
    
    Timing nextBeat(int unitPerBar, int unitPerBeat);
    Timing nextBar(int unitPerBar, int unitPerBeat);
    
    Timing seek(int offset, int unitPerBar, int unitPerBeat);
    
    static const Timing ZERO;
};

NS_MUSIC_ENGINE_END

#endif /* defined(__CCMusicEngine__Timing__) */
