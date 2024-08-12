all: lib/libgeo.so bin/geo.exe

bin/geo.exe: obj/geometric.o obj/app.o
	g++ obj/geometric.o obj/app.o -o bin/geo.exe

obj/geometric.o: src/geometric.cpp
	g++ -c src/geometric.cpp -o obj/geometric.o

obj/app.o:app/app.cpp
	g++ -c app/app.cpp -o obj/app.o

lib/libgeo.so: src/geometric.cpp geometric.hpp
	g++ --shared src/geometric.cpp -o lib/libgeo.so -I include

test: bin/test.exe
	g++ obj/test.o -o bin/test.exe

obj/test.o: test/test.cpp
	g++ -c test/test.cpp -o obj/test.o

clean:
	rm -rf lib/* obj/* bin/*

