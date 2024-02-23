#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <inttypes.h>
#include <sys/queue.h>

// Define the number of timers and the maximum random time in milliseconds
#define NUM_TIMERS 10
#define MAX_RANDOM_TIME_MS 20000

// Enumeration for timer callback return values
enum timer_callback_retval {
    CB_RETURN_NORMAL = 0,
    CB_RETURN_FREE_TIMER,
    CB_RETURN_INVALID,
};

// Enumeration for timer types
enum timer_type {
    TT_RELATIVE = 0,
    TT_ABSOLUTE,
    TT_INVALID,
};

// Define a linked list structure for timers
TAILQ_HEAD(timer_list, timer_node);

// Global variable for the tick count
uint64_t tick_cnt = 0;

// Structure to represent a timer node
struct timer_node {
    TAILQ_ENTRY(timer_node) entries;
    uint64_t fire;               // Monotonic fire time
    int (*cb)(void* user_data);  // Callback function
    void* user_data;             // User data for the callback
};

// Lists to manage active and free timers
struct timer_list active_timers;
struct timer_list free_timers;
struct timer_node* timer_memory;

// Function to free a timer
static void free_timer(struct timer_node* timer) {
    TAILQ_INSERT_HEAD(&free_timers, timer, entries);
}

// Function to allocate a timer
static struct timer_node* alloc_timer(void) {
    struct timer_node* np;
    if (TAILQ_EMPTY(&free_timers)) return NULL;
    np = TAILQ_FIRST(&free_timers);
    TAILQ_REMOVE(&free_timers, np, entries);
    return np;
}

// Function to arm a timer
static void arm_timer(struct timer_node* timer) {
    struct timer_node* np;

    if (TAILQ_EMPTY(&active_timers)) {
        TAILQ_INSERT_HEAD(&active_timers, timer, entries);
    } else {
        for (np = TAILQ_FIRST(&active_timers); np; np = TAILQ_NEXT(np, entries)) {
            if (timer->fire < np->fire) {
                TAILQ_INSERT_BEFORE(np, timer, entries);
                return;
            }
        }
        TAILQ_INSERT_TAIL(&active_timers, timer, entries);
    }
}

// Function to disarm a timer
static void disarm_timer(struct timer_node* timer) {
    TAILQ_REMOVE(&active_timers, timer, entries);
}

// Function to set timer attributes
static int set_timer(struct timer_node* timer, enum timer_type tt, uint64_t fire, int (*cb)(void*), void* user_data) {
    switch (tt) {
        case TT_RELATIVE:
            fire += tick_cnt;
            break;
        case TT_ABSOLUTE:
            break;
        case TT_INVALID:
        default:
            return -1;
    }
    timer->fire = fire;
    timer->cb = cb;
    timer->user_data = user_data;
    return 0;
}

// Function to initialize the timer subsystem
static void init_timers(void) {
    unsigned i;
    TAILQ_INIT(&active_timers);
    TAILQ_INIT(&free_timers);
    if ((timer_memory = malloc(sizeof(struct timer_node) * NUM_TIMERS)) == NULL) {
        perror("Fatal! Can't allocate our block of timers!");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < NUM_TIMERS; i++) {
        free_timer(&timer_memory[i]);
    }
}

// Function to handle clock ticks
static void clock_tick(int signo) {
    struct timer_node* np;
    tick_cnt++;
    while (!TAILQ_EMPTY(&active_timers) && (np = TAILQ_FIRST(&active_timers)) && np->fire <= tick_cnt) {
        disarm_timer(np);
        if (np->cb(np->user_data) == CB_RETURN_FREE_TIMER) free_timer(np);
    }
}

// Function to initialize the ticker for clock ticks
static int init_ticker(unsigned ms) {
    struct itimerval it;
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = ms * 1000;
    it.it_interval = it.it_value = tv;
    signal(SIGALRM, clock_tick);
    return setitimer(ITIMER_REAL, &it, NULL);
}

// User timer callback function
int tcb(void* data) {
    struct timer_node* np = data;
    printf("Timer Callback: %lu\n", np->fire);
    return CB_RETURN_FREE_TIMER;
}

// Function to set up timers
static void setup_timers(void) {
    struct timer_node* np;
    int i;
    init_timers();
    init_ticker(1);

    for (i = 0; i < NUM_TIMERS; i++) {
        if ((np = alloc_timer()) == NULL) {
            perror("Fatal! We ran out of timers?");
            exit(EXIT_FAILURE);
        }
        if (set_timer(np, 0, (rand() + 1) % MAX_RANDOM_TIME_MS, tcb, np) == -1) {
            perror("Fatal! Bad timer set!");
            exit(EXIT_FAILURE);
        }
        arm_timer(np);
    }
}

// Function to add a delay in milliseconds
static void msleep(unsigned int msecs) {
    struct timeval tv;
    tv.tv_sec = msecs / 1000;
    tv.tv_usec = (msecs % 1000) * 1000;
    select(0, NULL, NULL, NULL, &tv);
}

int main(int argc, char* argv[]) {

    setup_timers();	//Implemented a separate function to setup the timers to simplify main()

    while (1) {
        // Instead of using sleep, we use msleep to introduce a delay
        msleep(100); // Wait for 100 milliseconds
    }

    return 0;
}

