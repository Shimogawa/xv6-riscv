#ifndef K_SPINLOCK_H
#define K_SPINLOCK_H

#include "types.h"

// Mutual exclusion lock.
struct spinlock {
  uint locked; // Is the lock held?

  // For debugging:
  char* name;      // Name of lock.
  struct cpu* cpu; // The cpu holding the lock.
};

#endif // K_SPINLOCK_H
