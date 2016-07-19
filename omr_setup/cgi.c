/*CGI FILE
--------------------------------------------------------------------------------
--!@brief CGI FILE
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! CGI PARA UCLINUX
--!
--! DETAILS:      
--!
--!- Project Name: cgi              
--!- Module Name: cgi.c
--!- Tools: jedit 
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: 22/01/2014     
--!- Version: 1.0.0 (jan/2014) 
--------------------------------------------------------------------------------
-- LNLS - DET - 2014
--------------------------------------------------------------------------------
Header*/
#include <stdio.h>
#include <stdlib.h>	
#include <string.h>
#include "cgivars.h"
#include "htmllib.h"
#include "omr_setup.h"

int main(void)
{

	char **postvars = NULL; /* POST request data repository */
	char **getvars = NULL; /* GET request data repository */
	char *title = "Medipix Controller";
	int form_method; /* POST = 1, GET = 0 */  

	form_method = getRequestMethod();

	if (form_method == POST) 
    {
        	getvars = getGETvars();
        	postvars = getPOSTvars();
   	} 
    else if (form_method == GET) 
    {
        	getvars = getGETvars();
    } 
    else 
    {
   		    htmlBody();
            fflush(stdout);
	}

   	htmlBody();
	
   	template_page(postvars, getvars, form_method);

   	cleanUp(form_method, getvars, postvars);
    fflush(stdout);
   	exit(0);
}

