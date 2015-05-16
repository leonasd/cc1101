/*
SI     P1.4
SCLK   P1.5
SO     P1.2
GD2    P1.3
CSN    P1.0
GD0    P1.1
*/
#include <msp430f5529.h>

#define 	GDO0_BIT    BIT6
#define 	GDO2_BIT	BIT6
#define     MISO_BIT	BIT3
#define 	MOSI_BIT	BIT4
#define	    SCK_BIT	    BIT3
#define  	CSN_BIT		BIT2


#define 	GDO0_DIR    P6DIR
#define 	GDO2_DIR	P1DIR
#define     MISO_DIR	P1DIR
#define 	MOSI_DIR	P1DIR
#define	    SCK_DIR	    P3DIR
#define  	CSN_DIR		P1DIR


#define 	GDO0_POUT   P6OUT
#define 	GDO2_POUT	P1OUT
#define     MISO_POUT	P1OUT
#define 	MOSI_POUT	P1OUT
#define	    SCK_POUT	P3OUT
#define  	CSN_POUT	P1OUT


#define 	GDO0_PIN    P6IN
#define 	GDO2_PIN	P1IN
#define     MISO_PIN	P1IN
#define 	MOSI_PIN	P1IN
#define	    SCK_PIN	    P3IN
#define  	CSN_PIN		P1IN


#define 	GDO0_IN         GDO0_PIN&GDO0_BIT 
#define 	GDO2_IN	        GDO2_PIN&GDO2_BIT
#define     MISO_IN	        MISO_PIN&MISO_BIT
#define 	MOSI_IN	        MOSI_PIN&MOSI_BIT
#define	    SCK_IN	        SCK_PIN &SCK_BIT
#define  	CSN_IN		    CSN_PIN &CSN_BIT


#define 	GDO0_UP         GDO0_POUT|=GDO2_BIT 
#define 	GDO2_UP	        GDO2_POUT|=GDO2_BIT
#define     MISO_UP  	    MISO_POUT|=MISO_BIT
#define 	MOSI_UP	        MOSI_POUT|=MOSI_BIT
#define	    SCK_UP	        SCK_POUT|=SCK_BIT
#define  	CSN_UP		    CSN_POUT|=CSN_BIT


#define 	GDO0_DN         GDO0_POUT&=~GDO2_BIT 
#define 	GDO2_DN	        GDO2_POUT&=~GDO2_BIT
#define     MISO_DN  	    MISO_POUT&=~MISO_BIT
#define 	MOSI_DN	        MOSI_POUT&=~MOSI_BIT
#define	    SCK_DN	        SCK_POUT &=~SCK_BIT
#define  	CSN_DN		    CSN_POUT &=~CSN_BIT


#define 	GDO0_DIR_OUT        GDO0_DIR|=GDO0_BIT 
#define 	GDO2_DIR_OUT	    GDO2_DIR|=GDO2_BIT 
#define     MISO_DIR_OUT	    MISO_DIR|=MISO_BIT 
#define 	MOSI_DIR_OUT	    MOSI_DIR|=MOSI_BIT 
#define	    SCK_DIR_OUT	        SCK_DIR |=SCK_BIT  
#define  	CSN_DIR_OUT         CSN_DIR |=CSN_BIT 


#define 	GDO0_DIR_IN         GDO0_DIR&=~GDO0_BIT  
#define 	GDO2_DIR_IN	        GDO2_DIR&=~GDO2_BIT 
#define     MISO_DIR_IN	        MISO_DIR&=~MISO_BIT 
#define 	MOSI_DIR_IN	        MOSI_DIR&=~MOSI_BIT 
#define	    SCK_DIR_IN	        SCK_DIR &=~SCK_BIT 
#define  	CSN_DIR_IN          CSN_DIR &=~CSN_BIT 

