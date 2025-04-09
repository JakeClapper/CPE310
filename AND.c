#include "Instruction.h"
// Author: Kayden Yost

/**
 * Function: and_reg_assm
 * ----------------------
 * Encodes the "AND" (Bitwise AND) instruction into binary format using R-type format.
 * 
 * Preconditions:
 * - OP_CODE must be "AND".
 * - PARAM1 must be a REGISTER (destination register).
 * - PARAM2 must be a REGISTER (first source register).
 * - PARAM3 must be a REGISTER (second source register).
 * - All register values must be within the range 0–31.
 * 
 * Postconditions:
 * - Sets the binary representation of the AND instruction.
 * - Updates the `state` to COMPLETE_ENCODE if successful, or an error state otherwise.
 */
void and_reg_assm(void) {
    // Check if the operation code matches "AND".
    if (strcmp(OP_CODE, "AND") != 0) {
        state = WRONG_COMMAND; // Set state to WRONG_COMMAND if the opcode is incorrect.
        return;
    }

    // Validate that PARAM1 is a REGISTER (destination).
    if (PARAM1.type != REGISTER) {
        state = MISSING_REG; // Set state to MISSING_REG if PARAM1 is not a REGISTER.
        return;
    }

    // Validate that PARAM2 is a REGISTER (first source).
    if (PARAM2.type != REGISTER) {
        state = MISSING_REG; // Set state to MISSING_REG if PARAM2 is not a REGISTER.
        return;
    }

    // Validate that PARAM3 is a REGISTER (second source).
    if (PARAM3.type != REGISTER) {
        state = MISSING_REG; // Set state to MISSING_REG if PARAM3 is not a REGISTER.
        return;
    }

    // Ensure all register values are within the valid range (0–31).
    if (PARAM1.value > 31 || PARAM2.value > 31 || PARAM3.value > 31) {
        state = INVALID_REG; // Set state to INVALID_REG if any register is out of range.
        return;
    }

    // Set the opcode bits for R-type (always 000000 for AND).
    setBits_num(31, 0, 6);

    // Set the source registers (rs and rt).
    setBits_num(25, PARAM2.value, 5); // rs
    setBits_num(20, PARAM3.value, 5); // rt

    // Set the destination register (rd).
    setBits_num(15, PARAM1.value, 5); // rd

    // Set the shift amount (shamt), always 0 for AND.
    setBits_num(10, 0, 5);

    // Set the function code for AND.
    setBits_str(5, "100100");

    // Update the state to indicate successful encoding.
    state = COMPLETE_ENCODE;
}

/**
 * Function: and_reg_bin
 * ---------------------
 * Decodes a binary representation of the "AND" (Bitwise AND) instruction into its components.
 * 
 * Preconditions:
 * - The binary instruction must have the opcode "000000" at bits 31–26.
 * - The binary instruction must have the function code "100100" at bits 5–0.
 * 
 * Postconditions:
 * - Extracts the rs, rt, and rd register values.
 * - Sets the operation and parameters using `setOp` and `setParam`.
 * - Updates the `state` to COMPLETE_DECODE if successful, or an error state otherwise.
 */
void and_reg_bin(void) {
    // Check if the opcode and function code in the binary instruction match "AND".
    if (checkBits(31, "000000") != 0 || checkBits(5, "100100") != 0) {
        state = WRONG_COMMAND; // Set state to WRONG_COMMAND if the opcode or function code is incorrect.
        return;
    }

    // Extract the register values.
    uint32_t Rs = getBits(25, 5); // First source register (rs).
    uint32_t Rt = getBits(20, 5); // Second source register (rt).
    uint32_t Rd = getBits(15, 5); // Destination register (rd).

    // Set the operation name to "AND".
    setOp("AND");

    // Set the destination and source register parameters.
    setParam(1, REGISTER, Rd); // rd
    setParam(2, REGISTER, Rs); // rs
    setParam(3, REGISTER, Rt); // rt

    // Update the state to indicate successful decoding.
    state = COMPLETE_DECODE;
}
