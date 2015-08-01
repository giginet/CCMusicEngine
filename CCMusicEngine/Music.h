//
//  CCMusicEngine.h
//  CCMusicEngine
//
//  Created by giginet on 7/19/15.
//
//

#ifndef __CCMusicEngine__CCMusicEngine__
#define __CCMusicEngine__CCMusicEngine__

#include "cocos2d.h"
#include "Macros.h"

NS_MUSIC_ENGINE_BEGIN

class Music :public cocos2d::Ref {
CC_CONSTRUCTOR_ACCESS:
    virtual bool init();
    Music(float tempo);
    virtual ~Music();
public:
    void update(float dt);
    static Music* create(float tempo);
    
    /**
     Get musical time of current time
     * @return current musical time
     */
    float getMusicalTime();
    
    /**
     * Calc distance to the specific timing by musical time
     * @param timing destination
     * @return musical time
     */
    float distanceTo(Timing timing);
    
    /**
     * Get next Unit/Beat/Bar
     * @return next timing
     */
    Timing next();
    Timing nextBeat();
    Timing nextBar();
    
    CC_SYNTHESIZE(float, _tempo, Tempo);
    CC_SYNTHESIZE(float, _currentTime, CurrentTime);
    CC_SYNTHESIZE(float, _lastTime, LastTime);
    CC_SYNTHESIZE(int, _unitPerBeat, UnitPerBeat);
    CC_SYNTHESIZE(int, _unitPerBar, UnitPerBar);
    CC_SYNTHESIZE(bool, _enabled, Enabled);
    CC_SYNTHESIZE_READONLY(float, _unitDuration, UnitDuration);
    CC_SYNTHESIZE_READONLY(float, _beatDuration, beatDuration);
    CC_SYNTHESIZE_READONLY(float, _barDuration, barDuration);
    CC_SYNTHESIZE_PASS_BY_REF(Timing, _timing, Timing);
private:
    void updateTiming();
    void dispatchEvent(const char* eventName);
    float timingToSecond(Timing timing);
};

NS_MUSIC_ENGINE_END

#endif /* defined(__CCMusicEngine__CCMusicEngine__) */
