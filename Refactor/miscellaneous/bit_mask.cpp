#include <iostream>

enum LightMask {
    ENTRANCE = 0x01,
    LIVING_ROOM = 0x02,
    RESTROOM = 0x04,
    KITCHEN = 0x08,
    BATHROOM = 0x10,
    BEDROOM1 = 0x20,
    BEDROOM2 = 0x40,
    ATTIC = 0x80
};

//same thing
/*
enum LightMask {
    ENTRANCE    = 1 << 0,
    LIVING_ROOM = 1 << 1,
    RESTROOM    = 1 << 2,
    KITCHEN     = 1 << 3,
    BATHROOM    = 1 << 4,
    BEDROOM1    = 1 << 5,
    BEDROOM2    = 1 << 6,
    ATTIC       = 1 << 7
};
*/


int main()
{
    //using 8 bit integer for semplicity
    uint8_t lightsOn = 193; //11000001
    uint8_t everylightsOn = 255; //11111111

    //bitwise and 
    if (lightsOn & ATTIC) {
        std::cout << "ATTIC on" << std::endl;
    }

    if (lightsOn & BEDROOM2) {
        std::cout << "BEDROOM2 on" << std::endl;
    }

    if (lightsOn & ENTRANCE) {
        std::cout << "ENTRANCE on" << std::endl;
    }

    //check every lights on
    if (everylightsOn & ENTRANCE    &&
        everylightsOn & LIVING_ROOM &&
        everylightsOn & RESTROOM    &&
        everylightsOn & KITCHEN     &&
        everylightsOn & BATHROOM    &&
        everylightsOn & BEDROOM1    &&
        everylightsOn & BEDROOM2    &&
        everylightsOn & ATTIC       ){
        std::cout << "ALL LIGHTS on" << std::endl;
    }

    
}
