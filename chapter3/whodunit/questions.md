# Questions

## What's `stdint.h`?

`stdint.h` is a header file in the C standard library which was introduced in the C99 standard library.
This allowed programmers to write more portable code by providing a set of
typedefs that specify exact-width integer types.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

These are unassigned and signed intergers types from `stdint.h`. That uses
well-defined types makes the code far easier and safer to port since you won't
get any supries when one machine interprets an int as a 16-bit and another
as a 32-bir machine.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1 byte in a `BYTE`
4 bytes in a `DWORD` (32 Bits)
4 bytes in a `LONG` (32 Bits)
2 bytes in a `WORD` (16 Bits)

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

The first two bytes of any `BMP` file contain ASCII B then ASCII M.

## What's the difference between `bfSize` and `biSize`?

The `bfSize` is the size of the bmp file. Unlike the `biSize` which is the size
of the structure. Both are read in bytes

## What does it mean if `biHeight` is negative?

If the `biHeight` is positive, the image is flipped upside down (read bottom upwards).
If the `biHeight` is negative, the image is standard top to bottom (read bottom down)

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

The `biCBitCounter` specifies the BMP's color depth -- the number of bits per pixel

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

`fopen` might return a NULL pointer if the file that `fopen` is trying to reach
doesn't exist, but creates that file for future references.

## Why is the third argument to `fread` always `1` in our code?

`Fread`'s third argument is aways 1 because we are iterating over ever pixel

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

If the `int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;`
This ensures the number of bytes in every row is a multiple of 4

## What does `fseek` do?

`fseek` allows us to change the offset of a pointer

## What is `SEEK_CUR`?

`SEEK_CUR` is the current position indicator in the file

## Whodunit?

It was Professor Plum with the candlestick in the library
