
typedef struct Timer_struct {
    unsigned int start_time;
    void         (*start)       (struct Timer_struct *t);
    unsigned int (*time_passed) (struct Timer_struct *t);
} Timer;

void Timer_start (Timer *t);
unsigned int Timer_time_passed (Timer *t);
Timer Timer_new ();
