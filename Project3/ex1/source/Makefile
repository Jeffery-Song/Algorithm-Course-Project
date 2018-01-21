blackred12:
	g++ -std=c++11 Tree.cc -Dnumber=12
	./a.out
blackred24:
	g++ -std=c++11 Tree.cc -Dnumber=24
	./a.out
blackred36:
	g++ -std=c++11 Tree.cc -Dnumber=36
	./a.out
blackred48:
	g++ -std=c++11 Tree.cc -Dnumber=48
	./a.out
blackred60:
	g++ -std=c++11 Tree.cc -Dnumber=60
	./a.out
select12:
	g++ -std=c++11 select.cc -Dnumber=12
	./a.out
select24:
	g++ -std=c++11 select.cc -Dnumber=24
	./a.out
select36:
	g++ -std=c++11 select.cc -Dnumber=36
	./a.out
select48:
	g++ -std=c++11 select.cc -Dnumber=48
	./a.out
select60:
	g++ -std=c++11 select.cc -Dnumber=60
	./a.out
runall:
	for k in 12 24 36 48 60; do \
		g++ -std=c++11 Tree.cc -Dnumber=$$k; \
		./a.out; \
		g++ -std=c++11 select.cc -Dnumber=$$k; \
		./a.out; \
	done
random:
	g++ -std=c++11 ../input/random.cc -o ../input/a.out
	../input/a.out
	mv input.txt ../input/input.txt
