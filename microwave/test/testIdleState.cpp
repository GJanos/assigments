#include "Microwave.h"

#include "MLight.h"
#include "MMotor.h"
#include "MSystem.h"
#include "MUserInterface.h"

using ::testing::_;
using ::testing::Return;

class TestIdleState : public ::testing::Test
{
protected:
    TestIdleState()
        : microwave(light, motor, system, ui)
    {
    }

    virtual ~TestIdleState() {}

    MLight light;
    MMotor motor;
    MSystem system;
    MUserInterface ui;
    Microwave microwave;
};

TEST_F(TestIdleState, test_start_event)
{
    // EXPECT_CALL(ui, GetRequestedPower()).WillOnce(Return(800));
    // EXPECT_CALL(motor, SetPower(800));
    EXPECT_EQ(STATE_HEATING, microwave.HandleIdleState(EV_START));
}

TEST_F(TestIdleState, test_start_event)
{
    // EXPECT_CALL(ui, GetRequestedPower()).WillOnce(Return(800));
    // EXPECT_CALL(motor, SetPower(800));
    EXPECT_EQ(STATE_DOOR_OPENED, microwave.HandleIdleState(EV_DOOR_OPEN));
}