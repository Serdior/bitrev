	.text
	.globl	bitrev
	.type	bitrev, @function

bitrev:
        xor     %eax,%eax
	ret

	.size	bitrev, .-bitrev
