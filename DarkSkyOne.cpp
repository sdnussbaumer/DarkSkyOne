// Do not remove the include below
#include "DarkSkyOne.h"
#include "SCoop.h"
#include "LogUtils.h"
#include "Wdt.h"
#include "SerialIP.h"

// Global variables
int led = 13;
LogUtils* logutils;

defineTask(LogTask)

// LogTask Thread
void LogTask::setup()
{
}

void LogTask::loop()
{
	logutils->processLogs();
}

defineTask(XBeeTask)

// This function is going to use uIP's protosockets to handle the connection.
// This means it must return int, because of the way the protosockets work.
// In a nutshell, when a PSOCK_* macro needs to wait for something, it will
// return from handle_connection so that other work can take place.  When the
// event is triggered, uip_callback() will call this function again and the
// switch() statement (see below) will take care of resuming execution where
// it left off.  It *looks* like this function runs from start to finish, but
// that's just an illusion to make it easier to code :-)
int handle_connection(uip_tcp_appstate_t *s, connection_data *d)
{
  logutils->logTrace(logutils->trace3, "Enter handle_connection");

  // All protosockets must start with this macro.  Its internal implementation
  // is that of a switch() statement, so all code between PSOCK_BEGIN and
  // PSOCK_END is actually inside a switch block.  (This means for example,
  // that you can't declare variables in the middle of it!)
  PSOCK_BEGIN(&s->p);

  // Send some text over the connection.
  PSOCK_SEND_STR(&s->p, "Hello. What is your name?\n");

  // Read some returned text into the input buffer we set in PSOCK_INIT.  Data
  // is read until a newline (\n) is received, or the input buffer gets filled
  // up.  (Which, at 16 chars by default, isn't hard!)
  PSOCK_READTO(&s->p, '\n');

  // Since any subsequent PSOCK_* functions would overwrite the buffer, we
  // need to make a copy of it first.  We can't use a local variable for this,
  // because any PSOCK_* macro may make the function return and resume later,
  // thus losing the data in any local variables.  This is why uip_callback
  // has allocated the connection_data structure for us to use instead.  (You
  // can add/remove other variables in this struct to store different data.
  // See the other file in this sketch, serialip_conn.h)
  strncpy(d->name, d->input_buffer, sizeof(d->name));
  // Note that this will misbehave when the input buffer overflows (i.e.
  // more than 16 characters are typed in) but hey, this is supposed to be
  // a simple example.  Fixing this problem will be left as an exercise for
  // the reader :-)

  // Send some more data over the connection.
  PSOCK_SEND_STR(&s->p, "Hello ");
  PSOCK_SEND_STR(&s->p, d->name);

  // Disconnect.
  PSOCK_CLOSE(&s->p);

  // All protosockets must end with this macro.  It closes the switch().
  PSOCK_END(&s->p);

  logutils->logTrace(logutils->trace3, "Exit handle_connection");
}

void uip_callback(uip_tcp_appstate_t *s)
{
  logutils->logTrace(logutils->trace3, "Enter uip_callback");

  if (uip_connected()) {

    // We want to store some data in our connections, so allocate some space
    // for it.  The connection_data struct is defined in a separate .h file,
    // due to the way the Arduino IDE works.  (typedefs come after function
    // definitions.)
    connection_data *d = (connection_data *)malloc(sizeof(connection_data));

    // Save it as SerialIP user data so we can get to it later.
    s->user = d;

    // The protosocket's read functions need a per-connection buffer to store
    // data they read.  We've got some space for this in our connection_data
    // structure, so we'll tell uIP to use that.
    PSOCK_INIT(&s->p, d->input_buffer, sizeof(d->input_buffer));

  }

  // Call/resume our protosocket handler.
  handle_connection(s, (connection_data *)s->user);

  // If the connection has been closed, release the data we allocated earlier.
  if (uip_closed()) {
    if (s->user) free(s->user);
    s->user = NULL;
  }

  logutils->logTrace(logutils->trace3, "Exit uip_callback");
}

// XBee Thread
void XBeeTask::setup()
{
	logutils->logTrace(logutils->trace3, "Enter XBeeTask::setup()");

	Serial1.begin(115200);
	while (!Serial1) {
	  ; // wait for serial port to connect. Needed for Leonardo only
	}

	// Tell SerialIP which serial port to use (some boards have more than one.)
	// Currently this is limited to HardwareSerial ports, until both it and
	// SoftwareSerial inherit from a common base class.
	SerialIP.use_device(Serial1);

	// We're going to be handling uIP events ourselves.  Perhaps one day a simpler
	// interface will be implemented for the Arduino IDE, but until then...
	SerialIP.set_uip_callback(uip_callback);

	// Set the IP address we'll be using.  Make sure this doesn't conflict with
	// any IP addresses or subnets on your LAN or you won't be able to connect to
	// either the Arduino or your LAN...
	IP_ADDR myIP = {192,168,131,70};
	IP_ADDR subnet = {255,255,255,0};
	SerialIP.begin(myIP, subnet);

	// If you'll be making outgoing connections from the Arduino to the rest of
	// the world, you'll need a gateway set up.
	//IP_ADDR gwIP = {192,168,5,1};
	//SerialIP.set_gateway(gwIP);

	// Listen for incoming connections on TCP port 1000.  Each incoming
	// connection will result in the uip_callback() function being called.
	SerialIP.listen(1000);

	logutils->logTrace(logutils->trace3, "Exit XBeeTask::setup()");
}

void XBeeTask::loop()
{
	SerialIP.tick();
}

defineTask(HeartBeatTask)

// HeartBeat Thread
void HeartBeatTask::setup()
{
	logutils->logTrace(logutils->trace3, "Enter HeartBeatTask::setup()");

	pinMode(led, OUTPUT);

	logutils->logTrace(logutils->trace3, "Exit HeartBeatTask::setup()");
}

void HeartBeatTask::loop()
{
	logutils->logTrace(logutils->trace3, "Enter HeartBeatTask::loop()");

	digitalWrite(led, HIGH);
    sleep(500);
	digitalWrite(led, LOW);
	sleep(500);

	logutils->logTrace(logutils->trace3, "Exit HeartBeatTask::loop()");
}

//The setup function is called once at startup of the sketch
void setup()
{
	// Initialize Watchdog

	// You have to edit the variants.cpp file in the Arduino core and comment the line "WDT_disable(WDT);"
	// inside the init function. Else it's not possible to set WDT_Enable again.

	#define __WDP_MS 2048
	WDT_Enable ( WDT, 0x2000 | __WDP_MS | ( __WDP_MS << 16 ) );

	// Initialize Log class
	logutils = new LogUtils;
	logutils->setLogLevel(logutils->trace3);

	logutils->logTrace(logutils->trace3, "Main::setup()");

	// Add your initialization code here
	mySCoop.start();
}

// The loop function is called in an endless loop
void loop()
{
	//Add your repeated code here
	yield();

	// Reset Watchdog
	WDT_Restart( WDT );
}
