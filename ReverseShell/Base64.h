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

#ifndef BASE64_H
#define BASE64_H

#include <Arduino.h>

/**
 * @brief Lightweight Base64 encoder for Arduino / Teensy.
 *
 * Designed for embedded systems:
 *  - No dynamic allocation
 *  - No STL
 *  - Deterministic memory usage
 *  - Small flash footprint
 *
 * Usage:
 *   size_t outLen = Base64::encodedLength(inputLen);
 *   char output[outLen + 1];
 *   Base64::encode(output, input, inputLen);
 */
class Base64
{
public:

    /**
     * @brief Calculate required Base64 output length.
     *
     * @param inputLength Length of input buffer in bytes
     * @return Required encoded length (without null terminator)
     */
    static size_t encodedLength(size_t inputLength);

    /**
     * @brief Encode a buffer into Base64.
     *
     * @param output Output buffer (must be at least encodedLength(inputLength) + 1)
     * @param input  Input buffer
     * @param inputLength Length of input buffer
     */
    static void encode(char* output, char* input, size_t inputLength);
};

#endif