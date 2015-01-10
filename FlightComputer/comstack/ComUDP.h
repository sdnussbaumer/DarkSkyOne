/*
 * ComUDP.h
 *
 *  Created on: 27.07.2014
 *      Author: san
 */

#ifndef COMUDP_H_
#define COMUDP_H_

namespace comstack {

struct stUDP {
	char sourceport;
	char destport;
	char length;
	char data[244];
};

class ComUDP {
public:
	ComUDP();
	virtual ~ComUDP();
};

} /* namespace comstack */
#endif /* COMUDP_H_ */
