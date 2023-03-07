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

TEST_F(MicrowaveTest, test_start_event)
{
    // EXPECT_CALL(ui, GetRequestedPower()).WillOnce(Return(800));
    // EXPECT_CALL(motor, SetPower(800));
    EXPECT_EQ(STATE_HEATING, microwave.HandleIdleState(EV_START));
}

TEST_F(MicrowaveTest, test_door_open_event)
{
    EXPECT_EQ(STATE_DOOR_OPENED, microwave.HandleIdleState(EV_DOOR_OPEN));
}

TEST_F(MicrowaveTest, test_door_close_event)
{
    microwave.HandleEvent(EV_DOOR_OPEN);
    EXPECT_EQ(STATE_IDLE, microwave.HandleDoorOpenedState(EV_DOOR_CLOSE));
}
/*

TEST_F(MicrowaveTest, test_door_open_event)
{
    EXPECT_EQ(STATE_DOOR_OPENED, microwave.HandleIdleState(EV_DOOR_OPEN));
}
TEST_F(MicrowaveTest, test_door_open_event)
{
    EXPECT_EQ(STATE_DOOR_OPENED, microwave.HandleIdleState(EV_DOOR_OPEN));
}
TEST_F(MicrowaveTest, test_door_open_event)
{
    EXPECT_EQ(STATE_DOOR_OPENED, microwave.HandleIdleState(EV_DOOR_OPEN));
}
*/