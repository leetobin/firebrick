	.file	"serprog.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__ = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	setup_uart
	.type	setup_uart, @function
setup_uart:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	movw r18,r22
	movw r20,r24
	ldi r22,lo8(4000000)
	ldi r23,hi8(4000000)
	ldi r24,hlo8(4000000)
	ldi r25,hhi8(4000000)
	call __udivmodsi4
	subi r18,lo8(-(-1))
	sbci r19,hi8(-(-1))
	sbci r20,hlo8(-(-1))
	sbci r21,hhi8(-(-1))
	lsr r21
	ror r20
	ror r19
	ror r18
	mov r24,r19
	clr r25
	sbrc r24,7
	dec r25
	sts 197,r24
	sts 196,r18
	ldi r30,lo8(192)
	ldi r31,hi8(192)
	ld r24,Z
	ori r24,lo8(2)
	st Z,r24
	ldi r24,lo8(-104)
	sts 193,r24
	ldi r24,lo8(6)
	sts 194,r24
/* epilogue start */
	ret
	.size	setup_uart, .-setup_uart
.global	select_chip
	.type	select_chip, @function
select_chip:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	cbi 37-32,2
/* epilogue start */
	ret
	.size	select_chip, .-select_chip
.global	unselect_chip
	.type	unselect_chip, @function
unselect_chip:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	sbi 37-32,2
/* epilogue start */
	ret
	.size	unselect_chip, .-unselect_chip
.global	setup_spi
	.type	setup_spi, @function
setup_spi:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	cbi 37-32,2
	ldi r24,lo8(44)
	out 36-32,r24
	ldi r24,lo8(80)
	out 76-32,r24
	ldi r24,lo8(1)
	out 77-32,r24
/* epilogue start */
	ret
	.size	setup_spi, .-setup_spi
.global	readwrite_spi
	.type	readwrite_spi, @function
readwrite_spi:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	out 78-32,r24
.L6:
	in __tmp_reg__,77-32
	sbrs __tmp_reg__,7
	rjmp .L6
	in r24,78-32
/* epilogue start */
	ret
	.size	readwrite_spi, .-readwrite_spi
.global	putchar_uart
	.type	putchar_uart, @function
putchar_uart:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
.L10:
	lds r25,192
	sbrs r25,5
	rjmp .L10
	 ldi r25,lo8(53)
    1:dec r25
    brne 1b
	nop
	sts 198,r24
/* epilogue start */
	ret
	.size	putchar_uart, .-putchar_uart
.global	getchar_uart
	.type	getchar_uart, @function
getchar_uart:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
.L13:
	lds r24,192
	sbrs r24,7
	rjmp .L13
	lds r24,198
/* epilogue start */
	ret
	.size	getchar_uart, .-getchar_uart
.global	word_uart
	.type	word_uart, @function
word_uart:
	push r14
	push r15
	push r28
	push r29
/* prologue: function */
/* frame size = 0 */
/* stack size = 4 */
.L__stack_usage = 4
	mov r14,r24
	movw r28,r14
	movw r14,r28
	mov r15,r25
	movw r28,r14
	ldi r18,lo8(0)
	ldi r19,hi8(0)
.L16:
	movw r30,r24
	ld __tmp_reg__,Z+
	tst __tmp_reg__
	brne .-6
	sbiw r30,1
	sub r30,r24
	sbc r31,r25
	cp r18,r30
	cpc r19,r31
	brsh .L20
	ld r21,Y+
.L17:
	lds r20,192
	sbrs r20,5
	rjmp .L17
	 ldi r20,lo8(53)
    1:dec r20
    brne 1b
	nop
	sts 198,r21
	subi r18,lo8(-(1))
	sbci r19,hi8(-(1))
	rjmp .L16
.L20:
/* epilogue start */
	pop r29
	pop r28
	pop r15
	pop r14
	ret
	.size	word_uart, .-word_uart
.global	get24_le
	.type	get24_le, @function
get24_le:
	push r14
	push r15
	push r16
	push r17
/* prologue: function */
/* frame size = 0 */
/* stack size = 4 */
.L__stack_usage = 4
.L22:
	lds r24,192
	sbrs r24,7
	rjmp .L22
	lds r24,198
	clr r25
	sbrc r24,7
	com r25
	mov r26,r25
	mov r27,r25
