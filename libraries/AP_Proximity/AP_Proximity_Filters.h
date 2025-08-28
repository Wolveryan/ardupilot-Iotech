// Digital Filters for Proximity
// Author - Yatin Khurana
// Copyright - IoTechWorld Avigations Pvt Ltd.
#pragma once
#include "AP_Proximity.h"

// 1D Glitch Filter
class AP_Proximity_Glitch_Filter
{
public:
    //contructor
    AP_Proximity_Glitch_Filter(float glitch_cm, uint8_t glitch_samples_num){
        _glitch_val = glitch_cm;
        _glitch_samples_num = glitch_samples_num;
    };
    void apply_glitch_filter(float &reading);

private:
    //variables for glitch filter
    float glitch_reading;
    int8_t glitch_samples;

    float _glitch_val;
    uint8_t _glitch_samples_num;
};

// R21 Glitch Filters also Stores Angle of the respective readings when setting or resetting the readings
class AP_Proximity_R21_Glitch_Filter
{
public:
    //contructor
    // Glitch_ang1 - For Distance further than 5m, Glitch_ang2 - For Distance close than 5m, glitch_ang_dist - the distance at which the glitch angle switches
    AP_Proximity_R21_Glitch_Filter(float glitch_cm, float glitch_ang1, float glitch_ang2, float glitch_ang_dist, uint8_t glitch_samples_num){
        _glitch_val_dist = glitch_cm;
        _glitch_val_angle = glitch_ang1;
        _glitch_samples_num = glitch_samples_num;
        _glitch_val_angle2 = glitch_ang2;
        _glitch_angle_dist = glitch_ang_dist;
    };

    // Returns Reset Flag
    bool apply_R21_glitch_filter(float &reading, float &angle);

private:
    //variables for glitch filter
    float glitch_dist;
    float glitch_angle;
    int8_t glitch_samples;

    float _glitch_val_dist;

    float _glitch_val_angle;
    float _glitch_val_angle2;
    float _glitch_angle_dist;

    uint8_t _glitch_samples_num;
};

// Moving Average for 10 Samples
class AP_Proximity_Moving_Average_Filter
{
public:
    //contructor
    AP_Proximity_Moving_Average_Filter(){};
    void apply_m_avg_filter(float &reading);
    void reset_filter_to_val(float val);

private:
    uint8_t ptr;
    float buffer[10];
};