#ifndef FIELD_H
#define FIELD_H

#include <stdint.h>

void initField(void);
void clearField(void);
uint8_t checkLineFull(int row);
void removeFullLines(void);

#endif
