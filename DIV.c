/*
 * Author: Ol' Jim
 * Date: 06/13/2012
 * ByteForge Systems
 * MIPS-Translatron 3000
 */

 #include "Instruction.h"

 /**
  * Function: div_reg_assm
  * -----------------------
  * Assembles a MIPS R-type "DIV" (Divide) instruction into its binary representation.
  * 
  * Preconditions:
  * - OP_CODE must be "DIV".
  * - PARAM1 must be a REGISTER (Rt).
  * - PARAM2 must be a REGISTER (Rs).
  * - Register values must be within 0–31.
  * 
  * Postconditions:
  * - Encodes the instruction as binary.
  * - Sets `state` to COMPLETE_ENCODE if successful, or an error state if validation fails.
  */
 void div_reg_assm(void) {
	 // Check opcode
	 if (strcmp(OP_CODE, "DIV") != 0) {
		 state = WRONG_COMMAND;
		 return;
	 }
 
	 // Validate parameter types
	 if (PARAM1.type != REGISTER || PARAM2.type != REGISTER) {
		 state = MISSING_REG;
		 return;
	 }
 
	 // Validate register values
	 if (PARAM1.value > 31 || PARAM2.value > 31) {
		 state = INVALID_REG;
		 return;
	 }
 
	 // Begin encoding: DIV is an R-type instruction
	 setBits_str(31, "000000");               // Opcode for R-type (bits 31–26)
	 setBits_num(25, PARAM2.value, 5);        // Rs (PARAM2) — bits 25–21
	 setBits_num(20, PARAM1.value, 5);        // Rt (PARAM1) — bits 20–16
	 setBits_num(15, 0, 5);                   // Rd — unused, set to 0
	 setBits_num(10, 0, 5);                   // Shamt — unused, set to 0
	 setBits_str(5, "011010");                // Function code for DIV (bits 5–0)
 
	 // Mark completion
	 state = COMPLETE_ENCODE;
 }
 
 
 /**
  * Function: div_reg_bin
  * ----------------------
  * Decodes the binary form of the MIPS "DIV" instruction into readable fields.
  * 
  * Preconditions:
  * - Must match the opcode ("000000") and function code ("011010").
  * 
  * Postconditions:
  * - Sets OP_CODE and registers Rs and Rt from binary.
  * - Updates `state` to COMPLETE_DECODE or error if the instruction doesn't match.
  */
 void div_reg_bin(void) {
	 // Validate opcode and function code for DIV
	 if (checkBits(31, "000000") != 0 || checkBits(5, "011010") != 0) {
		 state = WRONG_COMMAND;
		 return;
	 }
 
	 // Extract Rs and Rt from instruction
	 uint32_t Rs = getBits(25, 5); // Source register
	 uint32_t Rt = getBits(20, 5); // Target register
 
	 // Populate instruction metadata
	 setOp("DIV");
	 setParam(1, REGISTER, Rs);
	 setParam(2, REGISTER, Rt);
 
	 // Mark decoding as successful
	 state = COMPLETE_DECODE;
 }
 