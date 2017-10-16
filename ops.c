#include "cpu.h"
#include "ops.h"

void _cpu_rR_add(struct cpu* cpu)
{
        int sum;
        int src;
        int dest;

        src = cpu->ir & CPU_REG_SRC;
        dest = cpu->ir & CPU_REG_DST;

        cpu->r[dest] += cpu->r[src];
}

void _cpu_rR_sub(struct cpu* cpu)
{
        int src;
        int dest;

        src = cpu->ir & CPU_REG_SRC;
        dest = cpu->ir & CPU_REG_DST;

        cpu->r[dest] -= cpu->r[src];
}

void _cpu_rR_xor(struct cpu* cpu)
{
        int src;
        int dest;

        src = cpu->ir & CPU_REG_SRC;
        dest = cpu->ir & CPU_REG_DST;

        cpu->r[dest] ^= cpu->r[src];
}

void _cpu_rR_and(struct cpu* cpu)
{
        int src;
        int dest;

        src = cpu->ir & CPU_REG_SRC;
        dest = cpu->ir & CPU_REG_DST;

        cpu->r[dest] &= cpu->r[src];
}

void _cpu_rR_or(struct cpu* cpu)
{
        int src;
        int dest;

        src = cpu->ir & CPU_REG_SRC;
        dest = cpu->ir & CPU_REG_DST;

        cpu->r[dest] |= cpu->r[src];
}

void _cpu_rR_mul(struct cpu* cpu)
{
        short res;
        char  lhv;
        char  rhv;

        rhv = cpu->r[0];
        lhv = cpu->r[1];
        res = lhv * rhv;
        cpu->r[2] = (char)(res & 0xFF);
        cpu->r[3] = (char)((res >> 7) & 0xFF);
}

void _cpu_rR_div(struct cpu* cpu)
{
        short res;
        char  lhv;
        char  rhv;

        rhv = cpu->r[0];
        lhv = cpu->r[1];
        if(rhv != 0) {
                res = lhv / rhv;
        }
        cpu->r[2] = (char)(res & 0xFF);
        cpu->r[3] = (char)((res >> 7) & 0xFF);
}

void _cpu_rR_nop(struct cpu* cpu)
{
        cpu->r[0] = cpu->r[0];
}

void _cpu_rI_add(struct cpu* cpu)
{
        int imm;
        int dest;

        imm = cpu->ir & CPU_IMM_VAL;
        dest = cpu->ir & CPU_REG_DST;

        cpu->r[dest] += imm;
}

void _cpu_rI_sub(struct cpu* cpu)
{
        int imm;
        int dest;

        imm = cpu->ir & CPU_IMM_VAL;
        dest = cpu->ir & CPU_REG_DST;

        cpu->r[dest] -= imm;
}

void _cpu_rI_xor(struct cpu* cpu)
{
        int imm;
        int dest;

        imm = cpu->ir & CPU_IMM_VAL;
        dest = cpu->ir & CPU_REG_DST;

        cpu->r[dest] ^= imm;
}

void _cpu_rI_and(struct cpu* cpu)
{
        int imm;
        int dest;

        imm = cpu->ir & CPU_IMM_VAL;
        dest = cpu->ir & CPU_REG_DST;

        cpu->r[dest] &= imm;
}

void _cpu_rI_or(struct cpu* cpu)
{
        int imm;
        int dest;

        imm = cpu->ir & CPU_IMM_VAL;
        dest = cpu->ir & CPU_REG_DST;

        cpu->r[dest] |= imm;
}

void _cpu_rI_lsl(struct cpu* cpu)
{
        int imm;
        int dest;
        unsigned char rv;

        imm = cpu->ir & CPU_IMM_VAL;
        dest = cpu->ir & CPU_REG_DST;

        rv = cpu->r[dest];
        rv <<= imm;
        cpu->r[dest] = rv;
}

void _cpu_rI_lsr(struct cpu* cpu)
{
        int imm;
        int dest;
        unsigned char rv;

        imm = cpu->ir & CPU_IMM_VAL;
        dest = cpu->ir & CPU_REG_DST;

        rv = cpu->r[dest];
        rv >>= imm;
        cpu->r[dest] = rv;
}

void _cpu_rI_nop(struct cpu* cpu)
{
        cpu->r[0] = cpu->r[0];
}

void _cpu_rI_ldr(struct cpu* cpu)
{
        int src;
        int imm;
        int off;

        src = cpu->ir & CPU_REG_SRC;
        imm = cpu->ir & CPU_IMM_VAL;

        off = cpu->r[CPU_DAL] | cpu->r[CPU_DAH] << 7;
        off += imm;
        if(off > (1 << sizeof(short))) {
                off = (1 << sizeof(short)) % off;
        }
        cpu->r[src] = cpu->mem[off];
}

void _cpu_rI_str(struct cpu* cpu)
{
        int imm;
        int off;
        int dest;

        imm = cpu->ir & CPU_IMM_VAL;
        dest = cpu->ir & CPU_REG_SRC;

        off = cpu->r[CPU_DAL] | cpu->r[CPU_DAH] << 7;
        off += imm;
        if(off > (1 << sizeof(short))) {
                off = (1 << sizeof(short)) % off;
        }
        cpu->mem[off] = cpu->r[dest];
}

/**
 * TODO: check for special register access, get src val from register in
 * question.
 */
void _cpu_rR_psh(struct cpu* cpu)
{
        int src;
        char src_val;

        src = cpu->ir & CPU_REG_SRC;

        cpu->mem[cpu->sp] = src_val;
}

/**
 * TODO: check for special register access, set reg val accordingly.
 */
void _cpu_rR_pop(struct cpu* cpu)
{
}

void _cpu_rR_mov(struct cpu* cpu)
{
        /*int src;
        int dest;

        src = cpu->ir & CPU_REG_SRC;
        dest = cpu->ir & CPU_REG_DST;

        cpu->r[dest] = cpu->r[src];*/
}

void _cpu_rR_mvs(struct cpu* cpu)
{
}

void _cpu_rR_jmp(struct cpu* cpu)
{
        char imm;
        imm = cpu->ir & CPU_IMM_VAL;
        cpu->pc = (short)imm - 2;
}

void _cpu_rR_jle(struct cpu* cpu)
{
}

void _cpu_rR_jge(struct cpu* cpu)
{
}

void _cpu_rR_jeq(struct cpu* cpu)
{
}

void _cpu_rx_jlz(struct cpu* cpu)
{
}

void _cpu_rx_jgz(struct cpu* cpu)
{
}

void _cpu_rI_jrl(struct cpu* cpu)
{
        char imm;

        imm = cpu->ir & CPU_IMM_VAL;
        cpu->pc = cpu->pc + imm - 2;
}

