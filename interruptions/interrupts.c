#include "interrupts.h"

static struct idtEntry descriptors[NUM_OF_SIGNALS];

void interrupt_handler(__attribute__((unused)) struct cpuState reg_state, __attribute__((unused)) struct stackState stack_state, unsigned int inr_code)
{

}