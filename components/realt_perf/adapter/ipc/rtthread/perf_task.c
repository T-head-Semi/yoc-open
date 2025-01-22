#include "perf_ipc.h"
#include "rtthread.h"

perf_err_t perf_thread_yield(void)
{
    if(rt_thread_yield() == RT_EOK)
    {
        return PERF_OK;
    }
    return PERF_ERROR;
}

void perf_task_switch_sethook(perf_task_switch_hook hook)
{
    rt_scheduler_switch_sethook((void(*)(rt_thread_t))hook);
}
