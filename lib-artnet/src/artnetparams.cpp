/**
 * @file artnetparams.c
 *
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

#include <stdint.h>

#include "read_config_file.h"
#include "sscan.h"
#include "util.h"

#include "artnetparams.h"

static const char PARAMS_FILE_NAME[] ALIGNED = "artnet.txt";	///< Parameters file name
static const char PARAMS_NET[] ALIGNED = "net";					///<
static const char PARAMS_SUBNET[] ALIGNED = "subnet";			///<
static const char PARAMS_UNIVERSE[] ALIGNED = "universe";		///<
static const char PARAMS_OUTPUT[] ALIGNED = "output";			///<

static uint8_t ArtNetParamsNet ALIGNED = 0;								///<
static uint8_t ArtNetParamsSubnet ALIGNED = 0;							///<
static uint8_t ArtNetParamsUniverse ALIGNED = 0;						///<
static _output_type ArtNetParamsOutputType ALIGNED = OUTPUT_TYPE_DMX;	///<

/**
 *
 * @param line
 */
static void process_line_read(const char *line) {
	char value[8] ALIGNED;
	uint8_t len = 3;
	uint8_t value8;

	if (sscan_uint8_t(line, PARAMS_NET, &value8) == 2) {
		ArtNetParamsNet = value8;
	} else if (sscan_uint8_t(line, PARAMS_SUBNET, &value8) == 2) {
		ArtNetParamsSubnet = value8;
	} else if (sscan_uint8_t(line, PARAMS_UNIVERSE, &value8) == 2) {
		ArtNetParamsUniverse = value8;
	} else if (sscan_char_p(line, PARAMS_OUTPUT, value, &len) == 2) {
		if(memcmp(value, "spi", 3) == 0) {
			ArtNetParamsOutputType = OUTPUT_TYPE_SPI;
		}
	}
}

/**
 *
 */
ArtNetParams::ArtNetParams(void) {
	ArtNetParamsNet = 0;
	ArtNetParamsSubnet = 0;
	ArtNetParamsUniverse = 0;
	ArtNetParamsOutputType= OUTPUT_TYPE_DMX;
}

/**
 *
 */
ArtNetParams::~ArtNetParams(void) {
}

/**
 *
 * @return
 */
const _output_type ArtNetParams::GetOutputType(void) {
	return ArtNetParamsOutputType;
}

/**
 *
 * @return
 */
const uint8_t ArtNetParams::GetNet(void) {
	return ArtNetParamsNet;
}

/**
 *
 * @return
 */
const uint8_t ArtNetParams::GetSubnet(void) {
	return ArtNetParamsSubnet;
}

/**
 *
 * @return
 */
const uint8_t ArtNetParams::GetUniverse(void) {
	return ArtNetParamsUniverse;
}

/**
 *
 */
bool ArtNetParams::Load(void) {
	return read_config_file(PARAMS_FILE_NAME, &process_line_read);
}


