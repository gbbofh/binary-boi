/**
 * @file        cpu.h
 * @author      Garrett Bates <gbates@cs.nmt.edu>
 * @brief       provides the public interface for a simulated 8-bit processor
 * @bugs        none known
 */

#ifndef CPU_H
#define CPU_H

/**
 * 16-bit instructions
 * 4 8-bit registers
 * 2 16-bit registers for addressing (can be set to 4 extra 8-bit registers)
 */

/**
 * Instruction Specification
 *
 * Reg/reg Arithmetic/Logical Operations:
 * | 00ii | irrr | RRxx | xxxx |
 *
 * Imm/reg Arithmetic/Logical Operations:
 * | 01ii | irrr | IIII | IIII |
 * 
 * Mem/reg  Operations:
 * | 10ii | 1rrr | IIII | IIII |
 *
 * Branch Operations:
 * | 11ii | irrr | RRxx | xxxx |
 */

/**
 * Defined instructions:
 *
 * Reg/reg Arithmetic/Logical Operations
 * | ADD | | 0000 | 0rrr | RRRx | xxxx | | r <- r + R
 * | SUB | | 0000 | 1rrr | RRRx | xxxx | | r <- r - R
 * | XOR | | 0001 | 0rrr | RRRx | xxxx | | r <- r ^ R
 * | AND | | 0001 | 1rrr | RRRx | xxxx | | r <- r & R
 * | OR  | | 0010 | 0rrr | RRRx | xxxx | | r <- r | R
 * | MUL | | 0010 | 1xxx | xxxx | xxxx | | r3/r4 <- [r0] * [r1]
 * | DIV | | 0011 | 0xxx | xxxx | xxxx | | r3/r4 <- [r0] / [r1]
 * | NOP | | 0011 | 1xxx | xxxx | xxxx | | No Operation
 *
 * Imm/reg Arithmetic/Logical Operations
 * | ADD | | 0100 | 0rrr | IIII | IIII | | r <- r + I
 * | SUB | | 0100 | 1rrr | IIII | IIII | | r <- r - I
 * | XOR | | 0101 | 0rrr | IIII | IIII | | r <- r ^ I
 * | AND | | 0101 | 1rrr | IIII | IIII | | r <- r & I
 * | OR  | | 0110 | 0rrr | IIII | IIII | | r <- r | I
 * | LSL | | 0110 | 1rrr | xxxx | xIII | | r <- r << I
 * | LSR | | 0111 | 0rrr | xxxx | xIII | | r <- r >> I
 * | NOP | | 0111 | 1xxx | xxxx | xxxx | | No Operation
 *
 * Memory Operations
 * | LDR | | 1000 | 0rrr | IIII | IIII | | r <- *[as + I]
 * | STR | | 1000 | 1rrr | IIII | IIII | | *[as + I] <- r
 * | PSH | | 1001 | 0rrr | SSxx | xxxx | | r <- *[as + I]
 * | POP | | 1001 | 1rrr | SSxx | xxxx | | *[as + I] <- r
 * | MOV | | 1010 | 0rrr | RRRx | xxxx | | r <- [R]
 * | MVS | | 1010 | 1rrr | Sxxx | xxxx | | r <- [STATUS/pc]
 *
 * Branch Operations
 * | JMP | | 1100 | 0rrr | RRRx | xxxx | | pc <- ar
 * | JLE | | 1100 | 1rrr | RRRx | xxxx | | pc <- ar if rrr <=  RRR
 * | JGE | | 1101 | 0rrr | RRRx | xxxx | | pc <- ar if rrr >=  RRR
 * | JEQ | | 1101 | 1rrr | RRRx | xxxx | | pc <- ar if rrr <=> RRR
 * | JLZ | | 1110 | 0rrr | xxxx | xxxx | | pc <- ar if rrr < 0
 * | JGZ | | 1110 | 1rrr | xxxx | xxxx | | pc <- ar if rrr > 0
 * | JRL | | 1111 | 0rrr | IIII | IIII | | pc <- pc + imm
 */

/**
 * Addresses for general purpose registers
 */
#define CPU_R0          (0x00)
#define CPU_R1          (0x01)
#define CPU_R2          (0x02)
#define CPU_R3          (0x03)
#define CPU_SAL         (0x04)
#define CPU_SAH         (0x05)
#define CPU_DAL         (0x06)
#define CPU_DAH         (0x07)

/**
 * Flags in the status register
 */
#define CPU_STZ (1 << 0)        /** Zero flag */
#define CPU_STN (1 << 1)        /** Negative flag */
#define CPU_STO (1 << 2)        /** Overflow flag */
#define CPU_STC (1 << 3)        /** Carry flag */
#define CPU_GR8 (1 << 4)        /** make SAL/SAH, DAL/DAH independent */

typedef struct cpu {
        char    r[8];   /** General purpose registers */
        char    st;     /** Status register */
        short   pc;     /** Program counter */
        short   ir;     /** Instruction register */
        short   sp;     /** Stack pointer */
        char*   mem;    /** Memory */
} cpu;

/**
 * @brief initialize a cpu structure
 *
 * Zeroes out a cpu structure, and allocates ~64K to serve as RAM
 *
 * @param cpu -- cpu structure to initialize
 */
void cpu_init(struct cpu* cpu);

/**
 * @brief free memory for a cpu structure
 *
 * Frees resources for a cpu structure and zeroes out the structure
 *
 * @param cpu -- cpu structure to deallocate resources from
 */
void cpu_term(struct cpu* cpu);

/**
 * @brief advance the cpu structure by one clock cycle
 *
 * Reads in the next opcode from memory, and advances the program counter by
 * two bytes. The opcode is decoded and used to select an appropriate
 * handler function based on the type of instruction that was encountered.
 * The handlers then pass off control to another handler that actually
 * implements the operation in question. Convoluted? Maybe. Does it work? Yes.
 *
 * @param cpu -- cpu structure to update
 */
void cpu_clock(struct cpu* cpu);

#endif

