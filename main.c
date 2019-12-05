/*
 * main.c
 *
 *  Created on: Dec 2, 2019
 *      Author: ahmed
 */


#include "payment.h"
#include <stdio.h>

uint8_t u8_OperationStatus = 'y';

int main(){

    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    uint8_t u8_UserStatusCheck;

while(1)
{
    if(u8_OperationStatus == 'y')
	{
	    struct ST_transaction User;
	    fillCardData(&User);
	    u8_UserStatusCheck='y';

	    while(u8_UserStatusCheck=='y')
		{
		    checkAmount(&User);
		    if(gu8_CheckStatus==0)
			{
			    printf("Transaction is DECLINED!\n");
			    printf("Do you want to continue (y/n)?: ");
			    gets(&u8_UserStatusCheck);
			    if(u8_UserStatusCheck=='y')
				{
				    continue;
				}
			}
		    else
			break;
		}

	    fillTerminalData(&User);

	    checkExpiryDate(&User);

	    printf("Verifying Data from the server…\n");

	    if(gu8_CheckExpiry==0)
		{
		    printf("transaction date = \"%s\" and expiry date = \"%s\"\n",User.transData.transactionDate, User.cardHolderData.cardExpirationDate);
		    printf("The transaction is DECLINED\n");
		    printf("Do you want to continue (y/n)?: ");
		    gets(&u8_OperationStatus);
		    continue;
		}
	    checkBalance(&User);

	    if(gu8_CheckExist==0)
		{

		    printf("The transaction is DECLINED\n");
		    printf("Do you want to continue (y/n)?: ");
		    gets(&u8_OperationStatus);
		    continue;
		}

	    if(gu8_CheckBalance==0)
		{
		    printf("The transaction is DECLINED\n");
		    printf("Do you want to continue (y/n)?: ");
		    gets(&u8_OperationStatus);
		    continue;
		}

	    saveTransactionIntoServer(&User);

	    printf("Do you want to continue (y/n)?: ");
	    gets(&u8_OperationStatus);
	    continue;
	}
    else
	break;



	}
}
