CC = g++
CFLAGS = -fopenmp

all: app2 app3 app4

app2: externo.cpp
	$(CC) $(CFLAGS) externo.cpp -o app2

app3: externo2.cpp
	$(CC) $(CFLAGS) externo2.cpp -o app3

app4: externo3.cpp
	$(CC) $(CFLAGS) externo3.cpp -o app4


clean:
	rm -f app2
	rm -f app3
	rm -f app4
