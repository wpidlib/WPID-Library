#include "WPID/PID.h"

float PID::calculateSpeed(float error, float max_speed){
    // summation of error over time
    float integral = prev_integral + (error * (delay_time/(float)1000));

    if(prev_error == MAXFLOAT){
        prev_error = error > 0 ? error - 1 : error + 1; //for logging derivative
    }

    // slope of error over time
    float derivative = (error - prev_error) / (delay_time/(float)1000); 
    prev_error = error; // set previous error to current error

    // calculated speed value
    float speed = error*kp + integral*ki + derivative*kd; // calculated speed
    float prev_speed = speed; // pre cap speed

    // cap speed at max speed if saturated (speed unobtainable)
    if(speed > max_speed){ speed = max_speed; }
    if(speed < -max_speed){ speed = -max_speed; }
    
    // if saturated, check if getting worse, if so then remove integral term
    // and dont add new integral to integral
    // basically only starts to integrate if our output is less than our maximum
    if(speed != prev_speed && std::signbit(error) == std::signbit(prev_speed)){
        speed -= integral*ki;
        integral = prev_integral;
        speed += integral*ki;
    } // integral clamping
    prev_integral = integral;

    // retain minimum speed
    if (speed < bias && speed > 0) { speed = bias; }
    if (speed > -bias && speed < 0) { speed = -bias; }

    std::cout << std::fixed << std::setprecision(2);
    //this->logCSV(error, speed, (error*kp), integral, derivative);
    return speed;
}

void PID::setErrorRange(float bound){
    this->bound = bound;
}

bool PID::cont(float error){
    return std::fabs(error) > bound ? true : false;
}

void PID::reset(void){
    prev_error = MAXFLOAT;
    prev_integral = 0;
}

void PID::logCSV(float error, float speed, float proportional, float integral, float derivative){
    std::ofstream myfile;
    std::string suffix = ".csv";
    if(fName.compare("LoggedData") == 0){
        std::ostringstream ss;
        ss << (int)vex::timer::system();
        fName += ss.str();
        myfile.open(fName + suffix, std::ios::app);
        myfile << "Time,Error,Speed,Proportional,Integral,Derivative\n";
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
    myfile << '\n';
    myfile.close();
    if(!cont(error)){
        fName = "LoggedData";
    }
}

PID PID::copy(){
    return PID(kp, ki, kd);
}