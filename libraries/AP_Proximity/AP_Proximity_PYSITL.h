#pragma once
#include "AP_Proximity_Backend.h"

class AP_Proximity_PYSITL : public AP_Proximity_Backend {
public:
    AP_Proximity_PYSITL(AP_Proximity &_frontend, AP_Proximity::Proximity_State &_state) 
        : AP_Proximity_Backend(_frontend, _state) {}
    
    void update() override {}  // mark it override to silence -Werror
    
    // Required pure virtual methods from base class
    float distance_max() const override { return 100.0f; }  // or appropriate max distance
    float distance_min() const override { return 0.1f; }    // or appropriate min distance
};