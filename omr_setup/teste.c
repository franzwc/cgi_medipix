/*CGI FILE
teste
Header*/
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "../utils/global.h"
#include "../utils/persist.h"
#include "../utils/interface_uc.h"



int main(void) 
{	
    char buffer[12];
    int fd=-1;
    omr_parameters_t* omr_pt=NULL;

    if (fd=read_omrfile(OMR_FILE,omr_pt) == -1) {
		printf("Error! Failed to open OMR FILE!\n");
		return 0;
	}
    
    printf("\nLABEL %s\n",omr_pt->LABEL);
    printf("\n\nomr_atual->M %s\n",omr_pt->MODE);
    printf("omr_atual->crw %s\n",omr_pt->CRW_SRW);
    printf("omr_atual-pl %s\n",omr_pt->POLARITY);
    /*printf("omr_atual->ps %s\n",omr_atual->PS);
    printf("omr_atual->DISC_CSM_SPM %s\n",omr_atual->DISC_CSM_SPM);
    printf("omr_atual->ENABLE_TP %s\n",omr_atual->ENABLE_TP);
    printf("omr_atual-COUNTL %s\n",omr_atual->COUNTL);
    printf("omr_atual->COLUMNBLOCK %s\n",omr_atual->COLUMNBLOCK);
    printf("omr_atual->COLUMBLOCKSEL %s\n",omr_atual->COLUMBLOCKSEL);
    printf("omr_atual->ROWBLOCK %s\n",omr_atual->ROWBLOCK);
    printf("omr_atual-ROWBLOCKSEL %s\n",omr_atual->ROWBLOCKSEL);
    printf("omr_atual->EQUALIZATION %s\n",omr_atual->EQUALIZATION);
    printf("omr_atual->COLOURMODE %s\n",omr_atual->COLOURMODE);
    printf("omr_atual->CSM_SPM %s\n",omr_atual->CSM_SPM);
    printf("omr_atual-INFOHEADER %s\n",omr_atual->INFOHEADER);
    printf("omr_atual->GAINMODE %s\n",omr_atual->GAINMODE);*/

	return 0;
}



