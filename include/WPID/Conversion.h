#include <iostream>
#include <map>
using namespace std;

class Conversion {
    private:
        const float FT_TO_IN = 12.0;
        const float YD_TO_IN = 36.0;
        const float M_TO_IN = 39.3701;
        const float CM_TO_IN = 0.393701;
        const float MM_TO_IN = 0.0393701;

        const enum measurement{in, ft, yd, m, cm, mm};
        map<string, measurement> measurements;

        void setEnum(); //Sets the enumeration hashmap

    public:
    
    /**
     * @brief Converts any measured value to the standardized units used in this library
     * @param value the numeric value
     * @param value_type the abbreviation representing the type of input data
    */
    float standardize(float value, string value_type);

    /**
     * @brief Converts a value in the standardized units used in this library to preferred units
     * @param value the numeric value
     * @param output_type the abbreviation representing the desired output type of data
    */
    float convertTo(float value, string output_type);
};