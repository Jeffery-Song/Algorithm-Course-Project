.PHONY: all 1 2 3 4 5 6
all: 1 2 3 4 5 6
1: random.cc
	g++ random.cc -std=c++11 -Din_size=1
	./a.out
2: random.cc
	g++ random.cc -std=c++11 -Din_size=2
	./a.out
3: random.cc
	g++ random.cc -std=c++11 -Din_size=3
	./a.out
4: random.cc
	g++ random.cc -std=c++11 -Din_size=4
	./a.out
5: random.cc
	g++ random.cc -std=c++11 -Din_size=5
	./a.out
6: random.cc
	g++ random.cc -std=c++11 -Din_size=6
	./a.out
clean:
	find . -name "*.txt" -exec rm -r {} \;
	rm a.out