CC = g++
CFLAGS = -fopenmp

all: app2 app3

app2: externo.cpp
	$(CC) $(CFLAGS) externo.cpp -o app2

app3: externo2.cpp
	$(CC) $(CFLAGS) externo2.cpp -o app3

clean:
	rm -f app2
	rm -f app3
