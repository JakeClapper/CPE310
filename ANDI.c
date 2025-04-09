#include "Instruction.h"
// Author: Kayden Yost

/**
 * Function: andi_immd_assm
 * ------------------------
 * Encodes the "ANDI" (Bitwise AND Immediate) instruction into binary format using I-type format.
 * 
 * Preconditions:
 * - OP_CODE must be "ANDI".
 * - PARAM1 must be a REGISTER (destination register).
 * - PARAM2 must be a REGISTER (source register).
 * - PARAM3 must be an IMMEDIATE value (16-bit integer).
 * - All register values must be within the range 0–31.
 * - Immediate value must be within the 16-bit range (0–65535).
 * 
 * Postconditions:
 * - Sets the binary representation of the ANDI instruction.
 * - Updates the `state` to COMPLETE_ENCODE if successful, or an error state otherwise.
 */
void andi_immd_assm(void) {
    // Check if the operation code matches "ANDI".
    if (strcmp(OP_CODE, "ANDI") != 0) {
        state = WRONG_COMMAND; // Set state to WRONG_COMMAND if the opcode is incorrect.
        return;
    }

    // Validate that PARAM1 is a REGISTER (destination).
    if (PARAM1.type != REGISTER) {
        state = MISSING_REG; // Set state to MISSING_REG if PARAM1 is not a REGISTER.
        return;
    }

    // Validate that PARAM2 is a REGISTER (source).
    if (PARAM2.type != REGISTER) {
        state = MISSING_REG; // Set state to MISSING_REG if PARAM2 is not a REGISTER.
        return;
    }

    // Validate that PARAM3 is an IMMEDIATE value.
    if (PARAM3.type != IMMEDIATE) {
        state = INVALID_PARAM; // Set state to INVALID_PARAM if PARAM3 is not an IMMEDIATE.
        return;
    }

    // Validate that the register values are within the valid range (0–31).
    if (PARAM1.value > 31 || PARAM2.value > 31) {
        state = INVALID_REG; // Set state to INVALID_REG if either register is out of range.
        return;
    }

    // Validate that the immediate value fits in 16 bits.
    if (PARAM3.value > 0xFFFF) {
        state = INVALID_IMMED; // Set state to INVALID_IMMED if the immediate exceeds 16 bits.
        return;
    }

    // Set the opcode bits for ANDI.
    setBits_str(31, "001100");

    // Set the source register (rs).
    setBits_num(25, PARAM2.value, 5);

    // Set the destination register (rt).
    setBits_num(20, PARAM1.value, 5);

    // Set the 16-bit immediate value.
    setBits_num(15, PARAM3.value, 16);

    // Update the state to indicate successful encoding.
    state = COMPLETE_ENCODE;
}

/**
 * Function: andi_immd_bin
 * -----------------------
 * Decodes a binary representation of the "ANDI" (Bitwise AND Immediate) instruction into its components.
 * 
 * Preconditions:
 * - The binary instruction must have the opcode "001100" at bits 31–26.
 * 
 * Postconditions:
 * - Extracts the source register (rs), destination register (rt), and immediate value.
 * - Sets the operation and parameters using `setOp` and `setParam`.
 * - Updates the `state` to COMPLETE_DECODE if successful, or an error state otherwise.
 */
void andi_immd_bin(void) {
    // Check if the opcode in the binary instruction matches "ANDI".
    if (checkBits(31, "001100") != 0) {
        state = WRONG_COMMAND; // Set state to WRONG_COMMAND if the opcode is incorrect.
        return;
    }

    // Extract the register and immediate values.
    uint32_t Rs = getBits(25, 5);     // Source register (rs).
    uint32_t Rt = getBits(20, 5);     // Destination register (rt).
    uint32_t imm16 = getBits(15, 16); // 16-bit immediate value.

    // Set the operation name to "ANDI".
    setOp("ANDI");

    // Set the parameters in the correct order.
    setParam(1, REGISTER, Rt);      // rt (destination).
    setParam(2, REGISTER, Rs);      // rs (source).
    setParam(3, IMMEDIATE, imm16);  // immediate.

    // Update the state to indicate successful decoding.
    state = COMPLETE_DECODE;
}
