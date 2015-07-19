//
//  CCMusicEngine.h
//  Commuage
//
//  Created by koki-miki on 7/19/15.
//
//

#ifndef __Commuage__CCMusicEngine__
#define __Commuage__CCMusicEngine__

#include "cocos2d.h"
#include <AudioEngine.h>

namespace CCMusicEngine {
    
    class Timing {
        public:
        int bar;
        int beat;
        int unit;
        Timing();
        Timing(int bar, int beat, int unit);
        static const Timing ZERO;
    };

    class Music :public cocos2d::Ref {
    CC_CONSTRUCTOR_ACCESS:
        virtual bool init();
        Music(int audioID, float tempo);
        virtual ~Music();
    public:
        void update(float dt);
        static Music* create(int audioID, float tempo);
        
        CC_SYNTHESIZE(int, _audioID, AudioID);
        CC_SYNTHESIZE(float, _tempo, Tempo);
        CC_SYNTHESIZE(int, _unitPerBeat, UnitPerBeat);
        CC_SYNTHESIZE(int, _unitPerBar, UnitPerBar);
        CC_SYNTHESIZE(Timing, _timing, Timing);
    private:
        void updateTiming();
    };

}

#endif /* defined(__Commuage__CCMusicEngine__) */
