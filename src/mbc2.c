#include "../include/mbc.h"
#include "../include/mbc2.h"
#include "../include/debug.h"

void mbc2_allocate(VM* vm) {
    MBC_2* mbc = (MBC_2*)malloc(sizeof(MBC_2));
    mbc->ramEnabled = false;

    /* Built in RAM is left uninitialised */

    vm->memController = (void*)mbc;
    vm->memControllerType = MBC_TYPE_2;
}

void mbc2_free(VM* vm) {
    MBC_2* mbc = (MBC_2*)vm->memController;

    free(mbc);
    vm->memController = NULL;
}

void mbc2_interceptROMWrite(VM *vm, uint16_t addr, uint8_t byte) {
    MBC_2* mbc = (MBC_2*)vm->memController;

    if (addr >= 0x0000 && addr <= 0x3FFF) {
        /* If bit 8 of the address is clear, the value written is 
         * used to enable/disable ram 
         *
         * If bit 8 is set, it is used to do a bank switch 
         * The bank number is determined with the lower 4 bits
         * of the value written */

        if ((addr >> 8) & 0x1) {
            /* Bit 8 is set, do a bank switch */
            uint8_t bankNumber = byte & 0xF;
            
            /* We mask the bank number to fit any smaller rom sizes 
             *
             * Max MBC2 supports is 256KB ROM which can be addressed by 
             * the entire 4 bits */

            switch (vm->cartridge->romSize) {
                case ROM_32KB:  log_warning(vm, "Why're u bank switching with a 32KB ROM"); return;
                case ROM_64KB:  bankNumber &= 0b00000011; break;
                case ROM_128KB: bankNumber &= 0b00000111; break;
                case ROM_256KB: break;                  /* No masking needed */
                default: log_warning(vm, "ROM is too big for MBC2, it can only be partially mapped");
                         break; 
            }
            
            /* BankNumber 0 gets translated to 1 */
            if (bankNumber == 0) bankNumber = 1;

            switchROMBank(vm, bankNumber);
        } else {
            /* Enable/Disable RAM 
             *
             * 0x0A = Enable
             * Anything Else = Disable */

            mbc->ramEnabled = byte == 0x0A;

#ifdef DEBUG_LOGGING
            printf("MBC : RAM %s\n", mbc->ramEnabled ? "Enabled" : "Disabled");
#endif
        }
    } else {
        log_fatal(vm, "MBC : Attempt to write to an undefined MBC Register");
        return;
    }
}

void mbc2_writeBuiltInRAM(VM *vm, uint16_t addr, uint8_t byte) {
    MBC_2* mbc = (MBC_2*)vm->memController;
    if (!mbc->ramEnabled) log_warning(vm, "It is recommended to enable RAM when writing");

    /* Only the bottom 9 bits are used to address the memory, the upper bits 
     * dont matter and are thus 'echoed', for our purpose we just mask it */

    addr &= 0b0000000111111111;
    
    /* In this RAM only the lower 4 bits are supposed to be stored/retrieved
     * but we can just dump the whole byte too since upper bits are undefined 
     * anyway */
    mbc->builtInRAM[addr] = byte;
}

uint8_t mbc2_readBuiltInRAM(VM* vm, uint16_t addr) {
    MBC_2* mbc = (MBC_2*)vm->memController;
    if (!mbc->ramEnabled) log_warning(vm, "It is recommended to enable RAM when reading");
    
    /* Just like writing to ram, we make up for echoing memory by masking 
     * the bits */

    addr &= 0b0000000111111111;

    return mbc->builtInRAM[addr];
}
