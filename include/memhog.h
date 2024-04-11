#pragma once

#ifndef MEMHOG_H
#define MEMHOG_H 1

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  /// @brief Gets the total memory available on the system (in bytes).
  /// @return The total system memory in bytes.
  extern size_t get_total_system_memory (void);

  /// @brief Allocates memory of the given size and fills it with random bytes.
  /// @param size The number of bytes to allocate.
  /// @return A pointer to the allocated memory, or `NULL` if allocation
  /// failed.
  extern uint8_t *hog_memory (size_t size);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MEMHOG_H */
