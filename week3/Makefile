jsoncpp.o : json/json.h json/json-forwards.h jsoncpp.cpp
	g++ -std=c++11 -c jsoncpp.cpp

my_re.o : my_re.cpp
	g++ -std=c++11 -c my_re.cpp

my_lcs.o : my_lcs.cpp
	g++ -std=c++11 -c my_lcs.cpp

my_dist.o : my_dist.cpp
	g++ -std=c++11 -c my_dist.cpp

my_re : jsoncpp.o my_re.o
	g++ jsoncpp.o my_re.o -o my_re

my_dist : jsoncpp.o my_dist.o
	g++ jsoncpp.o my_dist.o -o my_dist

my_lcs : jsoncpp.o my_lcs.o
	g++ jsoncpp.o my_lcs.o -o my_lcs
