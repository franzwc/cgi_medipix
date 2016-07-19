#ifndef INTERFACE_UC_H_
#define INTERFACE_UC_H_
/*HEADER FILE
--------------------------------------------------------------------------------
--!@brief INTERFACE UC HEADER FILE
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! HEADER COM A STRUCT QUE CONTEM TODOS OS PARAMETROS DO REGISTRO OMR
--!
--! DETAILS:      
--!
--!- Project Name: interface_uc
--!- Module Name: interface_uc.h
--!- Tools: jedit 
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: 22/01/2014     
--!- Version: 1.0.0 (jan/2014) 
--------------------------------------------------------------------------------
-- LNLS - DET - 2014
--------------------------------------------------------------------------------
Header*/
#define BUFFER 16

typedef struct omr_parameters
{
    char        LABEL[BUFFER];            /*LABEL*/
    char        MODE[BUFFER];             /*M*/
    char        CRW_SRW[BUFFER];          /*CONTINUOUS - SEQUENCIAL MODE*/
    char        POLARITY[BUFFER];         /*ELETRONS - HOLE*/
    char        PS[BUFFER];               /*DATA OUT*/
    char        DISC_CSM_SPM[BUFFER];     /*DISCL - DISCH*/
    char        ENABLE_TP[BUFFER];        /*TEST PULSE*/
    char        COUNTL[BUFFER];           /*COUNTER DEPTH*/
    char        COLUMNBLOCK[BUFFER];      /*MATRIX COLUMNS TO BE READ*/
    char        COLUMBLOCKSEL[BUFFER];    /*ALL - MATRIX*/
    char        ROWBLOCK[BUFFER];         /*MATRIX ROW TO BE READ*/
    char        ROWBLOCKSEL[BUFFER];      /*ALL - MATRIX*/
    char        EQUALIZATION[BUFFER];     /*OFF - ON*/
    char        COLOURMODE[BUFFER];       /*FINE PITCH - SPECTROSCOPIC*/
    char        CSM_SPM[BUFFER];          /*SINGLE PIXEL - CHARGE SUMMING*/
    char        INFOHEADER[BUFFER];       /*NO - INFO*/
    char        GAINMODE[BUFFER];         /*SHGM - HGM - LGM - SLGM*/
    char        SENSEDAC[BUFFER];         /*DAC TO BE SENSE THROUGH DACOUT*/
    char        EXTDAC[BUFFER];           /*SELECT DAC TO BE EXT IMPOSET THROUGH*/
    char        EXTBGSEL[BUFFER];         /*INT - EXT*/
	char        TIME[BUFFER];             /*AQUIRE TIME*/
	char        COUNTER[BUFFER];          /*AQUIRE COUNTER*/
	char        GAP[BUFFER];              /*AQUIRE GAP*/
	char        READCOUNT[BUFFER];        /*READ COUNTER*/
	char        PULSE_PERIOD[BUFFER];     /*TEST PULSE PERIOD*/
	char		NPULSES[BUFFER];          /*NUMBER OF TEST PULSES*/
    
} omr_parameters_t;

typedef struct dac_parameters
{
   // const char* LABEL;                  /*LABEL*/
    char        THRESHOLD_0[BUFFER];      /*THRESHOLD 0*/
    char        THRESHOLD_1[BUFFER];      /*THRESHOLD 1*/
    char        THRESHOLD_2[BUFFER];      /*THRESHOLD 2*/
    char        THRESHOLD_3[BUFFER];      /*THRESHOLD 3*/
    char        THRESHOLD_4[BUFFER];      /*THRESHOLD 4*/
    char        THRESHOLD_5[BUFFER];      /*THRESHOLD 5*/
    char        THRESHOLD_6[BUFFER];      /*THRESHOLD 6*/
    char        THRESHOLD_7[BUFFER];      /*THRESHOLD 7*/
    char        PREAMP[BUFFER];           /*PREAMP*/
    char        IKRUM[BUFFER];            /*IKRUM*/
    char        SHAPER[BUFFER];           /*SHAPER*/
    char        DISC[BUFFER];             /*DISC*/
    char        DISCLS[BUFFER];           /*DISCLS*/
    char        SHAPER_TEST[BUFFER];      /*SHAPER_TEST*/
    char        DAC_DISCL[BUFFER];        /*DAC_DISCL*/
    char        DAC_TEST[BUFFER];         /*DAC_TEST*/
    char        DAC_DISCH[BUFFER];        /*DAC_DISCH*/
    char        DELAY[BUFFER];            /*DELAY*/
    char        TP_BUFFER_IN[BUFFER];     /*TP_BUFFER_IN*/
    char        TP_BUFFER_OUT[BUFFER];    /*TP_BUFFER_OUT*/
    char        RPZ[BUFFER];              /*RPZ*/
    char        GND[BUFFER];              /*GND*/
    char        TP_REF[BUFFER];           /*TP_REF*/
    char        FBK[BUFFER];              /*FBK*/
    char        CAS[BUFFER];              /*CAS*/
    char        TP_REFA[BUFFER];          /*TP_REFA*/
    char        TP_REFB[BUFFER];          /*TP_REFB*/
    
} dac_param_t;

#endif /*INTERFACE_UC_H_*/
