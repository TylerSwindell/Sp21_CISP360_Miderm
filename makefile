# Compiles all .o files into Main run file
all: controllers functions
	if [ ! -d "./out/" ]; then mkdir out; fi;
	g++ *.o -o AirportApplication
	chmod u+x AirportApplication
	mv *.o out/
	./AirportApplication

# Compiles 'main' entry point file
controllers: 
	g++ -c Main/AirportApplication.cpp 

# Compiles function definition file
functions:
	g++ -c */*Functions.cpp
	g++ -c Utils/utilsTS.cpp

# Cleans up all compiled files in src folder 
clean:
	rm out/*.o AirportApplication
	rmdir out

again: clean
	make clean
	make