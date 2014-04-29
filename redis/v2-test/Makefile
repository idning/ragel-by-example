all: redis.png redis.out

%.out: %.rl
	ragel $*.rl
	rm -f $*.ri
	indent -npro -kr -i4 -ts4 -sob -l120 -ss -ncs -cp1 --no-tabs -di16 -psl $*.c
	cc $*.c -o $*.out

%.png: %.rl
	ragel -V -p $*.rl | dot -Tpng -o $@


clean:
	rm *.out

	
