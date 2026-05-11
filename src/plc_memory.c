#include "friendly_plc/plc.h"

#include <string.h>


static bool    s_memBool[PLC_MEM_BOOL_COUNT];
static int32_t s_memInt[PLC_MEM_INT_COUNT];
static float   s_memReal[PLC_MEM_REAL_COUNT];

void plc_mem_set_bool(uint16_t index, bool value)
{
    if (index >= PLC_MEM_BOOL_COUNT) return;
    s_memBool[index] = value;
}

bool plc_mem_get_bool(uint16_t index)
{
    if (index >= PLC_MEM_BOOL_COUNT) return false;
    return s_memBool[index];
}

void plc_mem_set_int(uint16_t index, int32_t value)
{
    if (index >= PLC_MEM_INT_COUNT) return;
    s_memInt[index] = value;
}

int32_t plc_mem_get_int(uint16_t index)
{
    if (index >= PLC_MEM_INT_COUNT) return 0;
    return s_memInt[index];
}

void plc_mem_set_real(uint16_t index, float value)
{
    if (index >= PLC_MEM_REAL_COUNT) return;
    s_memReal[index] = value;
}

float plc_mem_get_real(uint16_t index)
{
    if (index >= PLC_MEM_REAL_COUNT) return 0.0f;
    return s_memReal[index];
}

void plc_mem_reset_all(void)
{
    memset(s_memBool, 0, sizeof(s_memBool));
    memset(s_memInt,  0, sizeof(s_memInt));
    memset(s_memReal, 0, sizeof(s_memReal));
}

void plc_mem_init(void)
{
    plc_mem_reset_all();
}