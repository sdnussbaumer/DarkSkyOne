/*
 * ComNetwork.h
 *
 *  Created on: 27.07.2014
 *      Author: san
 */

#ifndef COMNETWORK_H_
#define COMNETWORK_H_

namespace comstack {

static const char TCP = 0x06;
static const char UDP = 0x11;

struct stNetwork {
	char protocolid;
	char totallength;
	char sourceaddr;
	char destaddr;
	char packet[247];
};

class ComNetwork {
public:
	ComNetwork();
	virtual ~ComNetwork();
};

} /* namespace comstack */
#endif /* COMNETWORK_H_ */
