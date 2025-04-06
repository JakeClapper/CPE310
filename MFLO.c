#include "Instruction.h"
// Author: Kayden Yost

/**
 * Function: mflo_reg_assm
 * -----------------------
 * Encodes the "MFLO" (Move From LO Register) instruction into binary format based on the provided parameters.
 * 
 * Preconditions:
 * - OP_CODE must be "MFLO".
 * - PARAM1 must be a REGISTER (destination register).
 * - PARAM1.value must be within the valid range of 0-31.
 * 
 * Postconditions:
 * - Sets the binary representation of the instruction using `setBits_str` and `setBits_num`.
 * - Updates the `state` to COMPLETE_ENCODE if successful, or an error state otherwise.
 */
void mflo_reg_assm(void) {

    // Check if the operation code matches "MFLO".
    if (strcmp(OP_CODE, "MFLO") != 0) {
        state = WRONG_COMMAND; // Set state to WRONG_COMMAND if the opcode is incorrect.
        return;
    }
    
    // Validate that the first parameter is a REGISTER.
    if (PARAM1.type != REGISTER) {
        state = MISSING_REG; // Set state to MISSING_REG if PARAM1 is not a REGISTER.
        return;
    }
    
    // Validate that the register value is within the valid range (0-31).
    if (PARAM1.value > 31) {
        state = INVALID_REG; // Set state to INVALID_REG if the register value is invalid.
        return;
    }
    
    // Set the opcode bits for "MFLO".
    setBits_str(31, "000000");

    // Set the function code bits for "MFLO".
    setBits_str(5, "010010");

    // Set the destination register (Rd) bits.
    setBits_num(15, PARAM1.value, 5);

    // Update the state to indicate successful encoding.
    state = COMPLETE_ENCODE;
}

/**
 * Function: mflo_reg_bin
 * ----------------------
 * Decodes a binary representation of the "MFLO" (Move From LO Register) instruction into its components.
 * 
 * Preconditions:
 * - The binary instruction must have the opcode "000000" at bits 31-26 and the function code "010010" at bits 5-0.
 * 
 * Postconditions:
 * - Extracts the destination register (Rd).
 * - Sets the operation and parameters using `setOp` and `setParam`.
 * - Updates the `state` to COMPLETE_DECODE if successful, or an error state otherwise.
 */
void mflo_reg_bin(void) {

    // Check if the opcode and function code in the binary instruction match "MFLO".
    if (checkBits(31, "000000") != 0 || checkBits(5, "010010") != 0) {
        state = WRONG_COMMAND; // Set state to WRONG_COMMAND if the opcode or function code is incorrect.
        return;
    }
    
    // Extract the destination register (Rd) from bits 15-11.
    uint32_t Rd = getBits(15, 5);

    // Set the operation name to "MFLO".
    setOp("MFLO");

    // Set the destination register parameter.
    setParam(1, REGISTER, Rd);

    // Update the state to indicate successful decoding.
    state = COMPLETE_DECODE;
}