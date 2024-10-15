#include "uds_services.h"
#include "can_communication.h"

UDSState currentState = DIAGNOSTIC_SESSION_CONTROL;

void handleUDSStateMachine() {
    switch (currentState) {
        case DIAGNOSTIC_SESSION_CONTROL:
        {
            Serial.println("Sending Diagnostic Session Control request...");
            byte diagRequest[] = {0x02, 0x10, 0x02};  // Example UDS request
            sendCANMessage(diagRequest, sizeof(diagRequest));
            currentState = DTC_SETTING;
              break;
        }
        case DTC_SETTING:
        {
            Serial.println("Sending Control DTC Setting request...");
            byte dtcRequest[] = {0x02, 0x85, 0x02};  // Example DTC request
            sendCANMessage(dtcRequest, sizeof(dtcRequest));
            currentState = PROGRAMMING_SESSION;
            break;
        }
        case PROGRAMMING_SESSION:
        {
            Serial.println("Programming session in progress...");
            // Add your programming logic here
            break;
        }
        default:
        {
            Serial.println("Invalid state.");
              break;
        }
    }
}
