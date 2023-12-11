#include "WPID/PID.h"

using namespace std;
using namespace vex;
using namespace wpid;

float PID::calculateSpeed(float error, float max_speed, std::string mech_id){
    if (start_time == -1) {start_time = vex::timer::system();} // set the start time of a new PID run
    float a = .7; // alpha gain of low pass filter

    // summation of error over time
    float integral = prev_integral + (error * (delay_time/(float)1000));
    if(integral*ki > max_integral_speed) {integral = max_integral_speed/ki;}
    if(integral*ki < -max_integral_speed) {integral = (-max_integral_speed)/ki;}

    // calculate derivative, use low pass filter to smooth output
    if(prev_error == MAXFLOAT) {prev_error = error;}
    float current_estimate = (previous_estimate*a + (1-a)*(error - prev_error)); 
    previous_estimate = current_estimate;
    prev_error = error; // set previous error to current error
    float derivative = current_estimate / (delay_time/(float)1000);

    // calculated speed value
    float speed = error*kp + integral*ki + derivative*kd; // calculated speed
    
    // if system is saturated and error and speed are increasing
    // then make error 0 in integral calculation
    if(abs(speed) > abs(max_speed) && std::signbit(error) == std::signbit(speed)){
        speed -= integral*ki; // remove integral term
        integral = prev_integral; // set current error value to 0 
        speed += integral*ki; // add back new integral value
    }
    prev_integral = integral;
    
    // cap speed at max speed if saturated
    if(speed > max_speed){ speed = max_speed; }
    if(speed < -max_speed){ speed = -max_speed; }
    
    LOG(INFO) << "err: " << error << " spd: " << speed << " P: " << error*kp << " I: " << integral*ki << " D: " << derivative*kd;

    this->fileLogging(error, speed, (error*kp), integral, derivative, mech_id);

    return speed;
}

void PID::setErrorRange(float degrees){
    this->error_range = degrees;
}

void PID::setDelayTime(int delay){
    this->delay_time = delay;
}

int PID::getDelayTime(){
    return this->delay_time;
}

void PID::setLowSpeedThreshold(int threshold){
    this->low_speed_threshold = threshold;
}

void PID::setTimeout(int timeout){
    this->timeout = timeout;
}

void PID::setMaxIntegral(int max_integral){
    this->max_integral_speed = max_integral;
}

bool PID::unfinished(float error, int speed){
    bool timedout = vex::timer::system() >= (timeout + start_time);
    if(timeout != -1 && timedout) {
        LOG(WARN) << "PID timed out. Remaining error is " << error;
        return false;
    }
    bool high_speed = low_speed_threshold != -1 ? fabs(speed) > low_speed_threshold : false;
    bool outside_errorRanges = std::fabs(error) > error_range;
    return outside_errorRanges || high_speed;
}

void PID::reset(void){
    prev_error = MAXFLOAT;
    prev_integral = 0;
    previous_estimate = 0;
    start_time = -1;
    timeout = -1;
}

PID PID::copy(void){
    PID dupe = PID(this->kp, this->ki, this->kd);
    dupe.setDelayTime(this->delay_time);
    dupe.setErrorRange(this->error_range);
    dupe.setLowSpeedThreshold(this->low_speed_threshold);
    dupe.setTimeout(this->timeout);
    dupe.setMaxIntegral(this->max_integral_speed);
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
    if(!unfinished(error, speed)){
        fName = "LoggedData";
    }
}