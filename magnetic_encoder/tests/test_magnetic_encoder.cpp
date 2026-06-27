/*================================ FILE INFO =================================*/
/* Filename           : test_magnetic_encoder.cpp                             */
/*                                                                            */
/* Test implementation for magnetic_encoder.c                                 */
/*                                                                            */
/*============================================================================*/

/*============================================================================*/
/*                               Include Files                                */
/*============================================================================*/
extern "C"
{

#include <stdint.h>
#include "eic_hal.h"
#include "eic_hal_config.h"
#include "gpio_hal.h"
#include "gpio_hal_config.h"
#include "magnetic_encoder.h"

}

#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

/*============================================================================*/
/*                            Mock Implementations                            */
/*============================================================================*/
const struct eic_hal_handler *get_eic_hal_handler(void)
{
    return static_cast<const struct eic_hal_handler *>(
            mock().actualCall("get_eic_hal_handler").returnConstPointerValue());
}

const struct eic_handle *get_encoder_1_channel_a_eic_handle(void)
{
    return static_cast<const struct eic_handle *>(
            mock().actualCall("get_encoder_1_channel_a_eic_handle").returnConstPointerValue());
}

const struct eic_handle *get_encoder_2_channel_a_eic_handle(void)
{
    return static_cast<const struct eic_handle *>(
            mock().actualCall("get_encoder_2_channel_a_eic_handle").returnConstPointerValue());
}

const struct gpio_hal_handler *get_gpio_hal_handler(void)
{
    return static_cast<const struct gpio_hal_handler *>(
            mock().actualCall("get_gpio_hal_handler").returnConstPointerValue());
}

const struct gpio_handle *get_encoder_1_channel_b_handle(void)
{
    return static_cast<const struct gpio_handle *>(
            mock().actualCall("get_encoder_1_channel_b_handle").returnConstPointerValue());
}

const struct gpio_handle *get_encoder_2_channel_b_handle(void)
{
    return static_cast<const struct gpio_handle *>(
            mock().actualCall("get_encoder_2_channel_b_handle").returnConstPointerValue());
}

/*============================================================================*/
/*                             Public Definitions                             */
/*============================================================================*/
/* EIC mocks */
/* the definition of "struct eic_handle" is hardware specific, so we mock */
struct eic_handle {
    uint32_t mock_value;
};

const struct eic_handle mock_eic_handles[] = {{0}, {0}, {0}, {0}};

bool mock_external_callback_set_flags[] = {false, false};

enum external_callback_index
{
    EXTERNAL_CALLBACK_1_INDEX = 0,
    EXTERNAL_CALLBACK_2_INDEX,
    EXTERNAL_CALLBACK_COUNT
};

void dummy_init_eic(void) {}
void dummy_deinit_eic(void) {}
void mock_set_external_callback(const struct eic_handle *handle, void (*callback)(void))
{
    CHECK(callback != nullptr);
    for (uint32_t i{0u}; i < EXTERNAL_CALLBACK_COUNT; i++) {
        if (handle == &(mock_eic_handles[i])) {
            mock_external_callback_set_flags[i] = true;
        }
    }
}

const struct eic_hal_handler mock_eic_handler = {
        dummy_init_eic,
        dummy_deinit_eic,
        mock_set_external_callback};

/* -------------------------------------------------------------------------- */
/* GPIO mocks */
/* the definition of "struct gpio_handle" is hardware specific, so we mock */
struct gpio_handle {
    uint32_t mock_value;
};

const struct gpio_handle mock_gpio_handles[] = {{0}, {0}};

bool mock_gpio_inputs[] = {false, false};

enum gpio_index
{
    ENCODER_1_INDEX = 0,
    ENCODER_2_INDEX,
    GPIO_COUNT
};

void set_mock_input(enum gpio_index index, bool value)
{
    mock_gpio_inputs[index] = value;
}

void dummy_init_gpio(void) {}
void dummy_deinit_gpio(void) {}
bool mock_read_gpio_pin(const struct gpio_handle *handle)
{
    for (uint32_t i{0u}; i < GPIO_COUNT; i++) {
        if (handle == &(mock_gpio_handles[i])) {
            return mock_gpio_inputs[i];
        }
    }
    return 0;
}
void dummy_write_gpio_pin(const struct gpio_handle *handle, bool value) {}
void dummy_toggle_gpio_pin(const struct gpio_handle *handle) {}

const struct gpio_hal_handler mock_gpio_handler = {
        dummy_init_gpio,
        dummy_deinit_gpio,
        mock_read_gpio_pin,
        dummy_write_gpio_pin,
        dummy_toggle_gpio_pin};