.L23:
	lds r18,192
	sbrs r18,7
	rjmp .L23
	lds r14,198
	clr r15
	sbrc r14,7
	com r15
	mov r16,r15
	mov r17,r15
	mov r17,r16
	mov r16,r15
	mov r15,r14
	clr r14
.L24:
	lds r18,192
	sbrs r18,7
	rjmp .L24
	lds r18,198
	clr r19
	sbrc r18,7
	com r19
	mov r20,r19
	mov r21,r19
	movw r20,r18
	clr r19
	clr r18
	or r18,r14
	or r19,r15
	or r20,r16
	or r21,r17
	or r18,r24
	or r19,r25
	or r20,r26
	or r21,r27
	movw r22,r18
	movw r24,r20
/* epilogue start */
	pop r17
	pop r16
	pop r15
	pop r14
	ret
	.size	get24_le, .-get24_le
	.data
.LC0:
	.string	"serprog-duino"
	.text
.global	handle_command
	.type	handle_command, @function
handle_command:
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
	push r16
	push r17
/* prologue: function */
/* frame size = 0 */
/* stack size = 8 */
.L__stack_usage = 8
	cpi r24,lo8(4)
	brne .+2
	rjmp .L76
	cpi r24,lo8(5)
	brsh .+2
	rjmp .L128
	cpi r24,lo8(16)
	brne .+2
	rjmp .L77
	cpi r24,lo8(17)
	brsh .+2
	rjmp .L129
	cpi r24,lo8(18)
	brne .+2
	rjmp .L80
	cpi r24,lo8(19)
	breq .+2
	rjmp .L28
/* #APP */
 ;  239 "serprog.c" 1
	cli
 ;  0 "" 2
/* #NOAPP */
.L58:
	lds r24,192
	sbrs r24,7
	rjmp .L58
	lds r24,198
	clr r25
	sbrc r24,7
	com r25
	mov r26,r25
	mov r27,r25
.L59:
	lds r18,192
	sbrs r18,7
	rjmp .L59
	lds r14,198
	clr r15
	sbrc r14,7
	com r15
	mov r16,r15
	mov r17,r15
	mov r17,r16
	mov r16,r15
	mov r15,r14
	clr r14
.L60:
	lds r18,192
	sbrs r18,7
	rjmp .L60
	lds r18,198
	clr r19
	sbrc r18,7
	com r19
	mov r20,r19
	mov r21,r19
	movw r20,r18
	clr r19
	clr r18
	or r18,r14
	or r19,r15
	or r20,r16
	or r21,r17
	or r18,r24
	or r19,r25
	or r20,r26
	or r21,r27
.L61:
	lds r24,192
	sbrs r24,7
	rjmp .L61
	lds r10,198
	clr r11
	sbrc r10,7
	com r11
	mov r12,r11
	mov r13,r11
.L62:
	lds r24,192
	sbrs r24,7
	rjmp .L62
	lds r14,198
	clr r15
	sbrc r14,7
	com r15
	mov r16,r15
	mov r17,r15
	mov r17,r16
	mov r16,r15
	mov r15,r14
	clr r14
.L63:
	lds r24,192
	sbrs r24,7
	rjmp .L63
	lds r24,198
	clr r25
	sbrc r24,7
	com r25
	mov r26,r25
	mov r27,r25
	movw r26,r24
	clr r25
	clr r24
	or r24,r14
	or r25,r15
	or r26,r16
	or r27,r17
	or r24,r10
	or r25,r11
	or r26,r12
	or r27,r13
	cbi 37-32,2
	cp r18,__zero_reg__
	cpc r19,__zero_reg__
	cpc r20,__zero_reg__
	cpc r21,__zero_reg__
	breq .L82
.L125:
	lds r22,192
	sbrs r22,7
	rjmp .L125
	lds r22,198
	out 78-32,r22
.L66:
	in __tmp_reg__,77-32
	sbrs __tmp_reg__,7
	rjmp .L66
	in r22,78-32
	subi r18,lo8(-(-1))
	sbci r19,hi8(-(-1))
	sbci r20,hlo8(-(-1))
	sbci r21,hhi8(-(-1))
	brne .L125
