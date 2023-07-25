
#pragma once

#include <stdlib.h>

void creatBuffer();
void deleteBuffer();
void appendToBuffer(char ch);
void getBuffer(char **buffer, int *sz);
void clearBuffer();