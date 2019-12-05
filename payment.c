/*
 * payment.c
 *
 *  Created on: Dec 2, 2019
 *      Author: ahmed Sharaf
 */
#include <stdio.h>
#include "string.h"
#include "payment.h"

uint8_t gu8_CheckStatus;
uint8_t gu8_CheckExpiry=0;
uint8_t gu8_CheckExist=0;
uint8_t gu8_CheckBalance=0;
/*
 * Global array that stored the data of clients in the server
 */


ST_accountBalance gastru8_ServerDataBalance[10]={
						{"123456789","0100.00"},
						{"234567891","6000.00"},
						{"567891234","3250.25"},
						{"456789123","1500.12"},
						{"258649173","0500.00"},
						{"654823719","2100.00"},
						{"971362485","0000.00"},
						{"793148625","0001.00"},
						{"123123456","0010.12"},
						{"456789321","0000.55"}
};

uf32_t stringTofloat(uint8_t* str){

    uf32_t u32_conv_number=0;
    while(*str != '\0')
	{
	    if(*str != '.')
		u32_conv_number = (u32_conv_number*10) + (*(str++)-'0');
	    else
		{

		    str++;
		    continue;

		}

	}
    return u32_conv_number/100;
}

uint8_t stringTointeger_Year_Month(uint8_t* str){

    uint8_t u8_conv_number=0;
    uint8_t u8_fixed_iterator=2;
    while(u8_fixed_iterator)
	{
	    u8_conv_number = u8_conv_number*10 + (*(str++)-'0');
	    u8_fixed_iterator--;
	}
    return u8_conv_number;

}

/*
 * Global array that stored the data of status of every
 * transaction done in the server and its number
 */

ST_serverData gau_SequenceTransaction [255];

/*
 * Global structure for user
 */


void fillCardData(ST_transaction *transaction){

    printf("Please, Enter Cardholder Name: ");
    gets(transaction->cardHolderData.cardHolderName);
    printf("Please, Enter the Primary Account Number: ");
    gets(transaction->cardHolderData.primaryAccountNumber);
    printf("Please, Enter the Card Expiry Date: ");
    gets(transaction->cardHolderData.cardExpirationDate);
}


void checkAmount(ST_transaction *transaction){

    printf("Please Enter the Amount: ");
    gets(transaction->transData.transAmount);
    uf32_t u32_userAmount = stringTofloat(transaction->transData.transAmount);
    strcpy(transaction->transData.maxTransAmount,"5000.00");
    uf32_t u32_maxAmount = stringTofloat(transaction->transData.maxTransAmount);
    if(u32_userAmount > u32_maxAmount)
	gu8_CheckStatus=0;
    else
	gu8_CheckStatus=1;
}

void fillTerminalData(ST_transaction *transaction){

    printf("Please Enter transaction Date: ");
    gets(transaction->transData.transactionDate);
}

void checkExpiryDate(ST_transaction *transaction){

    uint8_t u8_user_year = stringTointeger_Year_Month(&transaction->transData.transactionDate[8]);
    uint8_t u8_user_month = stringTointeger_Year_Month(&transaction->transData.transactionDate[3]);
    uint8_t u8_exp_year = stringTointeger_Year_Month(&transaction->cardHolderData.cardExpirationDate[3]);
    uint8_t u8_exp_month = stringTointeger_Year_Month(&transaction->cardHolderData.cardExpirationDate[0]);

    if(u8_user_year > u8_exp_year)
	{
		gu8_CheckExpiry=0;
		return;
	}
    else if(u8_user_year < u8_exp_year)
	{
		gu8_CheckExpiry=1;
		return;
	}
    else if(u8_user_year == u8_exp_year)
	{
	    if(u8_user_month > u8_exp_month)
		{
			gu8_CheckExpiry=0;
			return;
		}
	    else
		{
			gu8_CheckExpiry=1;
			return;
		}
	}

}

void checkBalance(ST_transaction *transaction){

    uint8_t u8_iterator1;
    uint8_t u8_balance_index;

    for(u8_iterator1=0; u8_iterator1<10;u8_iterator1++)
	{
	    if((strcmp((char *)transaction->cardHolderData.primaryAccountNumber,(char *)gastru8_ServerDataBalance[u8_iterator1].primaryAccountNumber))==0)
	    {
		gu8_CheckExist=1;
		u8_balance_index = u8_iterator1;
		break;
	    }
	}
    if(gu8_CheckExist==1)
	{
	    uf32_t u32_userAmount = stringTofloat(transaction->transData.transAmount);
	    uf32_t u32_balanceAmount = stringTofloat(gastru8_ServerDataBalance[u8_balance_index].balance);
	    if(u32_balanceAmount < u32_userAmount)
		{
		    gu8_CheckBalance=0;
		}
	    else
		gu8_CheckBalance=1;
	}
}

void saveTransactionIntoServer(ST_transaction *transaction){

	static uint8_t u8_SequenceArray_index=0;
	gau_SequenceTransaction[u8_SequenceArray_index].receiptReferenceNumber=u8_SequenceArray_index;
	if((gu8_CheckExpiry & gu8_CheckExist & gu8_CheckBalance))
	    {
	    gau_SequenceTransaction[u8_SequenceArray_index].transactionStatus=transaction->transResponse.transactionStatus;
	    printf("The Transaction is APPROVED.\n");
	    }
	else
	    {
	    gau_SequenceTransaction[u8_SequenceArray_index].transactionStatus=transaction->transResponse.transactionStatus;
	    printf("The Transaction is DECLINED.\n");
	    }
	u8_SequenceArray_index++;
}






