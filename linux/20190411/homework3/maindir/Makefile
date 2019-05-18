OB:=main.o add.o
YYF:=main
$(YYF):$(OB) 
#gcc -o $@ $^
#main.o:main.c
#gcc -c main.c
# add.o:add.cc
.PHONY:rebuild clean
rebuild:clean 
clean:
	rm -rf $(OB) $(YYF)
