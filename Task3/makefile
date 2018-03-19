all: task3_1 task3_2 task3_3

task3_1: task3_1.c
	gcc task3_1.c -o task3_1

task3_2: task3_2.c
	gcc task3_2.c -o task3_2

task3_3: Parent_Prcs.c Prcs_P1.c Prcs_P2.c
	gcc Parent_Prcs.c -o Parent
	gcc Prcs_P1.c -o P1
	gcc Prcs_P2.c -o P2

clean:
	rm task3_1
	rm task3_2
	rm Parent
	rm P1
	rm P2
	rm destination1.txt
	rm destination2.txt
