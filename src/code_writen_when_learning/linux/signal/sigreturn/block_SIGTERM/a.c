#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

#include <ucontext.h>
#include <signal.h>

void Sigreturn_impl(ucontext_t context)
{
 //   syscall(__NR_rt_sigreturn);
    if (syscall(__NR_rt_sigreturn) == -1) {
	perror("When calling rt_sigreturn");
	exit(1);
    }
}

void Fflush()
{
    assert(fflush(stderr) == 0);
}

void Sigreturn(ucontext_t context)
{
    static int cnt = 0;

    assert(fprintf(stderr, "Invoke Sigreturn the %d time\n", ++cnt) == 28);
    Fflush();

    assert(cnt <= 2);
    assert(cnt > 0);
    if (cnt == 1) {
	assert(fprintf(stderr, "Start doing the real thing\n") == 27);
	Fflush();
        Sigreturn_impl(context);
    }
}

void Raise(int sig)
{
    assert(raise(sig) == 0);
}

_Noreturn void infinite_loop()
{
    assert(fprintf(stderr, "HAHA! Inside infinite loop\nAnd nobody can kill me!\nHAHA!\n") == 57);
    Fflush();

    for (int i = 0; 1; ++i) {
	assert(fprintf(stderr, "%d suicide attemption\n", i) >= 22);
	Fflush();
	Raise(SIGTERM);
    }
}

void setup_sigmask(sigset_t *sigmaskp)
{
    assert(sigfillset(sigmaskp) == 0);
}

ucontext_t Getcontext()
{
    ucontext_t uc;

    int ret = getcontext(&uc);

    if (ret == -1) {
	perror("When calling getcontext");
	exit(1);
    }
    
    return uc;
}

ucontext_t GetContextAndSetSigmask()
{
    ucontext_t uc = Getcontext();
    setup_sigmask(&uc.uc_sigmask);
    return uc;
}

int main(int argc, char *argv[])
{
    assert(printf("Invoke GetContextAndSetSigmask\n") == 31);
    Fflush();
    Sigreturn(GetContextAndSetSigmask());
    infinite_loop();

    // This line will never be touched
    return 1;
}
