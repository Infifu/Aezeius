#include "kernel/gdt.h"

extern void gdt_flush(struct gdt_ptr_struct* gp);

struct gdt_entry_struct gdt_entries[5];
struct gdt_ptr_struct gdt_ptr;

void initGdt()
{
    gdt_ptr.limit = (sizeof(struct gdt_entry_struct) * 5) - 1;
    gdt_ptr.base = (uint32_t)&gdt_entries;

    //9A = 1001 1010 (access bytes)
    // 1 - for valid segment, 0 0 - DPL higest privilege // 1 - code segment
    // 1 - Executable (code segment) 0 - Direction to let memory grow up, 1 - Read access, 0 - Accesed bit
    //second char 2 for data segment, first char F for user segment

    setGdtGate(0,0,0,0,0); //Null descriptor
    setGdtGate(1,0,0xFFFFFFFF,0x9A,0xCF); //kernel code segment
    setGdtGate(2,0,0xFFFFFFFF,0x92,0xCF); //kernel data segment
    setGdtGate(3,0,0xFFFFFFFF,0xFA,0xCF); //User code segment
    setGdtGate(4,0,0xFFFFFFFF,0xF2,0xCF); //User data segment

    gdt_flush(&gdt_ptr);
}

void setGdtGate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access,uint8_t gran)
{
    gdt_entries[num].base_low = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high = (base>>24) & 0xFF;

    gdt_entries[num].limit = (limit & 0xFFFF);
    gdt_entries[num].flags = (limit >> 16 ) & 0x0F;
    gdt_entries[num].flags |= (gran & 0xF0);

    gdt_entries[num].access = access;
}
