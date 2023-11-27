#include "WPID/Conversion.h"

using namespace wpid;

float Conversion::standardize(float value, measurement value_type){
    switch(value_type){
        case measurement::ft:
            return value * FT_TO_IN;
        case measurement::yd:
            return value * YD_TO_IN;
        case measurement::m:
            return value * M_TO_IN;
        case measurement::cm:
            return value * CM_TO_IN;
        case measurement::mm:
            return value * MM_TO_IN;
        default:
            return value;
    }
}

float Conversion::convertTo(float value, measurement output_type){
    switch(output_type){
        case measurement::ft:
            return value / FT_TO_IN;
        case measurement::yd:
            return value / YD_TO_IN;
        case measurement::m:
            return value / M_TO_IN;
        case measurement::cm:
            return value / CM_TO_IN;
        case measurement::mm:
            return value / MM_TO_IN;
        default:
            return value;
    }
}
