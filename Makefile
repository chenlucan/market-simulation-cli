BOOST_INCLUDE = vendor/boost_1_58_0/include
BOOST_LIB     = vendor/boost_1_58_0/lib

SRC_INCLUDE = src

INCL = -I"$(BOOST_INCLUDE)" -I"$(SRC_INCLUDE)"  
LINK = -L"$(BOOST_LIB)" -lboost_system -lboost_date_time
FLAG = -std=c++11
CC   = g++

.PHONY: all
all: generate

.PHONY : clean
clean:
	-rm generate

generate:
	$(CC)  src/generate/*.cc -o generate  $(INCL) $(LINK) $(FLAG)
