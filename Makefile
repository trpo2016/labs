CC = gcc
// CFLAGS = -g -Wall
CFLAGS = -Wall
BUILD_DIR = "./build/"
mkdir -p ${BUILD_DIR}

1:
	$(CC) $(CFLAGS) -o "${BUILD_DIR}lab_1" "./1.c"
2:
	$(CC) $(CFLAGS) -o "${BUILD_DIR}lab_2" "./2.c"
3_stack:
	$(CC) $(CFLAGS) -o "${BUILD_DIR}lab_3" "./3_stack.c"
3_queue:
	$(CC) $(CFLAGS) -o "${BUILD_DIR}lab_3" "./3_queue.c"
4:
	$(CC) $(CFLAGS) -o "${BUILD_DIR}lab_4" "./4.c"
5:
	$(CC) $(CFLAGS) -o "${BUILD_DIR}lab_5" "./5.c"
6:
	$(CC) $(CFLAGS) -o "${BUILD_DIR}lab_6" "./6.c"
all:	1 2 3_stack 3_queue 4 5 6
clean: 
	rm -r ${BUILD_DIR}