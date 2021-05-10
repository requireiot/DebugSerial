/**
 * @file          DebugSerial.h
 *
 * Created		: 07-Mar-2020
 * Author		: Bernd Waldmann
 * Tabsize		: 4
 *
 * This Revision: $Id: DebugSerial.h 996 2021-05-07 08:02:26Z  $
 *
 * @brief Debug output to UART if FTDI module is connected
 */
 
/*
   Copyright (C)2021 Bernd Waldmann

   This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
   If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/

   SPDX-License-Identifier: MPL-2.0
*/

#ifndef DEBUG_SERIAL
#define DEBUG_SERIAL

#include <stdarg.h>
#include <HardwareSerial.h>

class DebugSerialClass : public Print {
protected:
	HardwareSerial& _serial;
	bool m_disabled;
public:
	DebugSerialClass( HardwareSerial& serial );
	virtual size_t write(uint8_t);
	virtual void flush();
	using Print::write;
	
	void printf(const char* fmt, ...);
	void printf(const __FlashStringHelper *fmt, ...);
	void vprintf(const char* fmt, va_list args);
	void vprintf(const __FlashStringHelper *fmt, va_list args);
};


void debug_printf(const char* fmt, ...) __attribute__((weak));


#endif // DEBUG_SERIAL
