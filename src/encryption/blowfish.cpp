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
    result = ((S_BOX[0][a] + S_BOX[1][b])^S_BOX[2][c]) + S_BOX[3][d];
    return result;
}

