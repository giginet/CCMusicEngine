#include "CCMusicEngine.h"

NS_MUSIC_ENGINE_BEGIN

const char* onJustChangedBarEventName = "CCMusicEngine.onJustChangedBar";
const char* onJustChangedBeatEventName = "CCMusicEngine.onJustChangedBeat";
const char* onJustChangedAtEventName = "CCMusicEngine.onJustChangedAt";
const char* onNearChangedBarEventName = "CCMusicEngine.onNearChangedBar";
const char* onNearChangedBeatEventName = "CCMusicEngine.onNearChangedBeat";
const char* onNearChangedAtEventName = "CCMusicEngine.onNearChangedAt";

Music::Music(float tempo)
: _tempo(tempo)
, _currentTime(0)
, _lastTime(0)
, _enabled(true)
, _unitPerBar(16)
, _unitPerBeat(4)
, _unitDuration(0)
, _beatDuration(0)
, _barDuration(0)
, _timing(Timing(0, 0, 0))
, _updateHandler(0)
{
}

Music::~Music()
{
    _updateHandler = nullptr;
}

bool Music::init()
{
    return true;
}

Music* Music::create(float tempo)
{
    Music * music = new Music(tempo);
    if (music && music->init()) {
        music->autorelease();
        return music;
    }
    CC_SAFE_DELETE(music);
    return nullptr;
}

float Music::getMusicalTime()
{
    float toBeat = _timing.bar * _barDuration + _timing.beat * _beatDuration;
    float offset = toBeat * _unitDuration;
    return toBeat + ((_currentTime - offset) / _unitDuration);
}

float Music::distanceTo(CCMusicEngine::Timing timing)
{
    auto dstSecond = timing.unitCount(_unitPerBar, _unitPerBeat) * _unitDuration;
    return (dstSecond - _currentTime) / _unitDuration;
}

Timing Music::next()
{
    return _timing.next(_unitPerBar, _unitPerBeat);
}

Timing Music::nextBeat()
{
    return _timing.nextBeat(_unitPerBar, _unitPerBeat);
}

Timing Music::nextBar()
{
    return _timing.nextBar(_unitPerBar, _unitPerBeat);
}

void Music::update(float dt)
{
    if (!_enabled) {
        return;
    }
    if (_updateHandler) {
        _currentTime = _updateHandler(this);
    }
    this->updateTiming();
}

void Music::updateTiming()
{
    
    Timing lastTiming(_timing);
    
    _beatDuration = 60.0 / _tempo;
    _unitDuration = _beatDuration / _unitPerBeat;
    _barDuration = _unitDuration * _unitPerBar;
    int bar = floor(_currentTime / _barDuration);
    float barOffset = bar * _barDuration;
    int beat = floor((_currentTime - barOffset) / _beatDuration);
    float beatOffset = barOffset + (beat * _beatDuration);
    int unit = floor((_currentTime - beatOffset) / _unitDuration);
    
    _timing.bar = bar;
    _timing.beat = beat;
    _timing.unit = unit;
    
    const float nearUnitThreshold = _unitDuration / 2.0;
    const float nearBeatThreshold = _beatDuration / 2.0;
    const float nearBarThreshold = _barDuration / 2.0;
    Timing nextUnit = _timing.next(_unitPerBar, _unitPerBeat);
    Timing nextBar = _timing.nextBar(_unitPerBar, _unitPerBeat);
    Timing nextBeat = _timing.nextBeat(_unitPerBar, _unitPerBeat);
    
    if (lastTiming.unit != unit) {
        this->dispatchEvent(onJustChangedAtEventName);
    } else if ((timingToSecond(nextUnit) - _lastTime) >= nearUnitThreshold &&
               (timingToSecond(nextUnit) - _currentTime) < nearUnitThreshold) {
        this->dispatchEvent(onNearChangedAtEventName);
    }
    if (lastTiming.beat != beat) {
        this->dispatchEvent(onJustChangedBeatEventName);
    } else if ((timingToSecond(nextBeat) - _lastTime) >= nearBeatThreshold &&
               (timingToSecond(nextBeat) - _currentTime) < nearBeatThreshold) {
        this->dispatchEvent(onNearChangedBeatEventName);
    }
    
    if (lastTiming.bar != bar) {
        this->dispatchEvent(onJustChangedBarEventName);
    } else if ((timingToSecond(nextBar) - _lastTime) >= nearBarThreshold &&
               (timingToSecond(nextBar) - _currentTime) < nearBarThreshold) {
        this->dispatchEvent(onNearChangedBarEventName);
    }
    _lastTime = _currentTime;
}

void Music::dispatchEvent(const char *eventName)
{
    auto event = cocos2d::EventCustom(eventName);
    event.setUserData(this);
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

float Music::timingToSecond(CCMusicEngine::Timing timing)
{
    int unit = timing.unitCount(_unitPerBar, _unitPerBeat);
    return unit * (60.0 / _tempo / _unitPerBeat);
}

NS_MUSIC_ENGINE_END