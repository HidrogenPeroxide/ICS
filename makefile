all: try.cpp
	g++ -o try try.cpp
	./try
clean:
	rm -f try