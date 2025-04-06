/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

// dont get paid enough to implement

#include "Instruction.h"

void ori_immd_assm(void) {
    if (strcmp(OP_CODE, "ORI") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    if (PARAM1.type != REGISTER || PARAM2.type != REGISTER || PARAM3.type != IMMEDIATE) {
        state = INVALID_PARAM;
        return;
    }

    //set the opcode for ORI
    setBits_str(31, "001101");
    //set Rt as the destination register
    setBits_num(20, PARAM1.value, 5);
    //set Rs as the source register
    setBits_num(25, PARAM2.value, 5);
    //set the immediate value for ORI
    setBits_num(15, PARAM3.value, 16);
    state = COMPLETE_ENCODE;
}

//decode ORI instruction from binary to assembly
void ori_immd_bin(void) {
    if (checkBits(31, "001101") != 0) {
        state = WRONG_COMMAND;
        return;
    }
    //take Rs, Rt, and immediate from binary
    uint32_t Rs = getBits(25, 5);
    uint32_t Rt = getBits(20, 5);
    uint32_t imm16 = getBits(15, 16);
    //set operation and parameters for decoded instruction
    setOp("ORI");
    setParam(1, REGISTER, Rt);
    setParam(2, REGISTER, Rs);
    setParam(3, IMMEDIATE, imm16);
    // indicate decoding is complete
    state = COMPLETE_DECODE;
}



