#include "defs.h"
#include "memlayout.h"
#include "param.h"
#include "proc.h"
#include "riscv.h"
#include "spinlock.h"
#include "sysinfo.h"
#include "types.h"

uint64
sys_exit(void) {
  int n;
  argint(0, &n);
  exit(n);
  return 0; // not reached
}

uint64
sys_getpid(void) {
  return myproc()->pid;
}

uint64
sys_fork(void) {
  return fork();
}

uint64
sys_wait(void) {
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void) {
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void) {
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n) {
    if (killed(myproc())) {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void) {
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void) {
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// if enable trace for (1 << syscallnum) mask
uint64
sys_trace(void) {
  int mask;
  argint(0, &mask);
  myproc()->tracemask = mask;
  return 0;
}

uint64
sys_sysinfo(void) {
  uint64 info;
  argaddr(0, &info);
  return sysinfo(info);
}

uint64
sys_pgaccess(void) {
  uint64 va, buf;
  int numpg;
  argaddr(0, &va);
  argint(1, &numpg);
  argaddr(2, &buf);
  if (numpg <= 0)
    return -1;
  char bm[(numpg - 1) / 8 + 1];
  memset(bm, 0, (numpg - 1) / 8 + 1);
  pagetable_t pagetable = myproc()->pagetable;
  pte_t* pte;
  for (int i = 0; i < numpg; i++, va += PGSIZE) {
    pte = walk(pagetable, va, FALSE);
    if (pte == NULL)
      continue;
    if (*pte & PTE_A) {
      bm[i / 8] |= (1 << (i % 8));
      *pte &= ~PTE_A;
    }
  }
  return copyout(pagetable, buf, bm, (numpg - 1) / 8 + 1);
}

uint64
sys_sigalarm(void) {
  int ticks;
  uint64 handler_ptr;
  argint(0, &ticks);
  if (ticks < 0)
    return -1;
  argaddr(1, &handler_ptr);
  struct proc* p = myproc();
  p->alarmstat.handler = (void (*)())handler_ptr;
  p->alarmstat.interval = ticks;
  p->alarmstat.tickleft = ticks;
  return 0;
}

uint64
sys_sigreturn(void) {
  struct proc* p = myproc();
  memmove(p->trapframe, p->alarmstat.trapframe, sizeof(struct trapframe));
  p->alarmstat.tickleft = p->alarmstat.interval;
  return 0;
}
