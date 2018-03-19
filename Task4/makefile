all: generate_scores calculate_averages

generate_scores: generate_scores.c
	gcc generate_scores.c -o generate_scores

calculate_averages: calculate_averages.c
	gcc calculate_averages.c -o calculate_averages

clean:
	rm calculate_averages
	rm generate_scores
	rm scores.csv
	rm averages.txt