.L82:
	lds r18,192
	sbrs r18,5
	rjmp .L82
	 ldi r30,lo8(53)
    1:dec r30
    brne 1b
	nop
	ldi r18,lo8(6)
	sts 198,r18
	sbiw r24,0
	cpc r26,__zero_reg__
	cpc r27,__zero_reg__
	breq .L69
.L81:
	out 78-32,__zero_reg__
.L70:
	in __tmp_reg__,77-32
	sbrs __tmp_reg__,7
	rjmp .L70
	in r19,78-32
.L71:
	lds r18,192
	sbrs r18,5
	rjmp .L71
	 ldi r31,lo8(53)
    1:dec r31
    brne 1b
	nop
	sts 198,r19
	sbiw r24,1
	sbc r26,__zero_reg__
	sbc r27,__zero_reg__
	brne .L81
.L69:
	sbi 37-32,2
/* #APP */
 ;  257 "serprog.c" 1
	sei
 ;  0 "" 2
/* #NOAPP */
	rjmp .L28
.L76:
	lds r24,192
	sbrs r24,5
	rjmp .L76
	 ldi r24,lo8(53)
    1:dec r24
    brne 1b
	nop
	ldi r24,lo8(6)
	sts 198,r24
.L52:
	lds r24,192
	sbrs r24,5
	rjmp .L52
	 ldi r30,lo8(53)
    1:dec r30
    brne 1b
	nop
	ldi r24,lo8(-1)
	sts 198,r24
.L53:
	lds r24,192
	sbrs r24,5
	rjmp .L53
	 ldi r31,lo8(53)
    1:dec r31
    brne 1b
	nop
	ldi r24,lo8(-1)
	sts 198,r24
	rjmp .L28
.L128:
	cpi r24,lo8(1)
	breq .L84
	cpi r24,lo8(1)
	brsh .+2
	rjmp .L85
	cpi r24,lo8(2)
	brne .+2
	rjmp .L86
	cpi r24,lo8(3)
	breq .+2
	rjmp .L28
.L87:
	lds r24,192
	sbrs r24,5
	rjmp .L87
	 ldi r24,lo8(53)
    1:dec r24
    brne 1b
	nop
	ldi r24,lo8(6)
	sts 198,r24
	ldi r18,lo8(0)
	ldi r19,hi8(0)
	ldi r24,lo8(0)
	ldi r25,hi8(0)
.L49:
	subi r18,lo8(-(.LC0))
	sbci r19,hi8(-(.LC0))
	movw r30,r18
	ld r19,Z
.L48:
	lds r18,192
	sbrs r18,5
	rjmp .L48
	 ldi r31,lo8(53)
    1:dec r31
    brne 1b
	nop
	sts 198,r19
	adiw r24,1
	movw r18,r24
	cpi r24,13
	cpc r25,__zero_reg__
	brne .L49
	ldi r24,lo8(3)
	ldi r25,hi8(3)
.L124:
	lds r18,192
	sbrs r18,5
	rjmp .L124
	 ldi r18,lo8(53)
    1:dec r18
    brne 1b
	nop
	sts 198,__zero_reg__
	sbiw r24,1
	brne .L124
	rjmp .L28
.L84:
	lds r24,192
	sbrs r24,5
	rjmp .L84
	 ldi r24,lo8(53)
    1:dec r24
    brne 1b
	nop
	ldi r24,lo8(6)
	sts 198,r24
.L41:
	lds r24,192
	sbrs r24,5
	rjmp .L41
	 ldi r30,lo8(53)
    1:dec r30
    brne 1b
	nop
	ldi r24,lo8(1)
	sts 198,r24
.L42:
	lds r24,192
	sbrs r24,5
	rjmp .L42
	 ldi r31,lo8(53)
    1:dec r31
    brne 1b
	nop
	sts 198,__zero_reg__
	rjmp .L28
.L85:
	lds r24,192
	sbrs r24,5
	rjmp .L85
.L126:
	 ldi r18,lo8(53)
    1:dec r18
    brne 1b
	nop
	ldi r24,lo8(6)
	sts 198,r24
	rjmp .L28
.L77:
	lds r24,192
	sbrs r24,5
	rjmp .L77
	 ldi r30,lo8(53)
    1:dec r30
    brne 1b
	nop
	ldi r24,lo8(21)
	sts 198,r24
