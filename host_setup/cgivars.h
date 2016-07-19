#ifndef _CGIVARS_H
#define _CGIVARS_H

#define GET	0
#define POST	1

int getRequestMethod ();
char **getGETvars ();
char **getPOSTvars ();
int cleanUp (int form_method, char **getvars, char **postvars);

#endif
