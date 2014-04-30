ragel-by-example


官方例子::

    atoi.rl    比较好懂, 不过不适合入门
    awkemu.rl  适合入门
    params.rl

    clang.rl
    concurrent.rl
    cppscan.rl
    format.rl
    gotocallret.rl
    mailbox.rl
    pullscan.rl
    rlscan.rl
    statechart.rl

首先看awkemu.rl
===============

params.rl
=========

很好的一个例子, 解析命令行参数::

	help = ( '-h' | '-H' | '-?' | '--help' ) 0 @help;
	version = ( '-v' | '--version' ) 0 @version;
	output = '-o' 0? string 0 @output;
	spec = '-S' 0? string 0 @spec;
	mach = '-M' 0? string 0 @mach;

	main := (
		help |
		version |
		output |
		spec |
		mach
	)*;

示范了 access的用法::

	access fsm->;

clang.rl
========

    ning@ning-laptop:~/idning-source/c/ragel-6.8/examples$ ./clang
    a = 3;
    int f(){ b = 8; }
    ident(1): a
    symbol(1): =
    int(1): 3
    symbol(1): ;
    ident(2): int
    ident(2): f
    symbol(2): (
    symbol(2): )
    symbol(2): {
    ident(2): b
    symbol(2): =
    int(2): 8
    symbol(2): ;
    symbol(2): }

redis解析的例子
===============


