/*
 * ComDataLink.h
 *
 *  Created on: 27.07.2014
 *      Author: san
 */

#ifndef COMDATALINK_H_
#define COMDATALINK_H_

#include "ComNetwork.h"

namespace comstack {

static const char SOH = 0x01;
static const char DLE = 0x10;

struct stDataLink {
	static const char soh = SOH;
	char length;
	char dataframe[255];
	short unsigned int CRC16;
};

class ComDataLink {
public:
	ComDataLink();
	virtual ~ComDataLink();
	void addNetworkLayer(ComNetwork net);
};

} /* namespace comstack */
#endif /* COMDATALINK_H_ */
