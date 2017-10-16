#ifndef OPS_H
#define OPS_H

struct cpu;

#define CPU_REG_SRC     (0x00E0)
#define CPU_REG_DST     (0x0700)
#define CPU_IMM_VAL     (0x00FF)


/**
 * ARITHMETIC OPERATIONS
 */
void _cpu_rR_add(struct cpu* cpu);
void _cpu_rR_sub(struct cpu* cpu);
void _cpu_rR_xor(struct cpu* cpu);
void _cpu_rR_and(struct cpu* cpu);
void _cpu_rR_or(struct cpu* cpu);
void _cpu_rR_mul(struct cpu* cpu);
void _cpu_rR_div(struct cpu* cpu);
void _cpu_rR_nop(struct cpu* cpu);

void _cpu_rI_add(struct cpu* cpu);
void _cpu_rI_sub(struct cpu* cpu);
void _cpu_rI_xor(struct cpu* cpu);
void _cpu_rI_and(struct cpu* cpu);
void _cpu_rI_or(struct cpu* cpu);
void _cpu_rI_lsl(struct cpu* cpu);
void _cpu_rI_lsr(struct cpu* cpu);
void _cpu_rI_nop(struct cpu* cpu);

/**
 * MEMORY/REGISTER MEMORY OPERATIONS
 */
void _cpu_rI_ldr(struct cpu* cpu);
void _cpu_rI_str(struct cpu* cpu);
void _cpu_rR_psh(struct cpu* cpu);
void _cpu_rR_pop(struct cpu* cpu);
void _cpu_rR_mov(struct cpu* cpu);
void _cpu_rR_mvs(struct cpu* cpu);

/**
 * REGISTER/REGISTER MEMORY OPERATIONS
 */
void _cpu_rR_mov(struct cpu* cpu);

/**
 * BRANCH OPERATIONS
 */
void _cpu_rR_jmp(struct cpu* cpu);
void _cpu_rR_jle(struct cpu* cpu);
void _cpu_rR_jge(struct cpu* cpu);
void _cpu_rR_jeq(struct cpu* cpu);
void _cpu_rx_jlz(struct cpu* cpu);
void _cpu_rx_jgz(struct cpu* cpu);
void _cpu_rI_jrl(struct cpu* cpu);

#endif

