ROBOT : connection.o main.o 
	g++ -o bin/ROBOT obj/main.o obj/connection.o -lbluetooth

main.o : src/IA/main.cpp connection.o 
	g++ -o obj/main.o -c src/IA/main.cpp 

connection.o : src/IA/connection.cpp
	g++ -o obj/connection.o -c src/IA/connection.cpp -lbluetooth

clean_bin:
	rm -rf bin/*

clean_obj:
	rm -rf obj/*