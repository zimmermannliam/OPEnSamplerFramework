//
//  OPComponent.hpp
//  OPEnSamplerFramework
//
//  Created by Kawin on 2/10/19.
//  Copyright © 2019 Kawin. All rights reserved.
//

#pragma once
#include "Arduino.h"

static String Unnamed = "Unnamed";
static int Unavailable = -1;

/*
    OPComponent defines two abstract methods that must be overrided by the subclass to
    provide injection onto the main loop.
    - setup()
    - loop()
*/
class OPComponent {
public:
    String name = Unnamed;
    int pin = Unavailable;
    
    OPComponent() {

    }

    OPComponent(String name = Unnamed, int pin = Unavailable) 
    :
    name(name), pin(pin) {
        
    }
    
    virtual void setup() {

    }

    virtual void loop() {

    }
};
