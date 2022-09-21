//
// Created by scion on 9/13/2022.
//

#define DEG_TO_RAD ((float) std::numbers::pi / 180)
#define RAD_TO_DEG (180 / std::numbers::pi)

#define TRUE_MOD(x, mod) (std::fmod(x, mod) >= 0 ? std::fmod(x, mod) : std::fmod(x, mod) + mod)
#define CLAMP_MOD(x, mod) (x > mod || x < -mod ? TRUE_MOD(x, mod) : x)
#define QUICK_CEIL_DIVISION(x, y) (((x) + (y) - 1) / (y))