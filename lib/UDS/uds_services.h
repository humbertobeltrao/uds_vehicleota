#ifndef UDS_SERVICES_H
#define UDS_SERVICES_H

enum UDSState {
    DIAGNOSTIC_SESSION_CONTROL,
    DTC_SETTING,
    PROGRAMMING_SESSION
};

extern UDSState currentState;

void handleUDSStateMachine();

#endif
