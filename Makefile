all:
	cd Caravel && make clean && make
	cd MidBox && make clean && make

clean:
	cd Caravel && make clean
	cd MidBox && make clean

MidBox:
	cd MidBox && ./MidBox