.L55:
	lds r24,192
	sbrs r24,5
	rjmp .L55
	 ldi r31,lo8(53)
    1:dec r31
    brne 1b
	nop
	ldi r24,lo8(6)
	sts 198,r24
	rjmp .L28
.L129:
	cpi r24,lo8(5)
	breq .L83
.L28:
/* epilogue start */
	pop r17
	pop r16
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	ret
.L83:
	lds r24,192
	sbrs r24,5
	rjmp .L83
	 ldi r18,lo8(53)
    1:dec r18
    brne 1b
	nop
	ldi r24,lo8(6)
	sts 198,r24
.L54:
	lds r24,192
	sbrs r24,5
	rjmp .L54
	 ldi r24,lo8(53)
    1:dec r24
    brne 1b
	nop
	ldi r24,lo8(8)
	sts 198,r24
	rjmp .L28
.L80:
	lds r24,192
	sbrs r24,7
	rjmp .L80
	lds r24,198
	cpi r24,lo8(8)
	brne .+2
	rjmp .L78
.L79:
	lds r24,192
	sbrs r24,5
	rjmp .L79
	 ldi r24,lo8(53)
    1:dec r24
    brne 1b
	nop
	ldi r24,lo8(21)
	sts 198,r24
	rjmp .L28
.L86:
	lds r24,192
	sbrs r24,5
	rjmp .L86
	 ldi r18,lo8(53)
    1:dec r18
    brne 1b
	nop
	ldi r24,lo8(6)
	sts 198,r24
.L43:
	lds r24,192
	sbrs r24,5
	rjmp .L43
	 ldi r24,lo8(53)
    1:dec r24
    brne 1b
	nop
	ldi r24,lo8(63)
	sts 198,r24
.L44:
	lds r24,192
	sbrs r24,5
	rjmp .L44
	 ldi r30,lo8(53)
    1:dec r30
    brne 1b
	nop
	sts 198,__zero_reg__
.L45:
	lds r24,192
	sbrs r24,5
	rjmp .L45
	 ldi r31,lo8(53)
    1:dec r31
    brne 1b
	nop
	ldi r24,lo8(13)
	sts 198,r24
	ldi r24,lo8(29)
	ldi r25,hi8(29)
.L123:
	lds r18,192
	sbrs r18,5
	rjmp .L123
	 ldi r18,lo8(53)
    1:dec r18
    brne 1b
	nop
	sts 198,__zero_reg__
	sbiw r24,1
	brne .L123
	rjmp .L28
.L78:
	lds r24,192
	sbrc r24,5
	rjmp .L126
	lds r24,192
	sbrs r24,5
	rjmp .L78
	rjmp .L126
	.size	handle_command, .-handle_command
.global	__vector_18
	.type	__vector_18, @function
__vector_18:
	push __zero_reg__
	push r0
	in r0,__SREG__
	push r0
	clr __zero_reg__
	push r18
	push r19
	push r20
	push r21
	push r22
	push r23
	push r24
	push r25
	push r26
	push r27
	push r30
	push r31
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 15 */
.L__stack_usage = 15
	lds r24,198
	call handle_command
/* epilogue start */
	pop r31
	pop r30
	pop r27
	pop r26
	pop r25
	pop r24
	pop r23
	pop r22
	pop r21
	pop r20
	pop r19
	pop r18
	pop r0
	out __SREG__,r0
	pop r0
	pop __zero_reg__
	reti
	.size	__vector_18, .-__vector_18
.global	main
	.type	main, @function
main:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	sts 197,__zero_reg__
	sts 196,__zero_reg__
	lds r24,192
	ori r24,lo8(2)
	sts 192,r24
	ldi r24,lo8(-104)
	sts 193,r24
	ldi r24,lo8(6)
	sts 194,r24
	cbi 37-32,2
	ldi r24,lo8(44)
	out 36-32,r24
	ldi r24,lo8(80)
	out 76-32,r24
	ldi r24,lo8(1)
	out 77-32,r24
/* #APP */
 ;  273 "serprog.c" 1
	sei
 ;  0 "" 2
/* #NOAPP */
.L132:
	rjmp .L132
	.size	main, .-main
.global __do_copy_data
