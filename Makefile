n ?= test
all:
	@g++ index.cpp
	@rm -rf ./dados/*.txt
	@rm -rf ./images/*.png
	@./a.out
	@python3 gif.py
