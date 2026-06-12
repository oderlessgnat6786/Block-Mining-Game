#include "unitConverter.h"
#include "core/constants.h"


float convertToBlockUnits(float val)
{
    return val*TILE_SIZE;
}
