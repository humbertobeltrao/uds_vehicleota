#include "can_communication.h"

// MCP_CAN object initialization
MCP_CAN CAN(4);  // Using pin 4 for CS (SPI Chip Select)

const int CS_PIN = 4;           
const int CAN_INT_PIN = 27;       // CAN interruption pin
const int CAN_DEBUG_LED = 25;     // Debug LED

const long BCM_REQUEST_CAN_ID = 0x18DA40F1;
const long BCM_RESPONSE_CAN_ID = 0x98DAF140;

volatile bool messageReceived = false;  // Interrupt flag
long unsigned int rxId;                          // Received CAN message ID
unsigned char rxBuf[8];                 // Data buffer for received message
unsigned char rxLen = 0;                // Length of received message

// CAN initialization
void initCAN() {
    // Initialize CAN communication at 500 kbps
    if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
        Serial.println("CAN Initialized Successfully!");
    } else {
        Serial.println("CAN Initialization Failed.");
        while (1);
    }

    // Set the MCP2515 in normal mode to communicate
    CAN.setMode(MCP_NORMAL);

    // Set up the CAN INT pin
    pinMode(CAN_INT_PIN, INPUT); 

    // Attach interrupt for the CAN INT pin
    attachInterrupt(digitalPinToInterrupt(CAN_INT_PIN), receiveCANInterrupt, RISING);
}

// Send CAN message
void sendCANMessage(byte data[], byte len) {
    if (CAN.sendMsgBuf(BCM_REQUEST_CAN_ID, 1, len, data) == CAN_OK) {
        Serial.println("Message Sent Successfully");
    } else {
        Serial.println("Error Sending Message");
    }
}

// Interrupt Service Routine (ISR)
void IRAM_ATTR receiveCANInterrupt() {
    messageReceived = true;  // Set flag to indicate a message was received
    Serial.print("na interrupção");
}

// Check if a message is available and read it
bool checkCANMessage() {
    if (CAN.checkReceive() == CAN_MSGAVAIL) {
        CAN.readMsgBuf(&rxId, &rxLen, rxBuf);
        return true;
    }
    return false;
}

// Process the received CAN message
void processCANMessage() {
    if (rxId == BCM_RESPONSE_CAN_ID) {
        Serial.print("Received response from BCM: ");
        for (int i = 0; i < rxLen; i++) {
            Serial.print(rxBuf[i], HEX);
            Serial.print(" ");
        }
        Serial.println();
    } else {
        Serial.println("Received message from unknown ECU.");
    }
}
