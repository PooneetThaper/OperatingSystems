all: task5_a_queue task5_a_bounded_buffer task5_b

task5_a_queue: task5_a_queue.c
	gcc task5_a_queue.c -o task5_a_queue -lpthread

task5_a_bounded_buffer: task5_a_bounded_buffer.c
	gcc task5_a_bounded_buffer.c -o task5_a_bounded_buffer -lpthread

task5_b: task5_b.c
	gcc task5_b.c -o task5_b -lpthread -lrt -lm

clean:
	rm task5_b
	rm task5_a_queue
	rm task5_a_bounded_buffer
