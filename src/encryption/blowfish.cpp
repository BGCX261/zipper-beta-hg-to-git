#include "blowfish.h"

Blowfish::Blowfish()
{
}

Blowfish::Blowfish(const Blowfish& orig)
{
}

Blowfish::~Blowfish()
{
}

int32_t Blowfish::blowfishFeistel(int32_t data)
{
    int8_t a, b, c, d;
    int32_t result;
    a = data >> 24;
    b = (data >> 16)& 0xff;
    c = (data >> 8) & 0xff;
    d = data & 0xff;
    result = ((SBox[0][a] + SBox[1][b])^SBox[2][c]) + SBox[3][d];
    return result;
}

