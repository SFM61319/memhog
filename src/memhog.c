#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif /* WIN32 */

#include "memhog.h"

static size_t const BYTE_RANGE_LENGTH = 1 << __CHAR_BIT__;

static void
fill_with_rand (uint8_t *const ptr, size_t const size)
{
  srand (time (NULL));

  size_t i;
  for (i = 0; i < size; i++)
    {
      ptr[i] = (uint8_t)(rand () % BYTE_RANGE_LENGTH);
    }
}

size_t
get_total_system_memory (void)
{
#ifdef WIN32
  MEMORYSTATUSEX status;

  status.dwLength = sizeof (status);
  GlobalMemoryStatusEx (&status);

  return (size_t)status.ullTotalPhys;
#else
  return (size_t)sysconf (_SC_PHYS_PAGES) * (size_t)sysconf (_SC_PAGE_SIZE);
#endif /* WIN32 */
}

uint8_t *
hog_memory (size_t const size)
{
  uint8_t *const ptr = (uint8_t *)malloc (size);
  if (ptr != NULL)
    {
      fill_with_rand (ptr, size);
    }

  return ptr;
}
