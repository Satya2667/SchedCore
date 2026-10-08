
---

# 4) `Makefile`
```makefile
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall
SRC = scheduler.cpp
OUT = scheduler

.PHONY: all run clean

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

run: $(OUT)
	@echo "Running scheduler..."
	./$(OUT)

clean:
	-rm -f $(OUT) *.exe
	-rm -rf logs
