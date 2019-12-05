/*
 * payment.h
 *
 *  Created on: Dec 2, 2019
 *      Author: ahmed
 */

#ifndef PAYMENT_H_
#define PAYMENT_H_



typedef unsigned char uint8_t;
typedef float uf32_t;


extern uint8_t gu8_CheckStatus;
extern uint8_t gu8_CheckExpiry;
extern uint8_t gu8_CheckExist;
extern uint8_t gu8_CheckBalance;



/*
 * @breif: structure that hold the data of card form user
 * @para 1: cardHolderName : string parameter
 * 		it holds the name of the user
 * @para 2: primaryAccountNumber : string parameter
 * 		it holds the unique primary number of card owner
 * @para 3: cardExpirationDate : string parameter
 * 		it holds the date of card expiration
 */
typedef struct ST_cardData
{
	unsigned char cardHolderName[25];
	unsigned char primaryAccountNumber[19];
	unsigned char cardExpirationDate[6];
}ST_cardData;


/*
 * @breif: structure that hold the data transaction
 * @para 1: transAmount: string parameter
 * 		is a string contains the actual transaction amount
 * @para 2: maxTransAmount : string parameter
 * 		is a string contains the maximum allowed amount
 * @para 3: transactionDate : char parameter
 * 		is a string that holds the transaction date
 */

typedef struct ST_terminalData
{
	unsigned char transAmount[8];
	unsigned char maxTransAmount[8];
	unsigned char transactionDate[11];
}ST_terminalData;


/*
 * @breif: enum that hold 2 cases of operations true, false
 * @para 1: DECLINED : 0
 * @para 2: APPROVED : 1
 */

typedef enum EN_transStat
{
	DECLINED,
	APPROVED
}EN_transStat;

/*
 * @breif: structure that hold the status of transaction and its number
 * @para 1: transactionStatus: struct parameter
 * 		contains the status came from EN_transStat
 * @para 2: receiptReferenceNumber : unsigned int parameter
 * 		contains the number of transaction
 */


typedef struct ST_serverData
{
	EN_transStat transactionStatus;
	unsigned int receiptReferenceNumber;
}ST_serverData;

/*
 * @breif: structure that hold struucts of all data of owner
 * @para 1: cardHolderData: struct parameter
 * 		structure that hold the data of card form user
 * @para 2: transData : struct parameter
 * 		structure that hold the data transaction
 * @para 3: transResponse : struct parameter
 * 		structure that hold the status of transaction and its number
 */

typedef struct ST_transaction
{
	ST_cardData cardHolderData;
	ST_terminalData transData;
	ST_serverData transResponse;
}ST_transaction;

/*
 * @breif: structure that hold account balance
 * @para 1: balance: array of unsigned chars
 * 		holds the balance amount
 * @para 2: primaryAccountNumber : array of unsigned chars
 * 		holds the primary number
 */

typedef struct ST_accountBalance
{
	unsigned char primaryAccountNumber[19];
	unsigned char balance[8];

}ST_accountBalance;



/*
 * @breif: void function that fill the structure of ST_transaction
 * 	   with card data passed by reference.
 * @para 1: transaction : pointer to ST_transaction struct parameter
 * 		it holds the card data
 * @return: no return
 */
void fillCardData(ST_transaction *transaction);


/*
 * @breif: void function that reads amount of balance
 * 	   with card data passed by reference
 * 	   It checks if the amount > maximum transaction
 * 	   Amount (5000.00)
 * @para 1: transaction : pointer to ST_transaction struct parameter
 * 		it holds the card data
 * @return: no return
 */
void checkAmount(ST_transaction *transaction);

/*
 * @breif: void function that fill It fills transaction amount,
 *         maximum transaction amount and expiry date in
 *         the ST_transaction structure
 * @para 1: transaction : pointer to ST_transaction struct parameter
 * 		it holds the card data
 * @return: no return
 */
void fillTerminalData(ST_transaction *transaction);

/*
 * @breif: void function that Reads the expiry and transaction dates
 * 	   with card data passed by reference It checks if the
 * 	   expiry date > than transaction date
 * @para 1: transaction : pointer to ST_transaction struct parameter
 * 		it holds the card data
 * @return: no return
 */
void checkExpiryDate(ST_transaction *transaction);

/*
 * @breif: void function that It checks It checks for balance for
 *         the expiry date of ST_transaction with card data
 *         passed by reference.
 * @para 1: transaction : pointer to ST_transaction struct parameter
 * 		it holds the card data
 * @return: no return
 */
void saveTransactionIntoServer(ST_transaction *transaction);

/*
 * @breif: void function that reads the primary account number
 *         and searches for the primary account number
 *         into the account/balance array
 *         the expiry date of ST_transaction with card data
 *         passed by reference.
 * @para 1: transaction : pointer to ST_transaction struct parameter
 * 		it holds the card data
 *
 * @output: print the status of transaction
 * @return: no return
 */
void checkBalance(ST_transaction *transaction);


float stringTofloat(uint8_t* str);

uint8_t stringTointeger_Year_Month(uint8_t* str);

#endif /* PAYMENT_H_ */
