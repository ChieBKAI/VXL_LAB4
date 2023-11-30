/*
 * display.c
 *
 *  Created on: Nov 2, 2023
 *      Author: K21
 */
#include "display.h"

int SEG_turn = 0;


void display7SEG(int num1, int num2) {
    // Define the 7-segment patterns for each digit
    const uint8_t segmentPatterns[] = {
        0b11000000, // 0
        0b11111001, // 1
        0b10100100, // 2
        0b10110000, // 3
        0b10011001, // 4
        0b10010010, // 5
        0b10000010, // 6
        0b11111000, // 7
        0b10000000, // 8
        0b10010000  // 9
    };

    // Ensure the input number is within the valid range (0-9)
    if (num1 < 0 || num1 > 9 || num2 < 0 || num2 > 9) {
        // Handle invalid input
        return;
    }

    // Set the GPIO pins according to the 7-segment pattern for the digit
    HAL_GPIO_WritePin(SEG_A_1_GPIO_Port, SEG_A_1_Pin, (segmentPatterns[num1] >> 0) & 1);
    HAL_GPIO_WritePin(SEG_B_1_GPIO_Port, SEG_B_1_Pin, (segmentPatterns[num1] >> 1) & 1);
    HAL_GPIO_WritePin(SEG_C_1_GPIO_Port, SEG_C_1_Pin, (segmentPatterns[num1] >> 2) & 1);
    HAL_GPIO_WritePin(SEG_D_1_GPIO_Port, SEG_D_1_Pin, (segmentPatterns[num1] >> 3) & 1);
    HAL_GPIO_WritePin(SEG_E_1_GPIO_Port, SEG_E_1_Pin, (segmentPatterns[num1] >> 4) & 1);
    HAL_GPIO_WritePin(SEG_F_1_GPIO_Port, SEG_F_1_Pin, (segmentPatterns[num1] >> 5) & 1);
    HAL_GPIO_WritePin(SEG_G_1_GPIO_Port, SEG_G_1_Pin, (segmentPatterns[num1] >> 6) & 1);

    HAL_GPIO_WritePin(SEG_A_2_GPIO_Port, SEG_A_2_Pin, (segmentPatterns[num2] >> 0) & 1);
    HAL_GPIO_WritePin(SEG_B_2_GPIO_Port, SEG_B_2_Pin, (segmentPatterns[num2] >> 1) & 1);
    HAL_GPIO_WritePin(SEG_C_2_GPIO_Port, SEG_C_2_Pin, (segmentPatterns[num2] >> 2) & 1);
    HAL_GPIO_WritePin(SEG_D_2_GPIO_Port, SEG_D_2_Pin, (segmentPatterns[num2] >> 3) & 1);
    HAL_GPIO_WritePin(SEG_E_2_GPIO_Port, SEG_E_2_Pin, (segmentPatterns[num2] >> 4) & 1);
    HAL_GPIO_WritePin(SEG_F_2_GPIO_Port, SEG_F_2_Pin, (segmentPatterns[num2] >> 5) & 1);
    HAL_GPIO_WritePin(SEG_G_2_GPIO_Port, SEG_G_2_Pin, (segmentPatterns[num2] >> 6) & 1);
}
void toggle_SEG(int turn) {
	if (turn == 1) {
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);
		return;
	}
	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
	HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
}
void turn_off_SEG() {
	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
	HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);
}

void update_SEG(int seg1, int seg2) {
	display7SEG(seg1, seg2);
}

void DISPLAY_OUTPUT() {
	turn_off_SEG();
	toggle_SEG(SEG_turn);
	SEG_turn = 1 - SEG_turn;
}

