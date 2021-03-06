/**
 * @file sniffer_monitor.c
 */
/* Copyright (C) 2016 by Arjan van Vught mailto:info@raspberrypi-dmx.nl
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "monitor.h"
#include "midi.h"
#include "console.h"

void monitor_update(void) {
	// Handle Active Sensing messages
	switch (midi_get_active_sense_state()) {
	case MIDI_ACTIVE_SENSE_ENABLED:
		console_save_cursor();
		console_set_cursor(70, 3);
		console_set_fg_bg_color(CONSOLE_BLACK, CONSOLE_WHITE);
		(void) console_puts("ACTIVE SENSING          ");
		console_restore_cursor();
		break;
	case MIDI_ACTIVE_SENSE_FAILED:
		console_save_cursor();
		console_set_cursor(70, 3);
		console_set_fg_bg_color(CONSOLE_RED, CONSOLE_WHITE);
		(void) console_puts("ACTIVE SENSING - Failed!");
		console_restore_cursor();
		break;
	default:
		break;
	}

	monitor_time_uptime(2);
}
