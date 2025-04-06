#include "Instruction.h"
// Author: Kayden Yost

/**
 * Function: or_reg_assm
 * ---------------------
 * Encodes the "OR" (Bitwise OR) instruction into binary format based on the provided parameters.
 * 
 * Preconditions:
 * - OP_CODE must be "OR".
 * - PARAM1, PARAM2, and PARAM3 must be REGISTER types.
 * - PARAM1 is the destination register (Rd).
 * - PARAM2 and PARAM3 are the source registers (Rs and Rt).
 * 
 * Postconditions:
 * - Sets the binary representation of the instruction using `setBits_str` and `setBits_num`.
 * - Updates the `state` to COMPLETE_ENCODE if successful, or an error state otherwise.
 */
void or_reg_assm(void) {
    // Check if the operation code matches "OR".
    if (strcmp(OP_CODE, "OR") != 0) {
        state = WRONG_COMMAND; // Set state to WRONG_COMMAND if the opcode is incorrect.
        return;
    }

    // Verify that all parameters are registers.
    if (PARAM1.type != REGISTER || PARAM2.type != REGISTER || PARAM3.type != REGISTER) {
        state = INVALID_PARAM; // Set state to INVALID_PARAM if any parameter is not a REGISTER.
        return;
    }

    // Set the opcode for R-type instruction (OR).
    setBits_str(31, "000000");

    // Set the destination register (Rd) bits.
    setBits_num(20, PARAM1.value, 5);

    // Set the source registers (Rs and Rt) bits.
    setBits_num(25, PARAM2.value, 5);
    setBits_num(15, PARAM3.value, 5);

    // Set the shift amount (shamt) to 0.
    setBits_str(10, "00000");

    // Set the function code for "OR".
    setBits_str(5, "100101");

    // Update the state to indicate successful encoding.
    state = COMPLETE_ENCODE;
}

/**
 * Function: or_reg_bin
 * --------------------
 * Decodes a binary representation of the "OR" (Bitwise OR) instruction into its components.
 * 
 * Preconditions:
 * - The binary instruction must have the opcode "000000" at bits 31-26 and the function code "100101" at bits 5-0.
 * 
 * Postconditions:
 * - Extracts the source registers (Rs and Rt) and the destination register (Rd).
 * - Sets the operation and parameters using `setOp` and `setParam`.
 * - Updates the `state` to COMPLETE_DECODE if successful, or an error state otherwise.
 */
void or_reg_bin(void) {
    // Check if the opcode and function code in the binary instruction match "OR".
    if (checkBits(31, "000000") != 0 || checkBits(5, "100101") != 0) {
        state = WRONG_COMMAND; // Set state to WRONG_COMMAND if the opcode or function code is incorrect.
        return;
    }

    // Extract the source registers (Rs and Rt) and the destination register (Rd) from the binary instruction.
    uint32_t Rs = getBits(25, 5); // Extract Rs from bits 25-21.
    uint32_t Rt = getBits(20, 5); // Extract Rt from bits 20-16.
    uint32_t Rd = getBits(15, 5); // Extract Rd from bits 15-11.

    // Set the operation name to "OR".
    setOp("OR");

    // Set the destination register parameter (Rd).
    setParam(1, REGISTER, Rd);

    // Set the first source register parameter (Rs).
    setParam(2, REGISTER, Rs);

    // Set the second source register parameter (Rt).
    setParam(3, REGISTER, Rt);

    // Update the state to indicate successful decoding.
    state = COMPLETE_DECODE;
}