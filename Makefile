all:
	gcc main.c -o main `pkg-config --cflags --libs libnotify`
	
#./main

clean:
	rm ./main