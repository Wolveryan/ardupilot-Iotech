// Digital Filters for Proximity
// Author - Yatin Khurana
// Copyright - IoTechWorld Avigations Pvt Ltd.

#include "AP_Proximity_Filters.h"


// The Logic Creates a 2D Radial Window and 
// If the Object Moves out of the Window Too fast the last value is passed,
// else new one is accepted after 3 out of range values

bool AP_Proximity_R21_Glitch_Filter::apply_R21_glitch_filter(float &reading, float &angle)
{
    float current_reading = reading; //backup current reading
    float current_angle = angle;

    if(( abs(glitch_dist - reading) >= _glitch_val_dist) ||
       ((reading < _glitch_angle_dist)? (wrap_180(glitch_angle - angle) >= _glitch_val_angle2):(wrap_180(glitch_angle - angle) >= _glitch_val_angle)))
    {
        //it means there is a positive glitch
        glitch_samples += 1; //increment glitch sample
        reading = 0; // Set to 0 as in glitch, it will create ghost obstacles.
        angle = 0;
    }
    else
    {
        //we don't get a glitch
        glitch_samples = 0; //reset glitch samples counter
        //back up new glitch_reading and restore the original reading cm
        reading = current_reading;
        angle = current_angle;
        glitch_dist = reading;
        glitch_angle = angle;
        return true;
    }

    if(abs(glitch_samples) >= _glitch_samples_num){
        glitch_samples = 0; //reset glitch samples counter
        //it means we get consistent glitch no need to change reading_cm as that is an actual data so restore the reading
        reading = current_reading;
        angle = current_angle;
        glitch_dist = reading;
        glitch_angle = angle;
        return true;
    }
    return false;
}

void AP_Proximity_Glitch_Filter::apply_glitch_filter(float &reading)
{
    float current_reading = reading; //backup current reading

    if(abs(glitch_reading - reading) >= _glitch_val)
    {
        //it means there is a positive glitch
        glitch_samples+= 1; //increment glitch sample
        reading = glitch_reading; //as of now we will send prev reading which is approved not be glitch will be sent to fc
    }
    else if((reading - glitch_reading) >= _glitch_val)
    {
        //it means we get a negative glitch
        glitch_samples-= 1; //decrement the glitch sample
        reading = glitch_reading; //as of now we will send prev reading which is approved not be glitch will be sent to fc
    }
    else
    {
        //we don't get a glitch
        glitch_samples = 0; //reset glitch samples counter
        //back up new glitch_reading and restore the original reading cm
        reading = current_reading;
        glitch_reading = reading;
    }

    if(abs(glitch_samples) >= _glitch_samples_num){
        glitch_samples = 0; //reset glitch samples counter
        //it means we get consistent glitch no need to change reading as that is an actual data so restire the reading
        reading = current_reading;
        glitch_reading = reading;
    }
    return;
}

void AP_Proximity_Moving_Average_Filter::apply_m_avg_filter(float &reading)
{
    buffer[ptr++] = reading;
    if(ptr>=10){
        ptr = 0;
    }
    // For Faster Computation
    float result = buffer[0] +buffer[1] +buffer[2] +buffer[3] +buffer[4] +buffer[5] +buffer[6] +buffer[7] +buffer[8] +buffer[9];
    result = result/10;
    reading = result;
};

// sets the New Average of Moving Average filter to val
void AP_Proximity_Moving_Average_Filter::reset_filter_to_val(float val){
    for(int i=0; i<10; i++){
        buffer[i] = val;
    }
}