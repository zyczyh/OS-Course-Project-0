        .text
.globl zfunction
zfunction:
        pushl   %ebp
        movl    %esp, %ebp
        andl	$0xff803fff, 8(%ebp)
        shll	$4, 8(%ebp)
        movl    8(%ebp), %eax
        leave
        ret
