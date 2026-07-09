*This project has been created as part of the 42 curriculum by mbichet.*

# Codexion

## Description

Codexion is a concurrency simulation written in C using POSIX Threads. Each coder is represented by a thread and repeatedly compiles, debugs and refactors while competing for shared USB dongles. The project focuses on thread synchronization, resource sharing, deadlock prevention, fair scheduling (FIFO/EDF), and precise burnout detection.

---

## Instructions

### Build

```bash
make
```

### Run

```bash
./codexion number_of_coders time_to_burnout time_to_compile \
time_to_debug time_to_refactor number_of_compiles_required \
dongle_cooldown scheduler
```

Example:

```bash
./codexion 6 400 100 100 100 10 10 edf
```

### Debug

```bash
valgrind --tool=helgrind ./codexion <arguments>
```

---

## Resources

- POSIX Threads: https://man7.org/linux/man-pages/man7/pthreads.7.html
- The Little Book of Semaphores
- Operating System Concepts (Silberschatz)
- Modern Operating Systems (Tanenbaum)

### AI usage

AI was only used to improve the README (grammar and formatting). No AI-generated code was used in the implementation.

---

## Blocking cases handled

- Deadlock prevention by alternating dongle acquisition order.
- Coffman conditions addressed to avoid circular waiting.
- Fair scheduling using a priority heap (FIFO or EDF).
- Mandatory dongle cooldown before reuse.
- Dedicated monitor thread for burnout detection.
- Serialized logging using a mutex to prevent mixed output.

---

## Thread synchronization mechanisms

- **`pthread_mutex_t`** protects dongles, coder states, the global stop flag, and logging.
- **`pthread_cond_t`** allows coders to wait efficiently for available dongles.
- A **priority heap** implements FIFO or EDF scheduling for each dongle.
- Shared data is always accessed while holding the appropriate mutex, preventing race conditions.
- The monitor safely communicates with coder threads through protected shared state and condition variable broadcasts.

---

## Project layout

```
.
├── README.md
├─── coders/
├─────── Makefile
└─────── src/

```