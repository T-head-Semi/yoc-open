# dump the task info for rhino RTOS
# please file the elf before use this script
set height 0

define paddr
  # print current info
  i r
  p *g_active_task[0]
  bt

  # store the register
  set $gdb_x0  = $x0
  set $gdb_x1  = $x1
  set $gdb_x3  = $x3
  set $gdb_x4  = $x4
  set $gdb_x5  = $x5
  set $gdb_x6  = $x6
  set $gdb_x7  = $x7
  set $gdb_x8  = $x8
  set $gdb_x9  = $x9
  set $gdb_x10 = $x10
  set $gdb_x11 = $x11
  set $gdb_x12 = $x12
  set $gdb_x13 = $x13
  set $gdb_x14 = $x14
  set $gdb_x15 = $x15
  set $gdb_x16 = $x16
  set $gdb_x17 = $x17
  set $gdb_x18 = $x18
  set $gdb_x19 = $x19
  set $gdb_x20 = $x20
  set $gdb_x21 = $x21
  set $gdb_x22 = $x22
  set $gdb_x23 = $x23
  set $gdb_x24 = $x24
  set $gdb_x25 = $x25
  set $gdb_x26 = $x26
  set $gdb_x27 = $x27
  set $gdb_x28 = $x28
  set $gdb_x29 = $x29
  set $gdb_x30 = $x30
  set $gdb_x31 = $x31
  set $gdb_mcause = $mcause
  set $gdb_pc  = $pc
  set $gdb_sp  = $x2

  # get list offset
  set $gdb_offset = (unsigned long)((unsigned long)&g_active_task[0]->task_stats_item - (unsigned long)g_active_task[0])

  # get tcb addr
  set $gdb_tcb_addr = (ktask_t *)((unsigned long)(klist_t *)(&g_kobj_list.task_head)->next - $gdb_offset)
  
  # get task name
  set $gdb_task_name = ((ktask_t *)($gdb_tcb_addr))->task_name
  set $gdb_i = 0

  while (&($gdb_tcb_addr->task_stats_item) != &g_kobj_list.task_head)

    # print the task info
    p $gdb_i
    p $gdb_task_name
    p *$gdb_tcb_addr

    # set register to restore the task 
    set $x1  = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 0)
    set $x3  = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 4)
    set $x4  = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 8)
    set $x5  = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 12)
    set $x6  = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 16)
    set $x7  = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 20)
    set $x8  = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 24)
    set $x9  = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 28)
    set $x10 = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 32)
    set $x11 = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 36)
    set $x12 = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 40)
    set $x13 = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 44)
    set $x14 = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 48)
    set $x15 = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 52)
    set $x16 = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 56)
    set $x17 = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 60)
    set $x18 = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 64)
    set $x19 = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 68)
    set $x20 = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 72)
    set $x21 = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 76)
    set $x22 = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 80)
    set $x23 = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 84)
    set $x24 = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 88)
    set $x25 = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 92)
    set $x26 = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 96)
    set $x27 = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 100)
    set $x28 = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 104)
    set $x29 = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 108)
    set $x30 = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 112)
    set $x31 = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 116)
    set $pc  = *(unsigned long *)((unsigned long)$gdb_tcb_addr->task_stack + 120)
    set $sp = (unsigned long)($gdb_tcb_addr->task_stack) + 124

    # print the task stack backtrace
    bt
    shell sleep 1

    # go to next task
    set $gdb_i = $gdb_i + 1
    set $gdb_tcb_addr = (ktask_t *) ((unsigned long)$gdb_tcb_addr->task_stats_item - $gdb_offset)
    set $gdb_task_name = ((ktask_t *)($gdb_tcb_addr))->task_name
  end

  # restore the register
  set  $x0 = $gdb_x0 
  set  $x1 = $gdb_x1 
  set  $x3 = $gdb_x3 
  set  $x4 = $gdb_x4 
  set  $x5 = $gdb_x5 
  set  $x6 = $gdb_x6 
  set  $x7 = $gdb_x7 
  set  $x8 = $gdb_x8 
  set  $x9 = $gdb_x9 
  set  $x10 = $gdb_x10
  set  $x11 = $gdb_x11
  set  $x12 = $gdb_x12
  set  $x13 = $gdb_x13
  set  $x14 = $gdb_x14
  set  $x15 = $gdb_x15
  set  $x16 = $gdb_x16
  set  $x17 = $gdb_x17
  set  $x18 = $gdb_x18
  set  $x19 = $gdb_x19
  set  $x20 = $gdb_x20
  set  $x21 = $gdb_x21
  set  $x22 = $gdb_x22
  set  $x23 = $gdb_x23
  set  $x24 = $gdb_x24
  set  $x25 = $gdb_x25
  set  $x26 = $gdb_x26
  set  $x27 = $gdb_x27
  set  $x28 = $gdb_x28
  set  $x29 = $gdb_x29
  set  $x30 = $gdb_x30
  set  $x31 = $gdb_x31
  set  $mcause = $gdb_mcause
  set  $pc = $gdb_pc 
  set  $sp = $gdb_sp
end

paddr
