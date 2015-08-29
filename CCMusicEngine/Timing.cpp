//
//  Timing.cpp
//  CCMusicEngine
//
//  Created by giginet on 7/20/15.
//
//

#include "Timing.h"
#include <cmath>

NS_MUSIC_ENGINE_BEGIN

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

Timing::Timing(const Timing & other)
: bar(other.bar)
, beat(other.beat)
, unit(other.unit)
{
}

Timing Timing::createByUnit(int unitCount, int unitPerBar, int unitPerBeat) {
    int bar = floor(unitCount / unitPerBar);
    int mod = unitCount % unitPerBar;
    int beat = floor(mod / unitPerBeat);
    int unit = unitCount - ((bar * unitPerBar) + (beat * unitPerBeat));
    return Timing(bar, beat, unit);
}

bool Timing::isZero()
{
    return bar == 0 && beat == 0 && unit == 0;
}

int Timing::unitCount(int unitPerBar, int unitPerBeat)
{
    return unitPerBar * this->bar + unitPerBeat * beat + unit;
}

Timing Timing::prev(int unitPerBar, int unitPerBeat)
{
    return seek(-1, unitPerBar, unitPerBeat);
}

Timing Timing::next(int unitPerBar, int unitPerBeat)
{
    return seek(1, unitPerBar, unitPerBeat);
}

Timing Timing::nextBeat(int unitPerBar, int unitPerBeat)
{
    return seek(unitPerBeat - unit, unitPerBar, unitPerBeat);
}

Timing Timing::nextBar(int unitPerBar, int unitPerBeat)
{
    int offset = unitPerBar - ((beat * unitPerBeat) + unit);
    return seek(offset, unitPerBar, unitPerBeat);
}

Timing Timing::seek(int offset, int unitPerBar, int unitPerBeat)
{
    int unit = unitCount(unitPerBar, unitPerBeat);
    if (unit + offset < 0) {
        return Timing::ZERO;
    }
    return Timing::createByUnit(unit + offset, unitPerBar, unitPerBeat);
}

bool Timing::isBeginningOfBar()
{
    return beat == 0 && unit == 0;
}

NS_MUSIC_ENGINE_END