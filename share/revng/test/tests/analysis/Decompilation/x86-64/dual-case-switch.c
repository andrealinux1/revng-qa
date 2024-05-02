/*
 * This file is distributed under the MIT License. See LICENSE.md for details.
 */

#define WEAK __attribute__((weak))

WEAK void report(int code) {
}

WEAK int random(int arg) {
  return arg;
}

/// With this function we want to enforce the creation of an exit dispatcher
/// with two `case`s following the `while (arg1)` loop. The `switch` to `if`
/// beautify pass, should then create operate in order to reconstruct an `if`.

WEAK int f(int arg1) {
  int return_value;

  if (arg1 == 50) {

  // This forward edge is needed in order to avoid the inlining the blocks
  // following the loop inside the region representing the loop (early successor
  // inlining)
    goto LABEL_EXIT_1;
  }

  while (arg1 > 0) {
    if (arg1 == 1) {
      return_value = 10;
      report(1);

      // This `goto` is used in order to reach one of the successors of the loop
      goto LABEL_EXIT_1;
    } else if (arg1 == 2) {
      return_value = 20;
      report(2);

      // This `goto` is used in order to reach the other successor of the loop
      goto LABEL_EXIT_2;
    }
    report(arg1);
    arg1 = random(arg1);
  }

LABEL_EXIT_1:
  report(1);
  goto LABEL_EXIT_COMMON;

LABEL_EXIT_2:
  report(2);

LABEL_EXIT_COMMON:
  return return_value;
}

WEAK void _start() {
  f(1);
}
