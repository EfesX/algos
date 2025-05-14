CXX := g++
CXXFLAGS := -O2 -lm -fno-stack-limit -std=c++20 -x c++ -Wall -Wextra -fsanitize=address

# Ищем все .cc файлы в поддиректориях
SRCS := $(shell find . -type f -name '*.cc')
# Генерируем имена исполняемых файлов (заменяем .cc на .out)
TARGETS := $(SRCS:.cc=.out)

# Основная цель - собирает все возможные таргеты
all: $(TARGETS)

# Шаблонное правило для сборки каждого .out файла из .cc
%.out: %.cc
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	find . -type f -name '*.out' -delete

temp:
	rm -rf ../in2.txt
	echo 2 > ../in2.txt
	make season_7/s7e3_b.out && cat ../in1.txt | ./season_7/s7e3_b.out >> ../in2.txt

.PHONY: all clean
