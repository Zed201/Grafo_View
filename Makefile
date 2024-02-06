all:
	@g++ index.cpp Grafo.cpp
	@mkdir -p images
	@rm -rf ./images/*.png
	@./a.out
	
gif:
	@python3 gif.py
	@echo "feito"

re:
	@rm -rf ./images/*.png *.txt *.gif index ./*.out
	
