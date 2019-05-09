me_classifier : main.o genome.o gene.o item.o transcript.o
	g++ -o me_classifier main.o genome.o gene.o item.o transcript.o

main.o : main.cc
	g++ -c main.cc

genome.o : genome.cc genome.h
	g++ -c genome.cc

gene.o : gene.cc gene.h util.h
	g++ -c gene.cc

item.o : item.cc item.h
	g++ -c item.cc

transcript.o : transcript.cc transcript.h
	g++ -c transcript.cc
clean: 
	rm *.o me_classifier
