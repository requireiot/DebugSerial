DebugSerial.h
=============

Conditional debug output for ATmega controllers.

Send printf-style formatted output if "someone is listening", i.e. an FTDI module or similar is connected. 

The same logic is used in my `AvrUART` library (https://github.com/requireiot/AvrUART) for non-Arduino projects.

See [requirements](REQUIREMENTS.md) for objectives.

Suppressing debug messages when battery-operated
------------------------------------------------
Oftentimes in AVR projects, UART output is used for debug messages during development. For battery-powered devices that spend most of the time in a sleep mode, having lengthy debug messages sent out at maybe 9600 Baud when no PC is connected, and nobody is listening, increases the wake time of the device, and thereby decreases battery life.
For these cases, I have adopted the following convention in my projects:
* the UART RxD pin is pulled down with a 1 MOhm resistor. 
* during development, an FTDI serial module will be connected, which pulls the RxD high while no communication is ongoing
* when deployed and battery operated, no FTDI serial module is connected, so the RxD pin permanently reads as low
* RxD low after bootup is taken as an indication that debug messages can be suppressed

Member `m_disabled` is `true` if RxD is pulled low. 

The same effect could be achieved, of course, by re-compiling the code just before deployment, in "release mode", with all debug messages removed ... but then you have to recompile, code size changes, and you can't just bring back a devive from deployment, hook it up to an FTDI module, reboot it and look at the debug messages ...

Dependencies
------------
UART communication uses the normla Arduino `HardwareSerial` class.
