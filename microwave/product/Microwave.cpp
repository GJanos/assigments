#include "Microwave.h"

#include <iostream>

Microwave::Microwave(ILight &light, IMotor &motor, ISystem &system, IUserInterface &ui)
    : currentState(STATE_IDLE), light(light), motor(motor), system(system), ui(ui)
{
}

States Microwave::HandleIdleState(Events ev)
{
    States result = STATE_IDLE;

    switch (ev)
    {
    case EV_START:
        result = STATE_HEATING;
        light.On();
        ui.StartClock();
        break;

    case EV_DOOR_OPEN:
        result = STATE_DOOR_OPENED;
        break;

    default:
        // ignored event, nothing to do here
        break;
    }
    return result;
}

States Microwave::HandleDoorOpenedState(Events ev)
{
    States result = STATE_IDLE;

    switch (ev)
    {
    case EV_START:
        result = STATE_PAUSE;
        break;

    case EV_DOOR_CLOSE:
        result = STATE_IDLE;
        break;

    default:
        // ignored event, nothing to do here
        break;
    }

    return result;
}

States Microwave::HandleHeatingState(Events ev)
{
    States result = STATE_IDLE;
    motor.SetPower(ui.GetRequestedPower());
    switch (ev)
    {
    case EV_TIME_UP:
        result = STATE_IDLE;
        light.Off();
        ui.StopClock();
        ui.Ping();
        motor.SetPower(0);
        break;

    case EV_POWER_CHANGE:
        result = STATE_HEATING;
        break;

    case EV_DOOR_OPEN:
        result = STATE_PAUSE;
        ui.StopClock();
        motor.SetPower(0);
        break;

    default:
        // ignored event, nothing to do here
        break;
    }

    return result;
}

States Microwave::HandlePauseState(Events ev)
{
    States result = STATE_IDLE;
    switch (ev)
    {
    case EV_DOOR_CLOSE:
        result = STATE_HEATING;
        light.On();
        ui.StartClock();
        break;

    case EV_CLOCK_RESET:
        result = STATE_DOOR_OPENED;
        break;

    default:
        // ignored event, nothing to do here
        break;
    }

    return result;
}

void Microwave::HandleEvent(Events ev)
{
    switch (currentState)
    {
    case STATE_IDLE:
        currentState = HandleIdleState(ev);
        break;

    case STATE_DOOR_OPENED:
        currentState = HandleDoorOpenedState(ev);
        break;

    case STATE_HEATING:
        currentState = HandleHeatingState(ev);
        break;

    case STATE_PAUSE:
        currentState = HandlePauseState(ev);
        break;

    default:
        std::cerr << "ERROR: illegal/unhandled state with number: " << currentState;
        break;
    };
}
