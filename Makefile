BOOST_INCLUDE = vendor/boost_1_58_0/include
BOOST_LIB     = vendor/boost_1_58_0/lib

GTEST_INCLUDE = vendor/gtest-1.7.0/include
GTEST_LIB     = vendor/gtest-1.7.0/lib

SRC_INCLUDE = src

INCL = -I"$(BOOST_INCLUDE)" -I"$(GTEST_INCLUDE)" -I"$(SRC_INCLUDE)"  
LINK = -L"$(BOOST_LIB)" -L"$(GTEST_LIB)" -lboost_system -lboost_date_time
FLAG = -std=c++11
CC   = g++

.PHONY: all
all: generate listen serve connect unit_test
	./unit_test

.PHONY : clean
clean:
	-rm generate -f
	-rm listen -f
	-rm serve -f
	-rm connect -f
	-rm unit_test -f

generate:
	$(CC)  src/config/*.cc src/generate/*.cc -o generate  $(INCL) $(LINK) $(FLAG)
	
listen:
	$(CC)  src/common/*.cc src/config/*.cc  src/listen/main.cc -o listen $(INCL) $(LINK) $(FLAG)
	
serve:
	$(CC)  src/common/jsonxx.cc src/config/*.cc  src/server/*.cc -o serve $(INCL) $(LINK) $(FLAG)
		
connect:
	$(CC)  src/common/*.cc src/config/*.cc  src/connect/*.cc -o connect $(INCL) $(LINK) $(FLAG)
	
unit_test:
	$(CC)  src/config/*.cc src/common/*.cc $(filter-out src/server/main.cc, $(wildcard src/server/*.cc)) test/server/*.cc test/main.cc $(GTEST_LIB)/libgtest.a -o unit_test $(INCL) $(LINK) $(FLAG)
	./unit_test