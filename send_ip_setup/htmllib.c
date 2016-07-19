#include <stdio.h>
#include "htmllib.h"
/*CGI FILE
--------------------------------------------------------------------------------
--!@brief HTMLLIB FILE
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! HTMLLIB PARA UCLINUX
--!
--! DETAILS:      
--!
--!- Project Name: htmllib
--!- Module Name: htmllib.c
--!- Tools: jedit 
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: 22/01/2014     
--!- Version: 1.0.0 (jan/2014) 
--------------------------------------------------------------------------------
-- LNLS - DET - 2014
--------------------------------------------------------------------------------
Header*/
void htmlHeader(char *title)
{
}

void htmlBody() 
{
	printf("%s%c%c\n" , "Content-Type:text/html;charset=iso-8859-1" , 13,10);
}

void htmlFooter()
{
}

void addTitleElement(char *title) 
{
}

