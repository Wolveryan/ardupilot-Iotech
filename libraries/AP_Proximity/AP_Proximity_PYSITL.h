#pragma once
#include "AP_Proximity_Backend.h"

class AP_Proximity_PYSITL : public AP_Proximity_Backend {
public:
    AP_Proximity_PYSITL(AP_Proximity &frontend) : AP_Proximity_Backend(frontend) {}

    // Adjust based on what the backend API in your old repo actually requires
    void update() {}  
};
