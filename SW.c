#include "Instruction.h"

void sw_immd_assm(void) {
	// Checking that the op code matches
	// strcmp(string1, string2) return 0 if they match
	if (strcmp(OP_CODE, "LW") != 0) {
		// If the op code doesnt match, this isnt the correct command
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of parameters
	*/

	// The first parameter should be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Param 2 needs to be a register
	if (PARAM3.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Param 3 needs to be an immediate
	if (PARAM2.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}


	/*
		Checking the value of parameters
	*/

	// Rt should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rs should be 31 or less
	if (PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}

	// The immediate value is limited to 16 bits, this is 0xFFFF
	if (PARAM2.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}



	/*
		Putting the binary together
	*/

	// Set the opcode
	setBits_str(31, "100011");


	// set Rt
	setBits_num(20, PARAM1.value, 5);

	// set Rs
	setBits_num(25, PARAM3.value, 5);

	// set immediate
	setBits_num(15, PARAM2.value, 16);

	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void sw_immd_bin(void) {
	state = WRONG_COMMAND;
}