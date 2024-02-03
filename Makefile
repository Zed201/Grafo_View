n ?= test
all:
	@g++ index.cpp
	@./a.out $(n) > index.txt
	@cat index.txt
	@python3 index.py
	img $(n).png
