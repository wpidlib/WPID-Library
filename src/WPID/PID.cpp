#include "WPID/PID.h"

using namespace std;
using namespace vex;
using namespace wpid;

float PID::calculateSpeed(float error, float max_speed, std::string mech_id){
    // summation of error over time
    float integral = prev_integral + (error * (delay_time/(float)1000));

    // slope of error over time
    float derivative = (error - prev_error) / (delay_time/(float)1000); 
    prev_error = error; // set previous error to current error

    // calculated speed value
    float speed = error*kp + integral*ki + derivative*kd; // calculated speed
    float prev_speed = speed; // pre cap speed

    // cap speed at max speed if saturated
    if(speed > max_speed){ speed = max_speed; }
    if(speed < -max_speed){ speed = -max_speed; }
    
    // if saturated, check if getting worse
    // if getting worse, use previous integral and stop integrating
    if(speed != prev_speed && std::signbit(error) == std::signbit(prev_speed)){
        speed -= integral*ki; // remove integral component
        integral = prev_integral; // set error to 0 in integral calculation
        speed += integral*ki; // add back new clamped integral
    } // integral clamping
    prev_integral = integral;

    // retain minimum speed
    if (speed < bias && speed > 0) { speed = bias; }
    if (speed > -bias && speed < 0) { speed = -bias; }
    
    LOG(INFO) << " err: " << error << " spd: " << speed << " P: " << error*kp << " I: " << integral*ki << " D: " << derivative*kd;
    this->fileLogging(error, speed, (error*kp), integral, derivative, mech_id);

    return speed;
}

void PID::setErrorRange(float bound){
    this->bound = bound;
}

bool PID::unfinished(float error){
    return std::fabs(error) > bound ? true : false;
}

void PID::reset(void){
    prev_error = MAXFLOAT;
    prev_integral = 0;
}

PID PID::copy(void){
    PID dupe = PID(this->kp, this->ki, this->kd);
    dupe.bias = this->bias;
    dupe.setErrorRange(this->bound);
    return dupe;
}

void PID::fileLogging(float error, float speed, float proportional, float integral, float derivative, std::string mech_id){
    ofstream myfile;
    string suffix = ".csv";
    if(fName.compare("LoggedData") == 0){
        std::ostringstream ss;
        ss << (int)vex::timer::system();
        fName += ss.str();
        myfile.open(fName + suffix, std::ios::app);
        myfile << "Time,Error,Speed,Proportional,Integral,Derivative,Name\n";
        myfile.close();
    }
    myfile.open(fName + suffix, std::ios::app);
    myfile << vex::timer::system();
    myfile << ",";
    myfile << round(error*100.0)/100.0;
    myfile << ",";
    myfile << round(speed*100.0)/100.0;
    myfile << ",";
    myfile << round(proportional*100.0)/100.0;
    myfile << ",";
    myfile << round(integral*100.0)/100.0;
    myfile << ",";
    myfile << round(derivative*100.0)/100.0;
    myfile << ",";
    myfile << mech_id;
    myfile << '\n';
    myfile.close();
    if(!unfinished(error)){
        fName = "LoggedData";
    }
}