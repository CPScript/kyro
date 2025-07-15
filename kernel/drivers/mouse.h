#ifndef MOUSE_H
#define MOUSE_H

#include <stdint.h>
#include <stdbool.h>

// Mouse I/O ports (shared with keyboard controller)
#define MOUSE_DATA_PORT       0x60
#define MOUSE_STATUS_PORT     0x64
#define MOUSE_COMMAND_PORT    0x64

// Mouse commands
#define MOUSE_CMD_ENABLE_REPORTING    0xF4
#define MOUSE_CMD_DISABLE_REPORTING   0xF5
#define MOUSE_CMD_SET_DEFAULTS        0xF6
#define MOUSE_CMD_RESEND              0xFE
#define MOUSE_CMD_RESET               0xFF
#define MOUSE_CMD_SET_SAMPLE_RATE     0xF3
#define MOUSE_CMD_GET_DEVICE_ID       0xF2
#define MOUSE_CMD_SET_REMOTE_MODE     0xF0
#define MOUSE_CMD_SET_WRAP_MODE       0xEE
#define MOUSE_CMD_RESET_WRAP_MODE     0xEC
#define MOUSE_CMD_READ_DATA           0xEB
#define MOUSE_CMD_SET_STREAM_MODE     0xEA
#define MOUSE_CMD_STATUS_REQUEST      0xE9
#define MOUSE_CMD_SET_RESOLUTION      0xE8

// Mouse controller commands
#define MOUSE_CTRL_ENABLE_AUX         0xA8
#define MOUSE_CTRL_DISABLE_AUX        0xA7
#define MOUSE_CTRL_TEST_AUX           0xA9
#define MOUSE_CTRL_WRITE_AUX          0xD4

// Mouse responses
#define MOUSE_ACKNOWLEDGE             0xFA
#define MOUSE_RESEND                  0xFE
#define MOUSE_ERROR                   0xFC

// Mouse packet flags (first byte)
#define MOUSE_FLAG_LEFT_BUTTON        0x01
#define MOUSE_FLAG_RIGHT_BUTTON       0x02
#define MOUSE_FLAG_MIDDLE_BUTTON      0x04
#define MOUSE_FLAG_ALWAYS_ONE         0x08
#define MOUSE_FLAG_X_SIGN             0x10
#define MOUSE_FLAG_Y_SIGN             0x20
#define MOUSE_FLAG_X_OVERFLOW         0x40
#define MOUSE_FLAG_Y_OVERFLOW         0x80

// Mouse packet structure
typedef struct {
    uint8_t flags;
    int16_t x_delta;
    int16_t y_delta;
    uint8_t scroll_delta;  // For scroll wheel mice
} mouse_packet_t;

// Mouse state structure
typedef struct {
    int32_t x;
    int32_t y;
    bool left_button;
    bool right_button;
    bool middle_button;
    bool enabled;
    uint8_t packet_buffer[4];
    int packet_index;
    int packet_size;
    bool packet_ready;
    uint8_t device_id;
    uint8_t sample_rate;
    uint8_t resolution;
} mouse_state_t;

// Mouse event types
typedef enum {
    MOUSE_EVENT_MOVE,
    MOUSE_EVENT_BUTTON_PRESS,
    MOUSE_EVENT_BUTTON_RELEASE,
    MOUSE_EVENT_SCROLL
} mouse_event_type_t;

// Mouse event structure
typedef struct {
    mouse_event_type_t type;
    int32_t x;
    int32_t y;
    uint8_t button;       // Which button for press/release events
    int8_t scroll_delta;  // For scroll events
} mouse_event_t;

// Mouse event callback function type
typedef void (*mouse_event_callback_t)(mouse_event_t *event);

// Function prototypes
void mouse_init(void);
void mouse_handler(void);
uint8_t mouse_read_data(void);
void mouse_write_data(uint8_t data);
uint8_t mouse_read_status(void);
void mouse_write_command(uint8_t command);
bool mouse_data_available(void);
void mouse_wait_input(void);
void mouse_wait_output(void);
void mouse_enable(void);
void mouse_disable(void);
bool mouse_send_command(uint8_t command);
bool mouse_send_command_with_data(uint8_t command, uint8_t data);
void mouse_set_sample_rate(uint8_t rate);
void mouse_set_resolution(uint8_t resolution);
void mouse_reset(void);
uint8_t mouse_get_device_id(void);
void mouse_process_packet(void);
void mouse_update_state(mouse_packet_t *packet);
void mouse_set_position(int32_t x, int32_t y);
void mouse_get_position(int32_t *x, int32_t *y);
bool mouse_get_button_state(uint8_t button);
void mouse_set_event_callback(mouse_event_callback_t callback);
void mouse_enable_scroll_wheel(void);
void mouse_enable_5_button_mode(void);

// Interrupt handler
void mouse_interrupt_handler(void);

// Global mouse state
extern mouse_state_t mouse_state;
extern mouse_event_callback_t mouse_event_callback;

// Mouse button constants
#define MOUSE_BUTTON_LEFT     1
#define MOUSE_BUTTON_RIGHT    2
#define MOUSE_BUTTON_MIDDLE   4
#define MOUSE_BUTTON_4        8
#define MOUSE_BUTTON_5        16

// Mouse resolution constants
#define MOUSE_RESOLUTION_1_MM  0
#define MOUSE_RESOLUTION_2_MM  1
#define MOUSE_RESOLUTION_4_MM  2
#define MOUSE_RESOLUTION_8_MM  3

// Mouse sample rates
#define MOUSE_SAMPLE_RATE_10   10
#define MOUSE_SAMPLE_RATE_20   20
#define MOUSE_SAMPLE_RATE_40   40
#define MOUSE_SAMPLE_RATE_60   60
#define MOUSE_SAMPLE_RATE_80   80
#define MOUSE_SAMPLE_RATE_100  100
#define MOUSE_SAMPLE_RATE_200  200

#endif // MOUSE_H
