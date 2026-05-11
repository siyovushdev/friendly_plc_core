#include "friendly_plc/plc_port.h"

#include <string.h>
#include <time.h>

#define LINUX_DI_COUNT       16
#define LINUX_DO_COUNT       16
#define LINUX_AI_COUNT       8
#define LINUX_AO_COUNT       8
#define LINUX_HSC_COUNT      4
#define LINUX_ENCODER_COUNT  4

static bool    s_di[LINUX_DI_COUNT];
static bool    s_do[LINUX_DO_COUNT];
static int32_t s_ai_mv[LINUX_AI_COUNT];
static float   s_ao_percent[LINUX_AO_COUNT];

static int32_t s_hsc[LINUX_HSC_COUNT];
static int32_t s_encoder[LINUX_ENCODER_COUNT];

PlcPortHwInfo plc_port_get_hw_info(void)
{
    PlcPortHwInfo info = {
            .di_count = LINUX_DI_COUNT,
            .do_count = LINUX_DO_COUNT,
            .ai_count = LINUX_AI_COUNT,
            .ao_count = LINUX_AO_COUNT,
            .hsc_count = LINUX_HSC_COUNT,
            .encoder_count = LINUX_ENCODER_COUNT
    };

    return info;
}

bool plc_port_read_di(uint16_t ch)
{
    if (ch >= LINUX_DI_COUNT) {
        return false;
    }

    return s_di[ch];
}

void plc_port_write_do(uint16_t ch, bool value)
{
    if (ch >= LINUX_DO_COUNT) {
        return;
    }

    s_do[ch] = value;
}

int32_t plc_port_read_ai_mv(uint16_t ch)
{
    if (ch >= LINUX_AI_COUNT) {
        return 0;
    }

    return s_ai_mv[ch];
}

void plc_port_write_ao_percent(uint16_t ch, float percent)
{
    if (ch >= LINUX_AO_COUNT) {
        return;
    }

    if (percent < 0.0f) {
        percent = 0.0f;
    }

    if (percent > 100.0f) {
        percent = 100.0f;
    }

    s_ao_percent[ch] = percent;
}

int32_t plc_port_read_hsc(uint16_t ch)
{
    if (ch >= LINUX_HSC_COUNT) return 0;
    return s_hsc[ch];
}

int32_t plc_port_read_encoder(uint16_t ch)
{
    if (ch >= LINUX_ENCODER_COUNT) return 0;
    return s_encoder[ch];
}

#ifdef FRIENDLY_PLC_ENABLE_TEST_API

void plc_port_test_set_hsc(uint16_t ch, int32_t value)
{
    if (ch >= LINUX_HSC_COUNT) return;
    s_hsc[ch] = value;
}

void plc_port_test_set_encoder(uint16_t ch, int32_t value)
{
    if (ch >= LINUX_ENCODER_COUNT) return;
    s_encoder[ch] = value;
}

#endif

uint32_t plc_port_now_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    return (uint32_t)((ts.tv_sec * 1000u) + (ts.tv_nsec / 1000000u));
}

void plc_port_feed_watchdog(void)
{
}

void plc_port_reset_outputs(void)
{
    memset(s_do, 0, sizeof(s_do));
    memset(s_ao_percent, 0, sizeof(s_ao_percent));
}

#ifdef FRIENDLY_PLC_ENABLE_TEST_API

bool plc_port_test_get_do(uint16_t ch)
{
    if (ch >= LINUX_DO_COUNT) return false;
    return s_do[ch];
}

void plc_port_test_set_di(uint16_t ch, bool value)
{
    if (ch >= LINUX_DI_COUNT) return;
    s_di[ch] = value;
}

void plc_port_test_set_ai_mv(uint16_t ch, int32_t value)
{
    if (ch >= LINUX_AI_COUNT) return;
    s_ai_mv[ch] = value;
}

float plc_port_test_get_ao_percent(uint16_t ch)
{
    if (ch >= LINUX_AO_COUNT) return 0.0f;
    return s_ao_percent[ch];
}

#endif