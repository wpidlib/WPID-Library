#include "WPID/Conversion.h"

Conversion:: Conversion(){this->setEnum();}

void Conversion::setEnum(){
    this->measurements["ft"] = ft;
    this->measurements["yd"] = yd;
    this->measurements["m"] = m;
    this->measurements["cm"] = cm;
    this->measurements["mm"] = mm;
}

float Conversion::standardize(float value, string value_type){
    switch(measurements[value_type]){
        case ft:
            return value * FT_TO_IN;
        case yd:
            return value * YD_TO_IN;
        case m:
            return value * M_TO_IN;
        case cm:
            return value * CM_TO_IN;
        case mm:
            return value * MM_TO_IN;
        default:
            return value;
    }
}

float Conversion::convertTo(float value, string output_type){
    switch(measurements[output_type]){
        case ft:
            return value / FT_TO_IN;
        case yd:
            return value / YD_TO_IN;
        case m:
            return value / M_TO_IN;
        case cm:
            return value / CM_TO_IN;
        case mm:
            return value / MM_TO_IN;
        default:
            return value;
    }
}