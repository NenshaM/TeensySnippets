/*
  ============================================================
   Base64 - Lightweight Embedded Base64 Encoder
  ============================================================

  Description:
    Minimal, deterministic Base64 encoder designed for
    resource-constrained embedded systems.

    Features:
      - No dynamic memory allocation
      - No STL dependencies
      - Small flash footprint
      - Deterministic memory usage
      - Null-terminated output
      - Padding compliant with RFC 4648

  Usage:
      size_t outLen = Base64::encodedLength(inputLen);
      char output[outLen + 1];
      Base64::encode(output, input, inputLen);

  Notes:
      Output buffer must be at least:
          encodedLength(inputLength) + 1

      The +1 accounts for the null terminator.

  Author: NenshaM
  License: GPL v3
  Version: 1.0.0
  ============================================================
*/

#include "Base64.h"

static const char BASE64_TABLE[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

size_t Base64::encodedLength(size_t inputLength)
{
    // 4 output chars for every 3 input bytes
    return ((inputLength + 2) / 3) * 4;
}

void Base64::encode(char* output, char* input, size_t inputLength)
{
    size_t i = 0;
    size_t j = 0;

    while (i < inputLength)
    {
        uint32_t octet_a = input[i++];
        uint32_t octet_b = (i < inputLength) ? input[i++] : 0;
        uint32_t octet_c = (i < inputLength) ? input[i++] : 0;

        uint32_t triple = (octet_a << 16)
                        | (octet_b << 8)
                        |  octet_c;

        output[j++] = BASE64_TABLE[(triple >> 18) & 0x3F];
        output[j++] = BASE64_TABLE[(triple >> 12) & 0x3F];

        if (i - 1 > inputLength)
            output[j++] = '=';
        else
            output[j++] = BASE64_TABLE[(triple >> 6) & 0x3F];

        if (i > inputLength)
            output[j++] = '=';
        else
            output[j++] = BASE64_TABLE[triple & 0x3F];
    }

    output[j] = '\0';
}