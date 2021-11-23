#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void toFile(char *spec, ...) {
	va_list args;
	unsigned len = strlen(spec);
	va_start(args, spec);
	int count = 0;
	FILE *file=fopen("lab1.out", "a");
	for(int i=0; i<len; i++) {
		switch(spec[i]) {
			case 'd':
				//printf("%d\n",va_arg(args, int));
				fprintf(file, "%d\n", va_arg(args, int));
				break;
			case 's':
				//printf("%s\n",va_arg(args, char*));
				fprintf(file, "%s\n", va_arg(args, char*));
				break;
			case 'f':
				//printf("%f\n", va_arg(args, double));
				fprintf(file, "%f\n", va_arg(args, double));
				break;
			default:
				printf("ERROR OCCURRED! WRONG SPEC!\n");
				fprintf(file, "ERROR! WRONG SPEC LETTER!\n");
				fclose(file);
				return;
		}
	}
	va_end(args);
	fclose(file);
}
int main() {
	printf(">>>LAB_1. P.A.Ognyanovich\n");
	printf(">>>TEST-1: \"dd\": 12 & 23.\n");
		toFile("dd", 12, 23);
	printf(">>>TEST-2: \"ff\": 2.5 & 0.372\n");
		toFile("ff", 2.5f, 0.372f);
	printf(">>>TEST-3: \"ss\": ololo & HELLO!\n");
		toFile("ss", "ololo", "HELLO!");
	printf(">>>TEST-4: \"dsfdfs\": -47, test-str, 3.1415, 31415, 5.5, the-end\n");
		toFile("dsfdfs", -47, "test-str", 3.1415, 31415, 5.5, "the-end");
	printf(">>>TEST-5: \"dsmf\", 555, nextIsError, ???, 5.55\n");
		toFile("dsmf", 555, "nextIsError", "???", 5.55);
	return 0;
}

