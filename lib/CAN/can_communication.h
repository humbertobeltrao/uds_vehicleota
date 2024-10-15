#ifndef CAN_COMMUNICATION_H
#define CAN_COMMUNICATION_H

#include <SPI.h>
#include "mcp_can.h"

// CAN communication constants
extern const int CS_PIN;
extern const int CAN_INT_PIN;
extern const int CAN_DEBUG_LED;
extern const long BCM_REQUEST_CAN_ID;
extern const long BCM_RESPONSE_CAN_ID;

// CAN Interrupt flag
extern volatile bool messageReceived;
extern unsigned long int rxId;               // Stores received CAN message ID
extern unsigned char rxBuf[8];  // Stores received CAN data buffer
extern unsigned char rxLen;     // Stores the length of received CAN message

// Function declarations
void initCAN();
void sendCANMessage(byte data[], byte len);
void IRAM_ATTR receiveCANInterrupt();  // Interrupt Service Routine (ISR)
bool checkCANMessage();
void processCANMessage();

#endif
