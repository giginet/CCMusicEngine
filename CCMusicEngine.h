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

namespace CCMusicEngine {
    
    class Timing {
        public:
        int bar;
        int beat;
        int unit;
        Timing();
        Timing(int bar, int beat, int unit);
        Timing(const Timing& other);
        
        static const Timing ZERO;
    };

    class Music :public cocos2d::Ref {
    CC_CONSTRUCTOR_ACCESS:
        virtual bool init();
        Music(float tempo);
        virtual ~Music();
    public:
        void update(float dt);
        static Music* create(float tempo);
        
        CC_SYNTHESIZE(float, _tempo, Tempo);
        CC_SYNTHESIZE(float, _currentTime, CurrentTime);
        CC_SYNTHESIZE(int, _unitPerBeat, UnitPerBeat);
        CC_SYNTHESIZE(int, _unitPerBar, UnitPerBar);
        CC_SYNTHESIZE_PASS_BY_REF(Timing, _timing, Timing);
    private:
        void updateTiming();
    };

}

#endif /* defined(__Commuage__CCMusicEngine__) */
