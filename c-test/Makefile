

driver: 
	gcc -o driver driver.c -ldl

plugin:
	gcc -fPIC -c code.c
	gcc -shared -Wl,-soname,plugin.so -o plugin.so code.o

clean:
	rm -f driver code.o plugin.so
