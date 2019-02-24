//
//  main.cpp
//  OPEnSamplerFramework
//
//  Created by Kawin on 2/10/19.
//  Copyright © 2019 Kawin. All rights reserved.
//

#include "OPSystem.hpp"
#include "OPShiftRegisterComponent.hpp"


// TODO: Integrate Async to OPSystem

// LED blinking demo
void initialize() {
    pinMode(LED_BUILTIN, OUTPUT);

    OPActionSequence bl("blink");
    bl.delay(100, []() {
        digitalWrite(LED_BUILTIN, HIGH);
    }).delay(500, []() {
        digitalWrite(LED_BUILTIN, LOW);
    });
    bl.repeat = -1;

    run(bl);
}

void update() {

}

OPSystem app(initialize, update);
