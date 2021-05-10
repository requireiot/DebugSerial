/**
 * @file          DebugSerial.cpp
 *
 * Created		: 07-Mar-2020
 * Author		: Bernd Waldmann
 * Tabsize		: 4
 *
 * This Revision: $Id: DebugSerial.cpp 1016 2021-05-10 10:22:10Z  $
 * 
 * @brief Output strings to UART via HardwareSerial class, unless RXD is pulled low, 
 * i.e. FTDI not connected.
 */

/*
   Copyright (C) 2020,2021 Bernd Waldmann

   This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
   If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/

   SPDX-License-Identifier: MPL-2.0
*/

/**
	@defgroup  DebugSerial  <DebugSerial.h>: debug output to UART
	@brief Output strings to UART via Serial class, unless RXD is pulled low, i.e. FTDI module is connected.
*/

#include <stdio.h>
#include <stdarg.h>
#include <avr/pgmspace.h>

#include <Arduino.h>
#include <HardwareSerial.h>

#include "DebugSerial.h"

/** @{ */

/**
 * @brief Construct a new Debug Serial Class object, and
 * detect if output should be suppressed
 * 
 * @param serial  the real UART that will be used for output
 */
DebugSerialClass::DebugSerialClass( HardwareSerial& serial ) : _serial(serial) 
{
	const uint8_t RXD = 0;	// RxD appears to be Arduino pin "0" on all models
	m_disabled = true;
	pinMode(RXD,INPUT);
	for (int i=0; i<100; i++) m_disabled &= (digitalRead(RXD)==LOW)	;
}


/**
 * @brief write a character (overloaded virtual functiom from Print class),
 * unless output is suppressed.
 */
size_t DebugSerialClass::write(uint8_t aByte)
{
	if (!m_disabled)
		return _serial.write(aByte);
	else 
		return 1;
}


/**
 * @brief wait until all output has been sent (overloaded virtual functiom from Print class)
 * 
 *//
void DebugSerialClass::flush()
{
	_serial.flush();
}


/**
 * @brief Write formatted string, format string in data memory,
 * unless output is suppressed.
 *   
 * @param fmt  pointer to format string, printf-style
 */
void DebugSerialClass::printf(const char *fmt,...)
{
	char buf[64];   // default size of Arduino Serial.print is 64
	va_list args;
	if (!m_disabled) {
		va_start (args, fmt);
		vsnprintf(buf, sizeof(buf), fmt, args);
		_serial.print(buf);
		va_end (args);
	}
}


/**
 * @brief write formatted string, 
 * literal format string (placed in program memory),
 * unless output is suppressed.
 * 
 * @param fmtp  literal format string, printf-style
 */
void DebugSerialClass::printf(const __FlashStringHelper *fmtp, ...)
{
	PGM_P fmt = reinterpret_cast<PGM_P>(fmtp);
	char buf[64];   // default size of Arduino Serial.print is 64
	va_list args;
	if (!m_disabled) {
		va_start (args, fmtp);
		vsnprintf_P(buf, sizeof(buf), fmt, args);
		_serial.print(buf);
		va_end (args);
	}	
}

/**
 * @brief write formatted string, varargs-style arguments, 
 * with format string in program memory,
 * unless output is suppressed,
 * 
 * @param fmt  pointer to format string in PROGMEM
 * @param args  varargs-style list 
 */
void DebugSerialClass::vprintf(const char* fmt, va_list args)
{
	char buf[64];   // default size of Arduino Serial.print is 64
	if (!m_disabled) {
		vsnprintf(buf, sizeof(buf), fmt, args);
		_serial.print(buf);
	}
}


/**
 * @brief write formatted string, varargs-style arguments, 
 * with literal format string (placed in program memory),
 * unless output is suppressed.
 * 
 * @param fmt  literal format string, printf-style
 * @param args  varargs-style list
 */
void DebugSerialClass::vprintf(const __FlashStringHelper *fmt, va_list args)
{
	char buf[64];   // default size of Arduino Serial.print is 64
	if (!m_disabled) {
		vsnprintf_P(buf, sizeof(buf), (const char*)fmt, args);
		_serial.print(buf);
	}
}

/** @} */
