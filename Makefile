all:
	g++ src/reader.cpp -o bin/exe

run:
	./bin/exe

clean:
	rm bin/exe