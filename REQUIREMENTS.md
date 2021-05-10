Requirements for DebugSerial class

----

# Objectives

- use UART for "fire and forget" debug messages and simple input, in the development phase of a project
- optimize battery life by enabling *suppression* of debug messages when "no one is listening", i.e. when he device has been deployed and no FTDI module or similar is connected

# Requirements

- [x] `R20` same send/receive functions as standard Arduino Serial class
- [x] `R21` send printf-style formatted strings
- [x] `R22` detect if an FTDI module or similar is connected, so debug messages can be suppressed if no one is listening
