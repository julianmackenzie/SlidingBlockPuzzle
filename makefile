slidingBlock : slidingBlock.cpp Grid.h Piece.h Movement.h 
	g++ -std=c++11 -o slidingBlock -g -O2 -fsanitize=undefined -fsanitize=leak -fsanitize=address slidingBlock.cpp

clean:
	rm -f slidingBlock *.o

