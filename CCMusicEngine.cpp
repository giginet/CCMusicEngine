//
//  CCMusicEngine.cpp
//  Commuage
//
//  Created by koki-miki on 7/19/15.
//
//

#include "CCMusicEngine.h"

namespace CCMusicEngine {
    
    const Timing Timing::ZERO = Timing(0, 0, 0);
    
    Timing::Timing()
    : bar(0)
    , beat(0)
    , unit(0)
    {
        
    }
    
    Timing::Timing(int bar, int beat, int unit)
    : bar(bar)
    , beat(beat)
    , unit(unit)
    {
        
    }
    
    Timing::Timing(const CCMusicEngine::Timing & other)
    : bar(other.bar)
    , beat(other.beat)
    , unit(other.unit)
    {
    
    }
    
    Music::Music(int audioID, float tempo)
    : _audioID(audioID)
    , _tempo(tempo)
    , _unitPerBar(16)
    , _unitPerBeat(4)
    , _timing(Timing(0, 0, 0))
    {
        
    }
    
    Music::~Music()
    {
        
    }
    
    bool Music::init()
    {
        return true;
    }
    
    Music* Music::create(int audioID, float tempo)
    {
        Music * music = new Music(audioID, tempo);
        if (music && music->init()) {
            music->autorelease();
            return music;
        }
        CC_SAFE_DELETE(music);
        return nullptr;
    }
    
    void Music::update(float dt)
    {
        this->updateTiming();
    }
    
    void Music::updateTiming()
    {
        double currentTime = cocos2d::experimental::AudioEngine::getCurrentTime(_audioID);
        cocos2d::log("%lf", currentTime);
        float secPerBeat = 60.0 / _tempo;
        float secPerUnit = secPerBeat / _unitPerBeat;
        float secPerBar = secPerUnit * _unitPerBar;
        int bar = floor(currentTime / secPerBar);
        double barOffset = bar * secPerBar;
        int beat = floor((currentTime - barOffset) / secPerBeat);
        double beatOffset = barOffset + (beat * secPerBeat);
        int unit = floor((currentTime - beatOffset) / secPerUnit);

        _timing.bar = bar;
        _timing.beat = beat;
        _timing.unit = unit;
    }
    
    
}