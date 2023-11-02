#include "WPID/Conversion.h"

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

float Conversion::standardize(float value, float gearset, vex::rotationUnits value_type){
    switch(value_type){
        case vex::rotationUnits::rev:
            return value * REV_TO_DEG;
        case vex::rotationUnits::raw:
            return value * (gearset * RAW_TO_DEG);
        default:
            return value;
    }
}

float Conversion::convertTo(float value, float gearset, vex::rotationUnits output_type){
    switch(output_type){
        case vex::rotationUnits::rev:
            return value / REV_TO_DEG;
        case vex::rotationUnits::raw:
            return value / (gearset * RAW_TO_DEG);
        default:
            return value;
    }
}