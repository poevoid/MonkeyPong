#pragma once

/**** FX data header generated by fxdata-build.py tool version 1.15 ****/

using uint24_t = __uint24;

// Initialize FX hardware using  FX::begin(FX_DATA_PAGE); in the setup() function.

constexpr uint16_t FX_DATA_PAGE  = 0xff83;
constexpr uint24_t FX_DATA_BYTES = 27670;

constexpr uint16_t FX_SAVE_PAGE  = 0xfff0;
constexpr uint24_t FX_SAVE_BYTES = 2;

constexpr uint24_t abutton = 0x000000;
constexpr uint24_t bananaspin = 0x000302;
constexpr uint24_t bbutton = 0x000604;
constexpr uint24_t MonkeyIdleEast = 0x000906;
constexpr uint24_t MonkeyIdleWest = 0x001208;
constexpr uint24_t monkeymad = 0x001B0A;
constexpr uint24_t MonkeyWalkEast = 0x001E0C;
constexpr uint24_t MonkeyWalkWest = 0x002A0E;
constexpr uint24_t monkeywin = 0x003610;
constexpr uint24_t punklogooutlined = 0x003C12;
constexpr uint24_t titlecard = 0x005414;
