/*
 * ComStack.h
 *
 *  Created on: 19.07.2014
 *      Author: san
 */

#ifndef COMSTACK_H_
#define COMSTACK_H_

#include "ComDataLink.h"
#include "ComNetwork.h"
#include "ComTCP.h"
#include "ComUDP.h"

namespace comstack {

class ComStack {
public:
	ComStack();
	virtual ~ComStack();
};

}

#endif /* COMSTACK_H_ */
