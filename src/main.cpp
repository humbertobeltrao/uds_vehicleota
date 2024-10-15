#include <Arduino.h>
#include "can_communication.h"
#include "uds_services.h"

void setup() {
    Serial.begin(115200);

    // Initialize CAN communication
    initCAN();

    // Set initial UDS state
    currentState = DIAGNOSTIC_SESSION_CONTROL;
    handleUDSStateMachine();
}

void loop() {
    // If an interrupt has set the flag, process the message
    if (messageReceived) {
        messageReceived = false;  // Clear the interrupt flag

        // Check if a valid CAN message is available
        if (checkCANMessage()) {
            processCANMessage();  // Handle the received message

            // Continue with UDS state machine handling
            handleUDSStateMachine();
            delay(500);
        }
    }
}
