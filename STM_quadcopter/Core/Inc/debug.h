#include "usart.h"
#include "main.h"


int msgLen;
char msgDebug[100];

void PRINTF(char str[100]);


void PRINTF8(char str[100], uint8_t val);


void PRINTF16(char str[100], uint16_t val);


void PRINTF32(char str[100], uint32_t val);


void PRINTFchar(char str[100], char lettere[20]);


