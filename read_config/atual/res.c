// conversao ascii binario
	bzero(matrix,sizeof(matrix));
	token = strtok(threshold_high, " ");
	buff=atoi(token);
	strreverse(byte_to_binary(buff),token2);
	strncat(matrix,token2,5);
	line=0;
	while(token!= NULL)
	{
		token = strtok(NULL, " ");
		if (token!=NULL)
		{
			buff=atoi(token);
			strreverse(byte_to_binary(buff),token2);
			strncat(matrix,token2,5);
		}
		line++;
	}



	FILE *fp;
	fp=fopen(EQ_ARQUIVO,"w+");
	
    if(fp==NULL)
    {    
         fprintf(stderr,"Error open file \n");
         return -1;
    }

	for(line=0;line<=65535;line++)
	{	
	   	if ((line%3072==0)&(line!=0))
		{	
			fprintf(fp,"\n");
		}
		fprintf(fp,"%c",threshold_high[line]);
	}
    fclose(fp);
