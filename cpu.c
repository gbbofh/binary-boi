#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "ops.h"

typedef void (*cpu_handler)(struct cpu* cpu);

void _cpu_handle_rR_arith(struct cpu* cpu);
void _cpu_handle_rI_arith(struct cpu* cpu);
void _cpu_handle_rI_mem(struct cpu* cpu);
void _cpu_handle_rR_branch(struct cpu* cpu);
 
void cpu_init(struct cpu* cpu)
{
        memset(cpu, 0, sizeof(struct cpu));
        cpu->mem = calloc((1 << sizeof(short)) - 1, 1);

        /* Pre-fetch first instruction from memory */
        cpu->sp = 0xFFFF;
        cpu->ir = *(short*)(cpu->mem + cpu->pc);
        cpu->pc += 2;
}

void cpu_term(struct cpu* cpu)
{
        free(cpu->mem);
        memset(cpu, 0, sizeof(struct cpu));
}

void cpu_clock(struct cpu* cpu)
{
        int op_class;

        cpu_handler handler;
        cpu_handler handlers[] = {
                _cpu_handle_rR_arith,
                _cpu_handle_rI_arith,
                _cpu_handle_rI_mem,
                _cpu_handle_rR_branch
        };

        op_class = (cpu->ir >> 14) & 0x03;

        handler = handlers[op_class];
        handler(cpu);

        cpu->ir = *(short*)(cpu->mem + cpu->pc);
        cpu->pc += 2;
}

void _cpu_handle_rR_arith(struct cpu* cpu)
{
        int op_class;
        cpu_handler handler;

        cpu_handler handlers[] = {
                _cpu_rR_add,
                _cpu_rR_sub,
                _cpu_rR_xor,
                _cpu_rR_and,
                _cpu_rR_or,
                _cpu_rR_mul,
                _cpu_rR_div,
                _cpu_rR_nop
        };

        op_class = (cpu->ir >> 0x0B) & 0x03;
        handler = handlers[op_class];
        handler(cpu);
}

void _cpu_handle_rI_arith(struct cpu* cpu)
{
        int op_class;
        cpu_handler handler;

        cpu_handler handlers[] = {
                _cpu_rI_add,
                _cpu_rI_sub,
                _cpu_rI_xor,
                _cpu_rI_and,
                _cpu_rI_or,
                _cpu_rI_lsl,
                _cpu_rI_lsr,
                _cpu_rI_nop
        };

        op_class = (cpu->ir >> 0x0B) & 0x03;
        handler = handlers[op_class];
        handler(cpu);
}

void _cpu_handle_rI_mem(struct cpu* cpu)
{
        int op_class;
        cpu_handler handler;

        cpu_handler handlers[] = {
                _cpu_rI_ldr,
                _cpu_rI_str,
                _cpu_rR_psh,
                _cpu_rR_pop,
                _cpu_rR_mov,
                _cpu_rR_mvs
        };

        op_class = (cpu->ir >> 0x0C) & 0x03;
        handler = handlers[op_class];
        handler(cpu);
}

void _cpu_handle_rR_branch(struct cpu* cpu)
{
        int op_class;
        cpu_handler handler;

        cpu_handler handlers[] = {
                _cpu_rR_jmp,
                _cpu_rR_jle,
                _cpu_rR_jge,
                _cpu_rR_jeq,
                _cpu_rx_jlz,
                _cpu_rx_jgz,
                _cpu_rI_jrl
        };

        op_class = (cpu->ir >> 0x0B) & 0x03;
        handler = handlers[op_class];
        handler(cpu);
}

