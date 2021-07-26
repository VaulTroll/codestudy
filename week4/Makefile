jsoncpp.o : json/json.h json/json-forwards.h jsoncpp.cpp
	g++ -std=c++11 -c jsoncpp.cpp

my_tfidf.o : my_tfidf.cpp
	g++ -std=c++11 -c my_tfidf.cpp

my_tfidf : jsoncpp.o my_tfidf.o
	g++ jsoncpp.o my_tfidf.o -o my_tfidf