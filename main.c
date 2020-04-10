#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>
#include <sys/time.h>

extern uint64_t bitrev(uint64_t);

/* https://en.wikipedia.org/wiki/Xorshift#xorshift* */
static uint64_t random_u64(uint64_t *seed) {
  uint64_t x = *seed;
	x ^= x >> 12;
	x ^= x << 25;
	x ^= x >> 27;
	*seed = x;
	return x * 0x2545F4914F6CDD1DUL;
}

/* Only for testing. Such solution would get 0 points. */
static uint64_t bitrev_iter(uint64_t x) {
  uint64_t b, r = 0;
  for (int i = 0; i < 64; i++) {
    b = (x >> i) & 1;
    r |= b << (63 - i);
  }
  return r;
}

int main(int argc, char *argv[]) {
  static char buf[80];
  int ch, times = 0;

  while ((ch = getopt(argc, argv, "r:")) != -1) {
    if (ch == 'r') {
      times = strtol(optarg, NULL, 10);
      if (times < 0)
        return EXIT_FAILURE;
    } else {
      fprintf(stderr, "Usage: %s [-r TIMES] [NUMBER]\n", argv[0]);
      return EXIT_FAILURE;
    }
  }

  argc -= optind;
  argv += optind;

  if (times) {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    uint64_t seed = tv.tv_sec + tv.tv_usec * 1e6;

    for (int i = 0; i < times; i++) {
      uint64_t r = random_u64(&seed);
      if (bitrev(r) != bitrev_iter(r))
        return EXIT_FAILURE;
    }
  } else {
    if (argc > 1)
      return EXIT_FAILURE;
    if (argc == 0)
      if (fgets(buf, sizeof(buf), stdin) == NULL)
        return EXIT_FAILURE;
    uint64_t arg = strtoul(argc ? argv[0] : buf, NULL, 16);
    if (errno)
      return EXIT_FAILURE;
    uint64_t fast = bitrev(arg);
    printf("0x%016"PRIX64"\n", fast);
    if (fast != bitrev_iter(arg))
      return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
