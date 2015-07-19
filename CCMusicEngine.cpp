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
    
    Timing::Timing(int bar, int beat, int unit)
    : bar(bar)
    , beat(beat)
    , unit(unit)
    {
        
    }
    
    Music::Music(int audioID, float tempo)
    : _audioID(_audioID)
    , _tempo(_tempo)
    , _unitPerBar(16)
    , _unitPerBeat(4)
    , _timing(Timing::ZERO)
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

    }
    
    void Music::updateTiming()
    {
        auto currentTime = cocos2d::experimental::AudioEngine::getCurrentTime(_audioID);
        int secPerBeat = 60 / _tempo;
        int secPerUnit = secPerBeat / _unitPerBeat;
        int secPerBar = secPerUnit * _unitPerBar;
        int bar = floor(currentTime / secPerBar);
        double barOffset = bar * secPerBar;
        int beat = (currentTime - barOffset) / secPerBeat;
        double beatOffset = barOffset + (beat * secPerBeat);
        int unit = floor((currentTime - beatOffset) / secPerUnit);
        Timing newTiming(bar, beat, unit);
        _timing = newTiming;
    }
    
    
}