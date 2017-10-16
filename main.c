#include <stdio.h>

#include "cpu.h"

int main(int argc, char* argv[])
{
        struct cpu cpu;

        cpu_init(&cpu);

        *(short*)(cpu.mem + 0) = 0x0000;
        *(short*)(cpu.mem + 2) = 0x400F;
        *(short*)(cpu.mem + 4) = 0x8000;
        *(short*)(cpu.mem + 6) = 0xB000;
        *(short*)(cpu.mem + 8) = 0xC000;

        cpu_clock(&cpu);
        cpu_clock(&cpu);
        cpu_clock(&cpu);
        cpu_clock(&cpu);
        cpu_clock(&cpu);


        cpu_term(&cpu);
}

