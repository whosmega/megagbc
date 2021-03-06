#include <stdio.h>
#include "../include/debug.h"

void log_fatal(VM* vm, const char* string) {
    printf("[FATAL]");
    printf(" %s", string);
    printf("\n");

    stopEmulator(vm);
    exit(99);
}

void log_warning(VM* vm, const char* string) {
    printf("[WARNING]");
    printf(" %s", string);
    printf("\n");
}

static uint16_t read2Bytes(VM* vm) {
    uint8_t b1 = vm->MEM[vm->PC + 1];
    uint8_t b2 = vm->MEM[vm->PC + 2];
    uint16_t D16 = (b2 << 8) | b1;
    return D16;
}

static void printFlags(VM* vm) {
    uint8_t flagState = vm->GPR[R8_F];
    
    printf("[Z%d", flagState >> 7);
    printf(" N%d", (flagState >> 6) & 1);
    printf(" H%d", (flagState >> 5) & 1);
    printf(" C%d]", (flagState >> 4) & 1);
}

static void simpleInstruction(VM* vm, char* ins) {
    printf("%s\n", ins);;
}

static void d16(VM* vm, char* ins) {
    printf("%s (0x%04x)\n", ins, read2Bytes(vm));
}

static void d8(VM* vm, char* ins) {
    printf("%s (0x%02x)\n", ins, vm->MEM[vm->PC + 1]);
}

static void a16(VM* vm, char* ins) {
    printf("%s (0x%04x)\n", ins, read2Bytes(vm));
}

static void r8(VM* vm, char* ins) {
    printf("%s (%d)\n", ins, (int8_t)vm->MEM[vm->PC + 1]);
}

