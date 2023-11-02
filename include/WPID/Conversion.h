#pragma once
#include <iostream>
#include <map>
#include "v5_vcs.h"
using namespace std;

class Conversion {
    private:
        static constexpr float FT_TO_IN = 12.0;
        static constexpr float YD_TO_IN = 36.0;
        static constexpr float M_TO_IN = 39.3701;
        static constexpr float CM_TO_IN = 0.393701;
        static constexpr float MM_TO_IN = 0.0393701;
        static constexpr float REV_TO_DEG = 360;
        static constexpr float RAW_TO_DEG = 50;

    public:
    
        /**
        * @brief An enumerated class of measurement types for conversion
        */
        enum class measurement{ 
            /** @brief A measurement unit that is measured in inches*/
            in,
            /** @brief A measurement unit that is measured in feet*/
            ft,
            /** @brief A measurement unit that is measured in yards*/
            yd,
            /** @brief A measurement unit that is measured in meters*/
            m,
            /** @brief A measurement unit that is measured in centimeters*/
            cm,
            /** @brief A measurement unit that is measured in millimeters*/
            mm
        };
    
    /**
     * @brief Converts any measured value to the standardized units used in this library
     * @param value the numeric value
     * @param value_type the enum representing the type of input data
    */
    static float standardize(float value, measurement value_type);

    /**
     * @brief Converts a value in the standardized units used in this library to preferred units
     * @param value the numeric value
     * @param output_type the enum representing the desired output type of data
    */
    static float convertTo(float value, measurement output_type);

    /**
     * @brief Converts any measured rotation unit to the standardized units used in this library
     * @param value the numeric value
     * @param value_type the enum representing the type of input data
    */
    static float standardize(float value, float gearset, vex::rotationUnits value_type);

    /**
     * @brief Converts any measured rotation unit to the standardized units used in this library
     * @param value the numeric value
     * @param output_type the enum representing the type of input data
    */
    static float convertTo(float value, float gearset, vex::rotationUnits output_type);
};