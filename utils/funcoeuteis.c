//
//
//	funcoes uteis
//
//
void strreverse(char* begin, char* end) 
{
	char aux;
	while(end>begin)
	
		aux=*end, *end--=*begin, *begin++=aux;
}
	
void itoa(int value, char* str, int base) 
{
	static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	char* wstr=str;
	int sign;
	
	// Validate base
	if (base<2 || base>35){ *wstr='\0'; return; }
	
	// Take care of sign
	if ((sign=value) < 0) value = -value;
	
	// Conversion. Number is reversed.
	do *wstr++ = num[value%base]; while(value/=base);
	
	if(sign<0) *wstr++='-';
	
	*wstr='\0';

	// Reverse string
	strreverse(str,wstr-1);
}

int binary_decimal(int n) /* Function to convert binary to decimal.*/

{
    int decimal=0, i=0, rem;
    while (n!=0)
    {
        rem = n%10;
        n/=10;
        decimal += rem*pow(2,i);
        ++i;
    }
    return decimal;
}
