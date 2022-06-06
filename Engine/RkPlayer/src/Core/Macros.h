#pragma once

#define GIBIBYTES(amount) amount * 1024 * 1024 * 1024
#define MEBIBYTES(amount) amount * 1024 * 1024
#define KIBIBYTES(amount) amount * 1024

#define GIGABYTES(amount) amount * 1000 * 1000 * 1000
#define MEGABYTES(amount) amount * 1000 * 1000
#define KILOBYTES(amount) amount * 1000

#define SET_BIT(byte, bitPos)   ((byte) |= (1 << (bitPos)))
#define CLEAR_BIT(byte, bitPos) ((byte) &= ~(1 << (bitPos)))
#define FLIP_BIT(byte, bitPos)  ((byte) ^= (1 << (bitPos)))
#define CHECK_BIT(byte, bitPos) ((byte) & (1 << (bitPos)))

#define INCLUSIVE_CLAMP(x, min, max) (x <= min) ? min : (x >= max) ? max : x
#define EXCLUSIVE_CLAMP(x, min, max) (x < min) ? min : (x > max) ? max : x
