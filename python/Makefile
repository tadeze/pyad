PP=g++
INCLUDES=./Eigen/
PFLAGS=--std=c++11 -Wall -Werror -g  
all: iforest.exe
%.o: %.cpp %.hpp
	$(PP) $(PFLAGS) -I $(INCLUDES) -c $< -o $@
iforest.exe: Forest.o IsolationForest.o Tree.o utility.o FacadeForest.o main.o 
	$(PP) $(PFLAGS) -L$(INCLUDES) -o iforest.exe  Forest.o IsolationForest.o Tree.o utility.o FacadeForest.o  main.o 
fresh:
	make clean
	make all
clean:
	rm -rf *.o*
	rm -rf *.exe
	rm -rf C/*.o*
	rm -rf C/*.exe
