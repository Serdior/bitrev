#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

extern uint64_t bitrev(uint64_t);

int main(int argc, char **argv) {
  if (argc != 2)
    return EXIT_FAILURE;
  uint64_t arg = strtoul(argv[1], NULL, 16);
  if (errno)
    return EXIT_FAILURE;
  printf("0x%016"PRIX64"\n", bitrev(arg));
  return EXIT_SUCCESS;
}
