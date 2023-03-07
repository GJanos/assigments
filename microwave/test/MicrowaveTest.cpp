#include "Microwave.h"

#include "MLight.h"
#include "MMotor.h"
#include "MSystem.h"
#include "MUserInterface.h"

using ::testing::_;
using ::testing::Return;

class MicrowaveTest : public ::testing::Test
{
protected:
    MicrowaveTest()
        : microwave(light, motor, system, ui)
    {
    }

    virtual ~MicrowaveTest() {}

    MLight light;
    MMotor motor;
    MSystem system;
    MUserInterface ui;
    Microwave microwave;
};

TEST_F(MicrowaveTest, idle_start)
{
    // EXPECT_CALL(ui, GetRequestedPower()).WillOnce(Return(800));
    // EXPECT_CALL(motor, SetPower(800));
    EXPECT_EQ(STATE_HEATING, microwave.HandleIdleState(EV_START));
}

TEST_F(MicrowaveTest, idle_door_open)
{
    EXPECT_EQ(STATE_DOOR_OPENED, microwave.HandleIdleState(EV_DOOR_OPEN));
}

TEST_F(MicrowaveTest, door_open_door_close)
{
    microwave.HandleEvent(EV_DOOR_OPEN);
    EXPECT_EQ(STATE_IDLE, microwave.HandleDoorOpenedState(EV_DOOR_CLOSE));
}

TEST_F(MicrowaveTest, door_open_start)
{
    microwave.HandleEvent(EV_DOOR_OPEN);
    EXPECT_EQ(STATE_PAUSE, microwave.HandleDoorOpenedState(EV_START));
}

TEST_F(MicrowaveTest, pause_clk_reset)
{
    microwave.HandleEvent(EV_DOOR_OPEN);
    microwave.HandleEvent(EV_START);
    EXPECT_EQ(STATE_DOOR_OPENED, microwave.HandlePauseState(EV_CLOCK_RESET));
}

TEST_F(MicrowaveTest, pause_door_close)
{
    microwave.HandleEvent(EV_DOOR_OPEN);
    microwave.HandleEvent(EV_START);
    EXPECT_EQ(STATE_HEATING, microwave.HandlePauseState(EV_DOOR_CLOSE));
}

TEST_F(MicrowaveTest, heating_timer_up)
{
    microwave.HandleEvent(EV_START);
    EXPECT_EQ(STATE_IDLE, microwave.HandleHeatingState(EV_TIME_UP));
}

TEST_F(MicrowaveTest, heating_door_open)
{
    microwave.HandleEvent(EV_START);
    EXPECT_EQ(STATE_PAUSE, microwave.HandleHeatingState(EV_DOOR_OPEN));
}

TEST_F(MicrowaveTest, heating_power_change)
{
    microwave.HandleEvent(EV_START);
    EXPECT_EQ(STATE_HEATING, microwave.HandleHeatingState(EV_POWER_CHANGE));
}

TEST_F(MicrowaveTest, heating_power_change_func)
{
    EXPECT_CALL(ui, GetRequestedPower()).WillOnce(Return(800));
    EXPECT_CALL(motor, SetPower(800));
    microwave.HandleEvent(EV_START);
    EXPECT_EQ(STATE_HEATING, microwave.HandleHeatingState(EV_POWER_CHANGE));
}

TEST_F(MicrowaveTest, heating_time_up_func)
{
    microwave.HandleEvent(EV_START);
    EXPECT_CALL(motor, SetPower(0));
    EXPECT_CALL(light, Off());
    EXPECT_CALL(ui, StopClock());
    EXPECT_CALL(ui, Ping());

        EXPECT_EQ(STATE_IDLE, microwave.HandleHeatingState(EV_TIME_UP));
}
/*
TEST_F(MicrowaveTest, idle_door_open)
{
    EXPECT_EQ(STATE_DOOR_OPENED, microwave.HandleIdleState(EV_DOOR_OPEN));
}

TEST_F(MicrowaveTest, door_open_door_close)
{
    microwave.HandleEvent(EV_DOOR_OPEN);
    EXPECT_EQ(STATE_IDLE, microwave.HandleDoorOpenedState(EV_DOOR_CLOSE));
}

TEST_F(MicrowaveTest, door_open_start)
{
    microwave.HandleEvent(EV_DOOR_OPEN);
    EXPECT_EQ(STATE_PAUSE, microwave.HandleDoorOpenedState(EV_START));
}

TEST_F(MicrowaveTest, pause_clk_reset)
{
    microwave.HandleEvent(EV_DOOR_OPEN);
    microwave.HandleEvent(EV_START);
    EXPECT_EQ(STATE_DOOR_OPENED, microwave.HandlePauseState(EV_CLOCK_RESET));
}

TEST_F(MicrowaveTest, pause_door_close)
{
    microwave.HandleEvent(EV_DOOR_OPEN);
    microwave.HandleEvent(EV_START);
    EXPECT_EQ(STATE_HEATING, microwave.HandlePauseState(EV_DOOR_CLOSE));
}

TEST_F(MicrowaveTest, heating_timer_up)
{
    microwave.HandleEvent(EV_START);
    EXPECT_EQ(STATE_IDLE, microwave.HandleHeatingState(EV_TIME_UP));
}

TEST_F(MicrowaveTest, heating_door_open)
{
    microwave.HandleEvent(EV_START);
    EXPECT_EQ(STATE_PAUSE, microwave.HandleHeatingState(EV_DOOR_OPEN));
}

TEST_F(MicrowaveTest, heating_power_change)
{
    microwave.HandleEvent(EV_START);
    EXPECT_EQ(STATE_HEATING, microwave.HandleHeatingState(EV_POWER_CHANGE));
}
*/