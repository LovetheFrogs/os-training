ENTRY(loader)                   /* name of the entry label */

SECTIONS {
    . = 0x001000000;            /* load the code at 1 MB (lower addrs used by GRUB) */

    .text ALIGN (0x1000) :      /* align at 4 KB */
    {
        *(.text)                /* all text sections from all files */
    }

    .rodata ALIGN (0x1000) :    /* align at 4 KB */
    {
        *(.rodata)              /* all read-only sections from all files */
    }

    .data ALIGN (0x1000) :      /* align at 4 KB */
    {
        *(.data)                /* all data sections from all files */
    }

    .bss ALIGN (0x1000) :       /* align at 4 KB */
    {
        *(COMMON)               /* all COMMON sections from all files */
        *(.bss)                 /* all bss sections from all files */
    }
}