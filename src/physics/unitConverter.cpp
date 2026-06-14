#include "unitConverter.h"
#include "core/configParser.h"


float convertToBlockUnits(float val)
{
    return val*Engine_Constants::getTileSize();
}