void printCBInstruction(VM* vm, uint8_t byte) {
#ifdef DEBUG_PRINT_ADDRESS
    printf("[0x%04x]", vm->PC - 1);
#endif
#ifdef DEBUG_PRINT_FLAGS
    printFlags(vm);
#endif
#ifdef DEBUG_PRINT_CYCLES
    printf("[%ld]", vm->clock);
#endif
#ifdef DEBUG_PRINT_JOYPAD_REG
    printf("[sel:%x|", (vm->MEM[R_P1_JOYP] >> 4) & 0x3);
    printf("sig:%x]", (vm->MEM[R_P1_JOYP] & 0b00001111));
#endif
#ifdef DEBUG_PRINT_TIMERS
	printf("[%x|%x|%x|%x]", vm->MEM[R_DIV], vm->MEM[R_TIMA], vm->MEM[R_TMA], vm->MEM[R_TAC]);
#endif
    printf(" %5s", "");

    switch (byte) {
        case 0x00: return simpleInstruction(vm, "RLC B");
        case 0x01: return simpleInstruction(vm, "RLC C");
        case 0x02: return simpleInstruction(vm, "RLC D");
        case 0x03: return simpleInstruction(vm, "RLC E");
        case 0x04: return simpleInstruction(vm, "RLC H");
        case 0x05: return simpleInstruction(vm, "RLC L");
        case 0x06: return simpleInstruction(vm, "RLC (HL)");
        case 0x07: return simpleInstruction(vm, "RLC A");
        case 0x08: return simpleInstruction(vm, "RRC B");
        case 0x09: return simpleInstruction(vm, "RRC C");
        case 0x0A: return simpleInstruction(vm, "RRC D");
        case 0x0B: return simpleInstruction(vm, "RRC E");
        case 0x0C: return simpleInstruction(vm, "RRC H");
        case 0x0D: return simpleInstruction(vm, "RRC L");
        case 0x0E: return simpleInstruction(vm, "RRC (HL)");
        case 0x0F: return simpleInstruction(vm, "RRC A");
        case 0x10: return simpleInstruction(vm, "RL B");
        case 0x11: return simpleInstruction(vm, "RL C");
        case 0x12: return simpleInstruction(vm, "RL D");
        case 0x13: return simpleInstruction(vm, "RL E");
        case 0x14: return simpleInstruction(vm, "RL H");
        case 0x15: return simpleInstruction(vm, "RL L");
        case 0x16: return simpleInstruction(vm, "RL (HL)");
        case 0x17: return simpleInstruction(vm, "RL A");
        case 0x18: return simpleInstruction(vm, "RR B");
        case 0x19: return simpleInstruction(vm, "RR C");
        case 0x1A: return simpleInstruction(vm, "RR D");
        case 0x1B: return simpleInstruction(vm, "RR E");
        case 0x1C: return simpleInstruction(vm, "RR H");
        case 0x1D: return simpleInstruction(vm, "RR L");
        case 0x1E: return simpleInstruction(vm, "RR (HL)");
        case 0x1F: return simpleInstruction(vm, "RR A");
        case 0x20: return simpleInstruction(vm, "SLA B");
        case 0x21: return simpleInstruction(vm, "SLA C");
        case 0x22: return simpleInstruction(vm, "SLA D");
        case 0x23: return simpleInstruction(vm, "SLA E");
        case 0x24: return simpleInstruction(vm, "SLA H");
        case 0x25: return simpleInstruction(vm, "SLA L");
        case 0x26: return simpleInstruction(vm, "SLA (HL)");
        case 0x27: return simpleInstruction(vm, "SLA A");
        case 0x28: return simpleInstruction(vm, "SRA B");
        case 0x29: return simpleInstruction(vm, "SRA C");
        case 0x2A: return simpleInstruction(vm, "SRA D");
        case 0x2B: return simpleInstruction(vm, "SRA E");
        case 0x2C: return simpleInstruction(vm, "SRA H");
        case 0x2D: return simpleInstruction(vm, "SRA L");
        case 0x2E: return simpleInstruction(vm, "SRA (HL)");
        case 0x2F: return simpleInstruction(vm, "SRA A");
        case 0x30: return simpleInstruction(vm, "SWAP B");
        case 0x31: return simpleInstruction(vm, "SWAP C");
        case 0x32: return simpleInstruction(vm, "SWAP D");
        case 0x33: return simpleInstruction(vm, "SWAP E");
        case 0x34: return simpleInstruction(vm, "SWAP H");
        case 0x35: return simpleInstruction(vm, "SWAP L");
        case 0x36: return simpleInstruction(vm, "SWAP (HL)");
        case 0x37: return simpleInstruction(vm, "SWAP A");
        case 0x38: return simpleInstruction(vm, "SRL B");
        case 0x39: return simpleInstruction(vm, "SRL C");
        case 0x3A: return simpleInstruction(vm, "SRL D");
        case 0x3B: return simpleInstruction(vm, "SRL E");
        case 0x3C: return simpleInstruction(vm, "SRL H");
        case 0x3D: return simpleInstruction(vm, "SRL L");
        case 0x3E: return simpleInstruction(vm, "SRL (HL)");
        case 0x3F: return simpleInstruction(vm, "SRL A");
        case 0x40: return simpleInstruction(vm, "BIT 0, B");
        case 0x41: return simpleInstruction(vm, "BIT 0, C");
        case 0x42: return simpleInstruction(vm, "BIT 0, D");
        case 0x43: return simpleInstruction(vm, "BIT 0, E");
        case 0x44: return simpleInstruction(vm, "BIT 0, H");
        case 0x45: return simpleInstruction(vm, "BIT 0, L");
        case 0x46: return simpleInstruction(vm, "BIT 0, (HL)");
        case 0x47: return simpleInstruction(vm, "BIT 0, A");
        case 0x48: return simpleInstruction(vm, "BIT 1, B");
        case 0x49: return simpleInstruction(vm, "BIT 1, C");
        case 0x4A: return simpleInstruction(vm, "BIT 1, D");
        case 0x4B: return simpleInstruction(vm, "BIT 1, E");
        case 0x4C: return simpleInstruction(vm, "BIT 1, H");
        case 0x4D: return simpleInstruction(vm, "BIT 1, L");
        case 0x4E: return simpleInstruction(vm, "BIT 1, (HL)");
        case 0x4F: return simpleInstruction(vm, "BIT 1, A");
        case 0x50: return simpleInstruction(vm, "BIT 2, B");
        case 0x51: return simpleInstruction(vm, "BIT 2, C");
        case 0x52: return simpleInstruction(vm, "BIT 2, D");
        case 0x53: return simpleInstruction(vm, "BIT 2, E");
        case 0x54: return simpleInstruction(vm, "BIT 2, H");
        case 0x55: return simpleInstruction(vm, "BIT 2, L");
        case 0x56: return simpleInstruction(vm, "BIT 2, (HL)");
        case 0x57: return simpleInstruction(vm, "BIT 2, A");
        case 0x58: return simpleInstruction(vm, "BIT 3, B");
        case 0x59: return simpleInstruction(vm, "BIT 3, C");
        case 0x5A: return simpleInstruction(vm, "BIT 3, D");
        case 0x5B: return simpleInstruction(vm, "BIT 3, E");
        case 0x5C: return simpleInstruction(vm, "BIT 3, H");
        case 0x5D: return simpleInstruction(vm, "BIT 3, L");
        case 0x5E: return simpleInstruction(vm, "BIT 3, (HL)");
        case 0x5F: return simpleInstruction(vm, "BIT 3, A");
        case 0x60: return simpleInstruction(vm, "BIT 4, B");
        case 0x61: return simpleInstruction(vm, "BIT 4, C");
        case 0x62: return simpleInstruction(vm, "BIT 4, D");
        case 0x63: return simpleInstruction(vm, "BIT 4, E");
        case 0x64: return simpleInstruction(vm, "BIT 4, H");
        case 0x65: return simpleInstruction(vm, "BIT 4, L");
        case 0x66: return simpleInstruction(vm, "BIT 4, (HL)");
        case 0x67: return simpleInstruction(vm, "BIT 4, A");
        case 0x68: return simpleInstruction(vm, "BIT 5, B");
        case 0x69: return simpleInstruction(vm, "BIT 5, C");
        case 0x6A: return simpleInstruction(vm, "BIT 5, D");
        case 0x6B: return simpleInstruction(vm, "BIT 5, E");
        case 0x6C: return simpleInstruction(vm, "BIT 5, H");
        case 0x6D: return simpleInstruction(vm, "BIT 5, L");
        case 0x6E: return simpleInstruction(vm, "BIT 5, (HL)");
        case 0x6F: return simpleInstruction(vm, "BIT 5, A");
        case 0x70: return simpleInstruction(vm, "BIT 6, B");
        case 0x71: return simpleInstruction(vm, "BIT 6, C");
        case 0x72: return simpleInstruction(vm, "BIT 6, D");
        case 0x73: return simpleInstruction(vm, "BIT 6, E");
        case 0x74: return simpleInstruction(vm, "BIT 6, H");
        case 0x75: return simpleInstruction(vm, "BIT 6, L");
        case 0x76: return simpleInstruction(vm, "BIT 6, (HL)");
        case 0x77: return simpleInstruction(vm, "BIT 6, A");
        case 0x78: return simpleInstruction(vm, "BIT 7, B");
        case 0x79: return simpleInstruction(vm, "BIT 7, C");
        case 0x7A: return simpleInstruction(vm, "BIT 7, D");
        case 0x7B: return simpleInstruction(vm, "BIT 7, E");
        case 0x7C: return simpleInstruction(vm, "BIT 7, H");
        case 0x7D: return simpleInstruction(vm, "BIT 7, L");
        case 0x7E: return simpleInstruction(vm, "BIT 7, (HL)");
        case 0x7F: return simpleInstruction(vm, "BIT 7, A");
        case 0x80: return simpleInstruction(vm, "RES 0, B");
        case 0x81: return simpleInstruction(vm, "RES 0, C");
        case 0x82: return simpleInstruction(vm, "RES 0, D");
        case 0x83: return simpleInstruction(vm, "RES 0, E");
        case 0x84: return simpleInstruction(vm, "RES 0, H");
        case 0x85: return simpleInstruction(vm, "RES 0, L");
        case 0x86: return simpleInstruction(vm, "RES 0, (HL)");
        case 0x87: return simpleInstruction(vm, "RES 0, A");
        case 0x88: return simpleInstruction(vm, "RES 1, B");
        case 0x89: return simpleInstruction(vm, "RES 1, C");
        case 0x8A: return simpleInstruction(vm, "RES 1, D");
        case 0x8B: return simpleInstruction(vm, "RES 1, E");
        case 0x8C: return simpleInstruction(vm, "RES 1, H");
        case 0x8D: return simpleInstruction(vm, "RES 1, L");
        case 0x8E: return simpleInstruction(vm, "RES 1, (HL)");
        case 0x8F: return simpleInstruction(vm, "RES 1, A");
        case 0x90: return simpleInstruction(vm, "RES 2, B");
        case 0x91: return simpleInstruction(vm, "RES 2, C");
        case 0x92: return simpleInstruction(vm, "RES 2, D");
        case 0x93: return simpleInstruction(vm, "RES 2, E");
        case 0x94: return simpleInstruction(vm, "RES 2, H");
        case 0x95: return simpleInstruction(vm, "RES 2, L");
        case 0x96: return simpleInstruction(vm, "RES 2, (HL)");
        case 0x97: return simpleInstruction(vm, "RES 2, A");
        case 0x98: return simpleInstruction(vm, "RES 3, B");
        case 0x99: return simpleInstruction(vm, "RES 3, C");
        case 0x9A: return simpleInstruction(vm, "RES 3, D");
        case 0x9B: return simpleInstruction(vm, "RES 3, E");
        case 0x9C: return simpleInstruction(vm, "RES 3, H");
        case 0x9D: return simpleInstruction(vm, "RES 3, L");
        case 0x9E: return simpleInstruction(vm, "RES 3, (HL)");
        case 0x9F: return simpleInstruction(vm, "RES 3, A");
        case 0xA0: return simpleInstruction(vm, "RES 4, B");
        case 0xA1: return simpleInstruction(vm, "RES 4, C");
        case 0xA2: return simpleInstruction(vm, "RES 4, D");
        case 0xA3: return simpleInstruction(vm, "RES 4, E");
        case 0xA4: return simpleInstruction(vm, "RES 4, H");
        case 0xA5: return simpleInstruction(vm, "RES 4, L");
        case 0xA6: return simpleInstruction(vm, "RES 4, (HL)");
        case 0xA7: return simpleInstruction(vm, "RES 4, A");
        case 0xA8: return simpleInstruction(vm, "RES 5, B");
        case 0xA9: return simpleInstruction(vm, "RES 5, C");
        case 0xAA: return simpleInstruction(vm, "RES 5, D");
        case 0xAB: return simpleInstruction(vm, "RES 5, E");
        case 0xAC: return simpleInstruction(vm, "RES 5, H");
        case 0xAD: return simpleInstruction(vm, "RES 5, L");
        case 0xAE: return simpleInstruction(vm, "RES 5, (HL)");
        case 0xAF: return simpleInstruction(vm, "RES 5, A");
        case 0xB0: return simpleInstruction(vm, "RES 6, B");
        case 0xB1: return simpleInstruction(vm, "RES 6, C");
        case 0xB2: return simpleInstruction(vm, "RES 6, D");
        case 0xB3: return simpleInstruction(vm, "RES 6, E");
        case 0xB4: return simpleInstruction(vm, "RES 6, H");
        case 0xB5: return simpleInstruction(vm, "RES 6, L");
        case 0xB6: return simpleInstruction(vm, "RES 6, (HL)");
        case 0xB7: return simpleInstruction(vm, "RES 6, A");
        case 0xB8: return simpleInstruction(vm, "RES 7, B");
        case 0xB9: return simpleInstruction(vm, "RES 7, C");
        case 0xBA: return simpleInstruction(vm, "RES 7, D");
        case 0xBB: return simpleInstruction(vm, "RES 7, E");
        case 0xBC: return simpleInstruction(vm, "RES 7, H");
        case 0xBD: return simpleInstruction(vm, "RES 7, L");
        case 0xBE: return simpleInstruction(vm, "RES 7, (HL)");
        case 0xBF: return simpleInstruction(vm, "RES 7, A");
        case 0xC0: return simpleInstruction(vm, "SET 0, B");
        case 0xC1: return simpleInstruction(vm, "SET 0, C");
        case 0xC2: return simpleInstruction(vm, "SET 0, D");
        case 0xC3: return simpleInstruction(vm, "SET 0, E");
        case 0xC4: return simpleInstruction(vm, "SET 0, H");
        case 0xC5: return simpleInstruction(vm, "SET 0, L");
        case 0xC6: return simpleInstruction(vm, "SET 0, (HL)");
        case 0xC7: return simpleInstruction(vm, "SET 0, A");
        case 0xC8: return simpleInstruction(vm, "SET 1, B");
        case 0xC9: return simpleInstruction(vm, "SET 1, C");
        case 0xCA: return simpleInstruction(vm, "SET 1, D");
        case 0xCB: return simpleInstruction(vm, "SET 1, E");
        case 0xCC: return simpleInstruction(vm, "SET 1, H");
        case 0xCD: return simpleInstruction(vm, "SET 1, L");
        case 0xCE: return simpleInstruction(vm, "SET 1, (HL)");
        case 0xCF: return simpleInstruction(vm, "SET 1, A");
        case 0xD0: return simpleInstruction(vm, "SET 2, B");
        case 0xD1: return simpleInstruction(vm, "SET 2, C");
        case 0xD2: return simpleInstruction(vm, "SET 2, D");
        case 0xD3: return simpleInstruction(vm, "SET 2, E");
        case 0xD4: return simpleInstruction(vm, "SET 2, H");
        case 0xD5: return simpleInstruction(vm, "SET 2, L");
        case 0xD6: return simpleInstruction(vm, "SET 2, (HL)");
        case 0xD7: return simpleInstruction(vm, "SET 2, A");
        case 0xD8: return simpleInstruction(vm, "SET 3, B");
        case 0xD9: return simpleInstruction(vm, "SET 3, C");
        case 0xDA: return simpleInstruction(vm, "SET 3, D");
        case 0xDB: return simpleInstruction(vm, "SET 3, E");
        case 0xDC: return simpleInstruction(vm, "SET 3, H");
        case 0xDD: return simpleInstruction(vm, "SET 3, L");
        case 0xDE: return simpleInstruction(vm, "SET 3, (HL)");
        case 0xDF: return simpleInstruction(vm, "SET 3, A");
        case 0xE0: return simpleInstruction(vm, "SET 4, B");
        case 0xE1: return simpleInstruction(vm, "SET 4, C");
        case 0xE2: return simpleInstruction(vm, "SET 4, D");
        case 0xE3: return simpleInstruction(vm, "SET 4, E");
        case 0xE4: return simpleInstruction(vm, "SET 4, H");
        case 0xE5: return simpleInstruction(vm, "SET 4, L");
        case 0xE6: return simpleInstruction(vm, "SET 4, (HL)");
        case 0xE7: return simpleInstruction(vm, "SET 4, A");
        case 0xE8: return simpleInstruction(vm, "SET 5, B");
        case 0xE9: return simpleInstruction(vm, "SET 5, C");
        case 0xEA: return simpleInstruction(vm, "SET 5, D");
        case 0xEB: return simpleInstruction(vm, "SET 5, E");
        case 0xEC: return simpleInstruction(vm, "SET 5, H");
        case 0xED: return simpleInstruction(vm, "SET 5, L");
        case 0xEE: return simpleInstruction(vm, "SET 5, (HL)");
        case 0xEF: return simpleInstruction(vm, "SET 5, A");
        case 0xF0: return simpleInstruction(vm, "SET 6, B");
        case 0xF1: return simpleInstruction(vm, "SET 6, C");
        case 0xF2: return simpleInstruction(vm, "SET 6, D");
        case 0xF3: return simpleInstruction(vm, "SET 6, E");
        case 0xF4: return simpleInstruction(vm, "SET 6, H");
        case 0xF5: return simpleInstruction(vm, "SET 6, L");
        case 0xF6: return simpleInstruction(vm, "SET 6, (HL)");
        case 0xF7: return simpleInstruction(vm, "SET 6, A");
        case 0xF8: return simpleInstruction(vm, "SET 7, B");
        case 0xF9: return simpleInstruction(vm, "SET 7, C");
        case 0xFA: return simpleInstruction(vm, "SET 7, D");
        case 0xFB: return simpleInstruction(vm, "SET 7, E");
        case 0xFC: return simpleInstruction(vm, "SET 7, H");
        case 0xFD: return simpleInstruction(vm, "SET 7, L");
        case 0xFE: return simpleInstruction(vm, "SET 7, (HL)");
        case 0xFF: return simpleInstruction(vm, "SET 7, A");
    }
}

