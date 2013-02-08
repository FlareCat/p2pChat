server: server.c ../include/log.h
	gcc -o ../bin/server server.c -g

client: client.c ../include/log.h
	gcc -o ../bin/client client.c -g

.PHONY : clean
clean:
	rm -f ../bin/*
