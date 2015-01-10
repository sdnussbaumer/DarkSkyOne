/*
 * ComTCP.h
 *
 *  Created on: 27.07.2014
 *      Author: san
 */

#ifndef COMTCP_H_
#define COMTCP_H_

namespace comstack {

struct stTCP {
	char sourceport;
	char destport;
	char seqnr;
	char aknnr;
	char ctrflags;
	char length;
	char data[241];
};

class ComTCP {
public:
	ComTCP();
	virtual ~ComTCP();
};

} /* namespace comstack */
#endif /* COMTCP_H_ */
