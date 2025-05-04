# ---------- שמות ----------
TARGET      = matrix_demo
TEST_TARGET = test_runner      
TEST_SRC    = test_SquareMat.cpp

SRCS   = SquareMat.cpp main.cpp
HEADERS = SquareMat.hpp
OBJS   = $(SRCS:.cpp=.o)

CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic

# ---------- ברירת מחדל ----------
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

# ---------- טסטים  ----------
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRC) SquareMat.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(TEST_SRC) SquareMat.cpp -o $(TEST_TARGET)

# ---------- Valgrind ----------
valgrind: $(TARGET) $(TEST_TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TEST_TARGET)

clean:
	rm -f *.o $(TARGET) $(TEST_TARGET)