/* -------------------------------------------------------------------------- */
/* test helpers */
void reset_external_callback_set_flags(void)
{
    memset(mock_external_callback_set_flags, false, sizeof(mock_external_callback_set_flags));
}

void reset_mock_inputs(void)
{
    memset(mock_gpio_inputs, false, sizeof(mock_gpio_inputs));
}

void init_magnetic_encoders_with_cpputest_checks(void)
{
    mock().expectOneCall("get_eic_hal_handler").andReturnValue(&mock_eic_handler);
    mock().expectOneCall("get_encoder_1_channel_a_eic_handle")
            .andReturnValue(&(mock_eic_handles[EXTERNAL_CALLBACK_1_INDEX]));
    mock().expectOneCall("get_encoder_2_channel_a_eic_handle")
            .andReturnValue(&(mock_eic_handles[EXTERNAL_CALLBACK_2_INDEX]));
    mock().expectOneCall("get_gpio_hal_handler").andReturnValue(&mock_gpio_handler);
    mock().expectOneCall("get_encoder_1_channel_b_handle")
            .andReturnValue(&(mock_gpio_handles[ENCODER_1_INDEX]));
    mock().expectOneCall("get_encoder_2_channel_b_handle")
            .andReturnValue(&(mock_gpio_handles[ENCODER_2_INDEX]));
    init_magnetic_encoders();
}

/*============================================================================*/
/*                                 Test Group                                 */
/*============================================================================*/
TEST_GROUP(MagneticEncoderTests)
{
    void setup() override
    {
        reset_external_callback_set_flags();
        reset_mock_inputs();
        mock().clear();
    }

    void teardown() override
    {
        mock().checkExpectations();
        mock().clear();
        reset_mock_inputs();
        reset_external_callback_set_flags();
    }
};

/*============================================================================*/
/*                                    Tests                                   */
/*============================================================================*/
TEST(MagneticEncoderTests, InitCallsFunctions)
{
    init_magnetic_encoders_with_cpputest_checks();
}

TEST(MagneticEncoderTests, InitSetsExternalCallbacks)
{
    init_magnetic_encoders_with_cpputest_checks();
    CHECK(mock_external_callback_set_flags[EXTERNAL_CALLBACK_1_INDEX]);
    CHECK(mock_external_callback_set_flags[EXTERNAL_CALLBACK_2_INDEX]);
}

TEST(MagneticEncoderTests, InitResetsTicks)
{
    init_magnetic_encoders_with_cpputest_checks();
    encoder_1_isr();
    encoder_2_isr();
    init_magnetic_encoders_with_cpputest_checks();
    LONGS_EQUAL(0, get_encoder_1_ticks());
    LONGS_EQUAL(0, get_encoder_2_ticks());
}

TEST(MagneticEncoderTests, DeinitResetsTicks)
{
    init_magnetic_encoders_with_cpputest_checks();
    encoder_1_isr();
    encoder_2_isr();
    deinit_magnetic_encoders();
    LONGS_EQUAL(0, get_encoder_1_ticks());
    LONGS_EQUAL(0, get_encoder_2_ticks());
}

TEST(MagneticEncoderTests, IsrsChangesTicks)
{
    init_magnetic_encoders_with_cpputest_checks();
    encoder_1_isr();
    encoder_2_isr();
    CHECK(get_encoder_1_ticks() != 0);
    CHECK(get_encoder_2_ticks() != 0);
}

TEST(MagneticEncoderTests, ClearEncoderTicksClearsTicks)
{
    init_magnetic_encoders_with_cpputest_checks();
    encoder_1_isr();
    encoder_2_isr();
    clear_1_encoder_ticks();
    clear_2_encoder_ticks();
    LONGS_EQUAL(0, get_encoder_1_ticks());
    LONGS_EQUAL(0, get_encoder_2_ticks());
}

TEST(MagneticEncoderTests, Encoder1IsrChangesTicks)
{
    init_magnetic_encoders_with_cpputest_checks();
    set_mock_input(ENCODER_1_INDEX, 1);
    encoder_1_isr();
    LONGS_EQUAL(-1, get_encoder_1_ticks());
    clear_1_encoder_ticks();
    set_mock_input(ENCODER_1_INDEX, 0);
    encoder_1_isr();
    LONGS_EQUAL(1, get_encoder_1_ticks());
}

TEST(MagneticEncoderTests, Encoder2IsrChangesTicks)
{
    init_magnetic_encoders_with_cpputest_checks();
    set_mock_input(ENCODER_2_INDEX, 1);
    encoder_2_isr();
    LONGS_EQUAL(1, get_encoder_2_ticks());
    clear_2_encoder_ticks();
    set_mock_input(ENCODER_2_INDEX, 0);
    encoder_2_isr();
    LONGS_EQUAL(-1, get_encoder_2_ticks());
}
