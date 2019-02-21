//
//  main.cpp
//  OPEnSamplerFramework
//
//  Created by Kawin on 2/10/19.
//  Copyright © 2019 Kawin. All rights reserved.
//

#include "OPSystem.hpp"
#include "OPSerialParser.hpp"
#include "OPLEDComponent.hpp"
#include "OPShiftRegisterComponent.hpp"

OPSystem app([] () {
    // Init
    // auto serial = new OPSerialParser();
    // app.addComponent(serial);

    auto led = new OPLEDComponent("led", LED_BUILTIN);
    app.addComponent(led);

    // auto tpic = new OPShiftRegisterComponent("tpic", 32);
    // tpic->setPins(11, 13, 10);
    // app.addComponent(tpic);

    // auto led = new OPLEDComponent("led", LED_BUILTIN);
    // app.addComponent(led);

}, [] () {
    // Update
});
