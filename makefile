
#YOU MUST HAVE YOUR NAME IN YOUR MAKEFILE!
#Anirudh Kondapaneni

#Makefile for lab 1-4.  You need to add you name to this file in the comments
# You will need to add a entry to create your zip file

#change the last dependency for each new lab
all:  tags headers lab3 proto1 proto2 proto3 proto4 lab4 lab4u

#this entry has to change for lab 2 - 4
# NEVER compile .c files with this rule - it lacks needed compile time flags
# There is an entry below that turns .c files into .o files

lab4: lab4.o bits.o input.o output.o physics.o dynamicM.o callbackFuncs.o n2.o link.o reliable.o
	gcc -g -o $@ $^  -lm -L. -lpb -lncurses

lab4u: lab4.o bits.o input.o output.o physics.o dynamicM.o callbackFuncs.o n2.o link.o unreliable.o
	gcc -g -o $@ $^  -lm -L. -lpb -lncurses
#this is where you create an entry to build yuour zip file
#it will also update with new labs

lab4.zip: makefile *.c *.h n2.o libpb.a liblinkedlist.a headers.sh headers.awk unreliable.o reliable.o README_LAB4
	zip $@ $^
	rm -rf install
	unzip $@ -d install
	make -C install lab4
	make -C install lab4u
	make -C install -r proto1
	make -C install -r proto2
	make -C install -r proto3
	make -C install -r proto4
	rm -rf install

#tests my iterate
proto1: proto1.o 
	gcc -g -o $@ $^ -lm -L. -lpb -llinkedlist -lncurses

#tests wether my insert is working.
proto2: proto2.o reliable.o
	gcc -g -o $@ $^ -lm -L. -lpb -llinkedlist -lncurses

#tests wether my delete is working.
proto3: proto3.o reliable.o
	gcc -g -o $@ $^ -lm -L. -lpb -llinkedlist -lncurses

#test my sort for linked list
proto4: proto4.o
	gcc -g -o $@ $^ -lm -L. -lpb -llinkedlist -lncurses




#this entry stays for C code labs
tags: *.c
	ctags -R .

# this entry stays for C code labs
headers: *.c tags
	headers.sh


# this entry takes care of C files depending on header files
# It has the flags for compiling the c code
# It you don't like makefiles, consider typing the following line a few
# thousand times this semester and reconsider.
# Be sure that this one doesn't get an inserted line break anywhere
%.o:%.c *.h
	gcc -std=c99 -pedantic -Wformat -Wreturn-type -g -c $< -o $@


