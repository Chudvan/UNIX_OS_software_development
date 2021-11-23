#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void toFile(char *name, ...){
	va_list args;
	va_start(args, name);
	FILE *f = fopen(name, "w");
	while(f) {
		char *s = va_arg(args, char*);
		if(strlen(s)==1 && s[0]=='0') {
			fclose(f);
			va_end(args);
			return;
		}
		fprintf(f, "%s\n", s);
	}

}

int main(){
	toFile("temp.txt", "str1", "str2", "str3", 0);
}
