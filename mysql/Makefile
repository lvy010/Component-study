# MySQL C++ 示例 Makefile
CXX = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS = -lmysqlclient
SRC = test_connect.cc test.cc
BIN = test_connect test

all: $(BIN)

# 编译 test_connect
 test_connect: test_connect.cc
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

# 编译 test
 test: test.cc
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

# 编译 test_transaction
 test_transaction: test_transaction.cc
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -f $(BIN) 