void printInstruction(VM* vm) {
#ifdef DEBUG_PRINT_ADDRESS
    printf("[0x%04x]", vm->PC);
#endif
#ifdef DEBUG_PRINT_FLAGS
    printFlags(vm);
#endif
#ifdef DEBUG_PRINT_CYCLES
	/* We print t-cycles */
    printf("[%ld]", vm->clock * 4);
#endif
#ifdef DEBUG_PRINT_JOYPAD_REG
    printf("[sel:%x|", (vm->MEM[R_P1_JOYP] >> 4) & 0x3);
    printf("sig:%x]", (vm->MEM[R_P1_JOYP] & 0b00001111));
#endif
#ifdef DEBUG_PRINT_TIMERS
	printf("[%x|%x|%x|%x]", vm->MEM[R_DIV], vm->MEM[R_TIMA], vm->MEM[R_TMA], vm->MEM[R_TAC]);
#endif
    printf(" %5s", "");
  
    switch (vm->MEM[vm->PC]) {
        case 0x00: return simpleInstruction(vm, "NOP");
        case 0x01: return d16(vm, "LD BC, d16");
        case 0x02: return simpleInstruction(vm, "LD (BC), A");
        case 0x03: return simpleInstruction(vm, "INC BC");
        case 0x04: return simpleInstruction(vm, "INC B");
        case 0x05: return simpleInstruction(vm, "DEC B");
        case 0x06: return d8(vm, "LD B, d8");
        case 0x07: return simpleInstruction(vm, "RLCA");
        case 0x08: return a16(vm, "LD a16, SP");
        case 0x09: return simpleInstruction(vm, "ADD HL, BC");
        case 0x0A: return simpleInstruction(vm, "LD A, (BC)");
        case 0x0B: return simpleInstruction(vm, "DEC BC");
        case 0x0C: return simpleInstruction(vm, "INC C");
        case 0x0D: return simpleInstruction(vm, "DEC C");
        case 0x0E: return d8(vm, "LD C, d8");
        case 0x0F: return simpleInstruction(vm, "RRCA");
        case 0x10: return simpleInstruction(vm, "STOP");
        case 0x11: return d16(vm, "LD DE, d16");
        case 0x12: return simpleInstruction(vm, "LD (DE), A");
        case 0x13: return simpleInstruction(vm, "INC DE");
        case 0x14: return simpleInstruction(vm, "INC D");
        case 0x15: return simpleInstruction(vm, "DEC D");
        case 0x16: return d8(vm, "LD D, d8");
        case 0x17: return simpleInstruction(vm, "RLA");
        case 0x18: return r8(vm, "JR r8");
        case 0x19: return simpleInstruction(vm, "ADD HL, DE");
        case 0x1A: return simpleInstruction(vm, "LD A, (DE)");
        case 0x1B: return simpleInstruction(vm, "DEC DE");
        case 0x1C: return simpleInstruction(vm, "INC E");
        case 0x1D: return simpleInstruction(vm, "DEC E");
        case 0x1E: return d8(vm, "LD E, D8");
        case 0x1F: return simpleInstruction(vm, "RRA");
        case 0x20: return r8(vm, "JR NZ, r8");
        case 0x21: return d16(vm, "LD HL, d16");
        case 0x22: return simpleInstruction(vm, "LD (HL+), A");
        case 0x23: return simpleInstruction(vm, "INC HL");
        case 0x24: return simpleInstruction(vm, "INC H");
        case 0x25: return simpleInstruction(vm, "DEC H");
        case 0x26: return d8(vm, "LD H, d8");
        case 0x27: return simpleInstruction(vm, "DAA");
        case 0x28: return r8(vm, "JR Z, r8");
        case 0x29: return simpleInstruction(vm, "ADD HL, HL");
        case 0x2A: return simpleInstruction(vm, "LD A, (HL+)");
        case 0x2B: return simpleInstruction(vm, "DEC HL");
        case 0x2C: return simpleInstruction(vm, "INC L");
        case 0x2D: return simpleInstruction(vm, "DEC L");
        case 0x2E: return d8(vm, "LD L, d8");
        case 0x2F: return simpleInstruction(vm, "CPL");
        case 0x30: return r8(vm, "JR NC, r8");
        case 0x31: return d16(vm, "LD SP,d16");
        case 0x32: return simpleInstruction(vm, "LD (HL-), A");
        case 0x33: return simpleInstruction(vm, "INC SP");
        case 0x34: return simpleInstruction(vm, "INC (HL)");
        case 0x35: return simpleInstruction(vm, "DEC (HL)");
        case 0x36: return d8(vm, "LD (HL), d8");
        case 0x37: return simpleInstruction(vm, "SCF");
        case 0x38: return r8(vm, "JR C, r8");
        case 0x39: return simpleInstruction(vm, "ADD HL, SP");
        case 0x3A: return simpleInstruction(vm, "LD A, (HL-)");
        case 0x3B: return simpleInstruction(vm, "DEC SP");
        case 0x3C: return simpleInstruction(vm, "INC A");
        case 0x3D: return simpleInstruction(vm, "DEC A");
        case 0x3E: return d8(vm, "LD A, d8");
        case 0x3F: return simpleInstruction(vm, "CCF");
        case 0x40: return simpleInstruction(vm, "LD B, B");
        case 0x41: return simpleInstruction(vm, "LD B, C");
        case 0x42: return simpleInstruction(vm, "LD B, D");
        case 0x43: return simpleInstruction(vm, "LD B, E");
        case 0x44: return simpleInstruction(vm, "LD B, H");
        case 0x45: return simpleInstruction(vm, "LD B, L");
        case 0x46: return simpleInstruction(vm, "LD B, (HL)");
        case 0x47: return simpleInstruction(vm, "LD B, A");
        case 0x48: return simpleInstruction(vm, "LD C, B");
        case 0x49: return simpleInstruction(vm, "LD C, C");
        case 0x4A: return simpleInstruction(vm, "LD C, D");
        case 0x4B: return simpleInstruction(vm, "LD C, E");
        case 0x4C: return simpleInstruction(vm, "LD C, H");
        case 0x4D: return simpleInstruction(vm, "LD C, L");
        case 0x4E: return simpleInstruction(vm, "LD C, (HL)");
        case 0x4F: return simpleInstruction(vm, "LD C, A");
        case 0x50: return simpleInstruction(vm, "LD D, B");
        case 0x51: return simpleInstruction(vm, "LD D, C");
        case 0x52: return simpleInstruction(vm, "LD D, D");
        case 0x53: return simpleInstruction(vm, "LD D, E");
        case 0x54: return simpleInstruction(vm, "LD D, H");
        case 0x55: return simpleInstruction(vm, "LD D, L");
        case 0x56: return simpleInstruction(vm, "LD D, (HL)");
        case 0x57: return simpleInstruction(vm, "LD D, A");
        case 0x58: return simpleInstruction(vm, "LD E, B");
        case 0x59: return simpleInstruction(vm, "LD E, C");
        case 0x5A: return simpleInstruction(vm, "LD E, D");
        case 0x5B: return simpleInstruction(vm, "LD E, E");
        case 0x5C: return simpleInstruction(vm, "LD E, H");
        case 0x5D: return simpleInstruction(vm, "LD E, L");
        case 0x5E: return simpleInstruction(vm, "LD E, (HL)");
        case 0x5F: return simpleInstruction(vm, "LD E, A");
        case 0x60: return simpleInstruction(vm, "LD H, B");
        case 0x61: return simpleInstruction(vm, "LD H, C");
        case 0x62: return simpleInstruction(vm, "LD H, D");
        case 0x63: return simpleInstruction(vm, "LD H, E");
        case 0x64: return simpleInstruction(vm, "LD H, H");
        case 0x65: return simpleInstruction(vm, "LD H, L");
        case 0x66: return simpleInstruction(vm, "LD H, (HL)");
        case 0x67: return simpleInstruction(vm, "LD H, A");
        case 0x68: return simpleInstruction(vm, "LD L, B");
        case 0x69: return simpleInstruction(vm, "LD L, C");
        case 0x6A: return simpleInstruction(vm, "LD L, D");
        case 0x6B: return simpleInstruction(vm, "LD L, E");
        case 0x6C: return simpleInstruction(vm, "LD L, H");
        case 0x6D: return simpleInstruction(vm, "LD L, L");
        case 0x6E: return simpleInstruction(vm, "LD L, (HL)");
        case 0x6F: return simpleInstruction(vm, "LD L, A");
        case 0x70: return simpleInstruction(vm, "LD (HL), B");
        case 0x71: return simpleInstruction(vm, "LD (HL), C");
        case 0x72: return simpleInstruction(vm, "LD (HL), D");
        case 0x73: return simpleInstruction(vm, "LD (HL), E");
        case 0x74: return simpleInstruction(vm, "LD (HL), H");
        case 0x75: return simpleInstruction(vm, "LD (HL), L");
        case 0x76: return simpleInstruction(vm, "HALT");
        case 0x77: return simpleInstruction(vm, "LD (HL), A");
        case 0x78: return simpleInstruction(vm, "LD A, B");
        case 0x79: return simpleInstruction(vm, "LD A, C");
        case 0x7A: return simpleInstruction(vm, "LD A, D");
        case 0x7B: return simpleInstruction(vm, "LD A, E");
        case 0x7C: return simpleInstruction(vm, "LD A, H");
        case 0x7D: return simpleInstruction(vm, "LD A, L");
        case 0x7E: return simpleInstruction(vm, "LD A, (HL)");
        case 0x7F: return simpleInstruction(vm, "LD A, A");
        case 0x80: return simpleInstruction(vm, "ADD A, B");
        case 0x81: return simpleInstruction(vm, "ADD A, C");
        case 0x82: return simpleInstruction(vm, "ADD A, D");
        case 0x83: return simpleInstruction(vm, "ADD A, E");
        case 0x84: return simpleInstruction(vm, "ADD A, H");
        case 0x85: return simpleInstruction(vm, "ADD A, L");
        case 0x86: return simpleInstruction(vm, "ADD A, (HL)");
        case 0x87: return simpleInstruction(vm, "ADD A, A");
        case 0x88: return simpleInstruction(vm, "ADC A, B");
        case 0x89: return simpleInstruction(vm, "ADC A, C");
        case 0x8A: return simpleInstruction(vm, "ADC A, D");
        case 0x8B: return simpleInstruction(vm, "ADC A, E");
        case 0x8C: return simpleInstruction(vm, "ADC A, H");
        case 0x8D: return simpleInstruction(vm, "ADC A, L");
        case 0x8E: return simpleInstruction(vm, "ADC A, (HL)");
        case 0x8F: return simpleInstruction(vm, "ADC A, A");
        case 0x90: return simpleInstruction(vm, "SUB B");
        case 0x91: return simpleInstruction(vm, "SUB C");
        case 0x92: return simpleInstruction(vm, "SUB D");
        case 0x93: return simpleInstruction(vm, "SUB E");
        case 0x94: return simpleInstruction(vm, "SUB H");
        case 0x95: return simpleInstruction(vm, "SUB L");
        case 0x96: return simpleInstruction(vm, "SUB (HL)");
        case 0x97: return simpleInstruction(vm, "SUB A");
        case 0x98: return simpleInstruction(vm, "SBC A, B");
        case 0x99: return simpleInstruction(vm, "SBC A, C");
        case 0x9A: return simpleInstruction(vm, "SBC A, D");
        case 0x9B: return simpleInstruction(vm, "SBC A, E");
        case 0x9C: return simpleInstruction(vm, "SBC A, H");
        case 0x9D: return simpleInstruction(vm, "SBC A, L");
        case 0x9E: return simpleInstruction(vm, "SBC A, (HL)");
        case 0x9F: return simpleInstruction(vm, "SBC A, A");
        case 0xA0: return simpleInstruction(vm, "AND B");
        case 0xA1: return simpleInstruction(vm, "AND C");
        case 0xA2: return simpleInstruction(vm, "AND D");
        case 0xA3: return simpleInstruction(vm, "AND E");
        case 0xA4: return simpleInstruction(vm, "AND H");
        case 0xA5: return simpleInstruction(vm, "AND L");
        case 0xA6: return simpleInstruction(vm, "AND (HL)");
        case 0xA7: return simpleInstruction(vm, "AND A");
        case 0xA8: return simpleInstruction(vm, "XOR B");
        case 0xA9: return simpleInstruction(vm, "XOR C");
        case 0xAA: return simpleInstruction(vm, "XOR D");
        case 0xAB: return simpleInstruction(vm, "XOR E");
        case 0xAC: return simpleInstruction(vm, "XOR H");
        case 0xAD: return simpleInstruction(vm, "XOR L");
        case 0xAE: return simpleInstruction(vm, "XOR (HL)");
        case 0xAF: return simpleInstruction(vm, "XOR A");
        case 0xB0: return simpleInstruction(vm, "OR B");
        case 0xB1: return simpleInstruction(vm, "OR C");
        case 0xB2: return simpleInstruction(vm, "OR D");
        case 0xB3: return simpleInstruction(vm, "OR E");
        case 0xB4: return simpleInstruction(vm, "OR H");
        case 0xB5: return simpleInstruction(vm, "OR L");
        case 0xB6: return simpleInstruction(vm, "OR (HL)");
        case 0xB7: return simpleInstruction(vm, "OR A");
        case 0xB8: return simpleInstruction(vm, "CP B");
        case 0xB9: return simpleInstruction(vm, "CP C");
        case 0xBA: return simpleInstruction(vm, "CP D");
        case 0xBB: return simpleInstruction(vm, "CP E");
        case 0xBC: return simpleInstruction(vm, "CP H");
        case 0xBD: return simpleInstruction(vm, "CP L");
        case 0xBE: return simpleInstruction(vm, "CP (HL)");
        case 0xBF: return simpleInstruction(vm, "CP A");
        case 0xC0: return simpleInstruction(vm, "RET NZ");
        case 0xC1: return simpleInstruction(vm, "POP BC");
        case 0xC2: return a16(vm, "JP NZ, a16");
        case 0xC3: return a16(vm, "JP a16");
        case 0xC4: return a16(vm, "CALL NZ, a16");
        case 0xC5: return simpleInstruction(vm, "PUSH BC");
        case 0xC6: return d8(vm, "ADD A, d8");
        case 0xC7: return simpleInstruction(vm, "RST 0x00");
        case 0xC8: return simpleInstruction(vm, "RET Z");
        case 0xC9: return simpleInstruction(vm, "RET");
        case 0xCA: return a16(vm, "JP Z, a16");
        case 0xCB: return simpleInstruction(vm, "PREFIX CB");
        case 0xCC: return a16(vm, "CALL Z, a16");
        case 0xCD: return a16(vm, "CALL a16");
        case 0xCE: return d8(vm, "ADC A, d8");
        case 0xCF: return simpleInstruction(vm, "RST 0x08");
        case 0xD0: return simpleInstruction(vm, "RET NC");
        case 0xD1: return simpleInstruction(vm, "POP DE");
        case 0xD2: return a16(vm, "JP NC, a16");
        case 0xD4: return a16(vm, "CALL NC, a16");
        case 0xD5: return simpleInstruction(vm, "PUSH DE");
        case 0xD6: return d8(vm, "SUB d8");
        case 0xD7: return simpleInstruction(vm, "RST 0x10");
        case 0xD8: return simpleInstruction(vm, "REC C");
        case 0xD9: return simpleInstruction(vm, "RETI");
        case 0xDA: return a16(vm, "JP C, a16");
        case 0xDC: return a16(vm, "CALL C, a16");
        case 0xDE: return d8(vm, "SBC A, d8");
        case 0xDF: return simpleInstruction(vm, "RST 0x18");
        case 0xE0: return d8(vm, "LD (0xFF00 + d8), A");
        case 0xE1: return simpleInstruction(vm, "POP HL");
        case 0xE2: return simpleInstruction(vm, "LD (0xFF00 + C), A");
        case 0xE5: return simpleInstruction(vm, "PUSH HL");
        case 0xE6: return d8(vm, "AND d8");
        case 0xE7: return simpleInstruction(vm, "RST 0x20");
        case 0xE8: return r8(vm, "ADD SP, r8");
        case 0xE9: return simpleInstruction(vm, "JP (HL)");
        case 0xEA: return a16(vm, "LD (a16), A");
        case 0xEE: return d8(vm, "XOR d8");
        case 0xEF: return simpleInstruction(vm, "RST 0x28");
        case 0xF0: return d8(vm, "LD A, (0xFF00 + d8)");
        case 0xF1: return simpleInstruction(vm, "POP AF");
        case 0xF2: return simpleInstruction(vm, "LD A, (0xFF00 + C)");
        case 0xF3: return simpleInstruction(vm, "DI");
        case 0xF5: return simpleInstruction(vm, "PUSH AF");
        case 0xF6: return d8(vm, "OR d8");
        case 0xF7: return simpleInstruction(vm, "RST 0x30");
        case 0xF8: return r8(vm, "LD HL, SP + r8");
        case 0xF9: return simpleInstruction(vm, "LD SP, HL");
        case 0xFA: return a16(vm, "LD A, (a16)");
        case 0xFB: return simpleInstruction(vm, "EI");
        case 0xFE: return d8(vm, "CP d8");
        case 0xFF: return simpleInstruction(vm, "RST 0x38");
        default: return simpleInstruction(vm, "????");
    }
}

void printRegisters(VM* vm) {
    printf("[A%02x|B%02x|C%02x|D%02x|E%02x|H%02x|L%02x|SP%04x]\n", 
            vm->GPR[R8_A], vm->GPR[R8_B], vm->GPR[R8_C],
            vm->GPR[R8_D], vm->GPR[R8_E], vm->GPR[R8_H],
            vm->GPR[R8_L], (uint16_t)(vm->GPR[R8_SP_HIGH] << 8) + vm->GPR[R8_SP_LOW]);
}
