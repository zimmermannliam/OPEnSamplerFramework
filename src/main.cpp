//
//  main.cpp
//  OPEnSamplerFramework
//
//  Created by Kawin on 2/10/19.
//  Copyright © 2019 Kawin. All rights reserved.
//

#include "OPSystem.hpp"


// LED blinking demo
void initialize() {
    pinMode(LED_BUILTIN, OUTPUT);

    OPActionSequence bl("blink");
    bl.delay(100, []() {
        digitalWrite(LED_BUILTIN, HIGH);
    }).delay(100, []() {
        digitalWrite(LED_BUILTIN, LOW);
    });

    // Blink 5 times
    app.scheduler.schedule(bl.then(bl).then(bl).then(bl).then(bl));
}

void update() {

}

OPSystem app(initialize, update);
