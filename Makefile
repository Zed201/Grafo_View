all:
	@g++ index.cpp
	@mkdir -p images
	@rm -rf ./images/*.png
	@./a.out
	@python3 gif.py
	@echo "feito"
