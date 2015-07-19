# CCMusicEngine

This is the port of MusicEngine for Unity by [@geekdrums](https://github.com/geekdrums/)

https://github.com/geekdrums/MusicEngine

For detail to read his documentation.

[English](https://github.com/geekdrums/MusicEngine/blob/master/AboutMusicEngineEn.pdf)
[日本語](https://github.com/geekdrums/MusicEngine/blob/master/AboutMusicEngine.pdf)

## Usage

### Setup

1. Add `CCMusicEngine` directory into your project
2. Include `CCMusicEngine.h`
3. Initialize Music

```cpp
bool YourScene::init()
{
    // first argument should be tempo of your music
    _music = CCMusicEngine::Music::create(120);
    cocos2d::experimental::AudioEngine::play2d("my_music.wav");

    // you can change `unitPerBar` and `unitPerBeat` properties.
    // For example, time signature of your music is 4/4,
    // unitPerBar = 16, unitPerBeat = 4(These are default values)
    _music->setUnitPerBar(16);
    _music->setUnitPerBeat(4);

    _music->retain();
}

void YourScene::update(float dt) 
{
    // You have to set current second of your playing music to the Music instance manually.
    _music->setCurrentTime(currentSecond);
    _music->update();
    CCMusicEngine::Timing currentTiming = _music->getTiming();

    // You can get Timing object. This contains musical attributes.
    cocos2d::log("bar = %d, beat = %d, unit = %d", timing.bar, timing.beat, timing.unit);
}
```

**Notice**: To get current time of playing music, you should not use `AudioEngine::getCurrentTime()`.
In latest cocos2d-x, this method will return inaccurate seconds. So this library will not work well.

Ref : [New AudioEngine getCurrentTime() precision BUG (win32) · Issue #9854 · cocos2d/cocos2d-x](https://github.com/cocos2d/cocos2d-x/issues/9854)

### Event Handlers

You can use custom events to detect the music state would be changed.

```cpp
this->getEventDispatcher()->addCustomEvent("CCMusicEngine.onJustChangedBar", [](Event *event) {
    CCMusicEngine::Music *music = static_cast<CCMusicEngine::Music *>(event->getUserData());
});

```

You can use following events.

#### CCMusicEngine.onJustChangedBar
#### CCMusicEngine.onJustChangedBeat
#### CCMusicEngine.onJustChangedAt

These events will be called on changes just after bar/beat/unit.

#### CCMusicEngine.onNearChangedUnit
#### CCMusicEngine.onNearChangedBeat
#### CCMusicEngine.onNearChangedAt

These events will be called on changes the nearest bar/beat/unit.
