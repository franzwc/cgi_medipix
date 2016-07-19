#include <stdio.h>
#include <stdlib.h>	
#include <string.h>
#include "cgivars.h"
#include "htmllib.h"
#include "ctpr_setup.h"

int main(void) {

	char **postvars = NULL; /* POST request data repository */
	char **getvars = NULL; /* GET request data repository */
	char *title = "Medipix Controller";
	int form_method; /* POST = 1, GET = 0 */  

	form_method = getRequestMethod();

	if (form_method == POST) {
        	getvars = getGETvars();
        	postvars = getPOSTvars();
    	} else if (form_method == GET) {
        	getvars = getGETvars();
    	} else {
		//htmlHeader();
    		htmlBody();
    		//addTitleElement("Error!");		
    		//htmlFooter();
		fflush(stdout);
	}

    	//htmlHeader(title);
    	htmlBody();
    	//addTitleElement(title);	
	
    	template_page(postvars, getvars, form_method);

    	//htmlFooter();
    	cleanUp(form_method, getvars, postvars);
	fflush(stdout);
    	exit(0);

}

