/*
 * calibration.c
 *
 *  Created on: 15 апр. 2015 г.
 *      Author: DDDD
 */

#include <stdio.h>
#include <stdlib.h>
#include "calibration.h"
#include "usart.h"

static FILE usart_str = FDEV_SETUP_STREAM(Tx_Char, uart_getc, _FDEV_SETUP_RW);

float biasX_s[] = { 0, -16.656539, 0, 0, 0, 0 };
float biasY_s[] = { 0, -177.28387, 0, 0, 0, 0 };
float biasZ_s[] = { 0, 77.193884, 0, 0, 0, 0 };
float gainX1_s[] = { 0, 1.094365, 0, 0, 0, 0 };
float gainX2_s[] = { 0, 0.024061, 0, 0, 0, 0 };
float gainX3_s[] = { 0, 0.005204, 0, 0, 0, 0 };
float gainY1_s[] = { 0, 0.024061, 0, 0, 0, 0 };
float gainY2_s[] = { 0, 1.067757, 0, 0, 0, 0 };
float gainY3_s[] = { 0, 0.024715, 0, 0, 0, 0 };
float gainZ1_s[] = { 0, 0.005204, 0, 0, 0, 0 };
float gainZ2_s[] = { 0, 0.024715, 0, 0, 0, 0 };
float gainZ3_s[] = { 0, 1.136209, 0, 0, 0, 0 };



int power(int n, int m) {
	if (m == 1)
		return n;
	else
		return n * (power(n, m - 1));
}

float strToFloat(char str[]) {
	float result = 0.0f;
	int len = strlen(str);
	int dotpos = 0;
	for (int n = 0; n < len; n++) {
		if (str[n] == '.') {
			dotpos = len - n - 1;
		} else {
			result = result * 10 + (str[n] - '0');
		}
	}
	result /= power(10, dotpos);
	return result;
}

void Calibrate() {
	stdout = stdin = &usart_str;
	char s[20];
	scanf("%s", &s);
	printf("s=%s   ", s);
	biasX_s[1] = strToFloat(s);
	printf("biasX_s1[1]=%d", (int) (biasX_s[1] * 100));

	//}
}
