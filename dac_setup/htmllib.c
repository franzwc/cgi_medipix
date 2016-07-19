#include <stdio.h>
#include "htmllib.h"

void htmlHeader(char *title) {
}
void htmlBody() {
	printf("%s%c%c\r\n\r\n" , "Content-Type:text/html;charset=iso-8859-1" , 13,10);
}

void htmlFooter() {
}

void addTitleElement(char *title) {
}

