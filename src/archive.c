#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

const char *DELIMITER = ",";
ssize_t array_size;

int *readLine(FILE *input, long int position){
	char *line = NULL;
	char *token = NULL;
	size_t initial_size = 0;
	int counter = 0;
	int *sequence;
	fseek(input, position, SEEK_SET);

	array_size = getline(&line, &initial_size, input);
	line[array_size - 1] = '\0';

	sequence = calloc(array_size, sizeof(*sequence));
	token = strtok(line, DELIMITER);

	while(token != NULL){
		sequence[counter] = atoi(token);
		token = strtok(NULL, DELIMITER);
		counter++;
	}

	array_size = array_size / 2;
	return sequence;
}

int getColumnSize(void){
	return array_size;
}


int readSizeMemory(FILE *input, long int position){
	int size;

	fseek(input, position, SEEK_SET);
	fscanf(input, "%d", &size);

	return (size);
}

void saveHistoric(page **historic, FILE *output){
	fprintf(output, "EVOLUCAO");

	for(int i = 0; i < getLineSize(); i++){
		for(int j = 0; j < getColumnSize(); j++){
			fprintf(output, "%d ", historic[i][j].numberPage);
		}

		fprintf(output, "\n");
	}
}

void saveFinalReport(FILE *output){
	fprintf(output, "ACERTOS \n%d", getHits());
	fprintf(output, "ERROS \n%d" , getMisses());
	fprintf(output, "TOTAL REQUISICOES \n%d", getColumnSize());
	fprintf(output, "TAXA DE ERRO \n%f", getErrorRate());
}
