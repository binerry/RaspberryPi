all: sipcall sipserv

sipcall: sipcall.c
	cc -o $@ $< `pkg-config --cflags --libs libpjproject`
	
sipserv: sipserv.c
	cc -o $@ $< `pkg-config --cflags --libs libpjproject`
	
clean:
	rm -rf sipcall
	rm -rf sipserv