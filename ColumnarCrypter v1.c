/*
    r4iD-ftw's Columnar Transposition Cipher Encryptor/Decryptor v1.1	
    Copyright (C) 2014  @Mihir Manek

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
    
    For further details, mail me at mihirmanek6@gmail.com or add me https://www.facebook.com/MihirManek6
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define ROWS 20
#define COLS 7
char msg[50],encrypted[50],mat[ROWS][COLS];
int arr_key[COLS];
long int key;
void head();
void encryptColumnar();
void decryptColumnar();
int check(long int);
int invalidKey();
void main()
{
	int ch,k,ch_in;
	//clrscr();
	head();
	while(1)
	{
		start:
		printf("\n\nMenu :\n\n1.Encrypt\n\n2.Decrypt\n\n3.Exit\n\t->");
		scanf("%d",&ch);
		switch(ch)
		{
		case 1:	printf("\nEnter string to encrypt: ");
			scanf("%s",&msg);
			invalidEnc:
			printf("\nEnter key(Order of Columns): ");
			scanf("%d",&key);
			k = check(key);
			if(k==1)
				encryptColumnar();
			else
			{	ch_in = invalidKey();
				switch(ch_in)
				{
					case 1:
						goto invalidEnc;
						break;
					case 2:
						goto start;
						break;
					default:
						printf("\nInvalid Choice!\n");
				}
			}
			head();	
			break;
		case 2:
			printf("\nEnter string to decrypt: ");
			scanf("%s",&encrypted);
			invalidDec:
			printf("\nEnter key: ");
			scanf("%d",&key);
			k = check(key);
			if(k==1)
				decryptColumnar();
			else
			{
				ch_in = invalidKey();
				switch(ch_in)
				{
					case 1:
						goto invalidDec;
						break;
					case 2:
						goto start;
						break;
					default:
						printf("\nInvalid Choice!\n");
				}
			}
			head();
			break;
		case 3:
			exit(1);
		}
	}
	//printf("Encrypted Message: %s",&encrypted);
}
void head()
{
	printf("\n\n\nr4iD-ftw's Columnar Transposition Cipher Encryptor/Decryptor\n");
	printf("Copyright 2014\n");
	printf("All Rights Reserved\n");
	printf("--------------------------------------------------------------\n");
}
void encryptColumnar()
{
	int i,j,k=0,rows_used,cols_used,temp=0;
	for(i=0;i<ROWS && k<strlen(msg);i++)
	{
		for(j=0;j<COLS;j++)
		{
			if(k<strlen(msg))
			{
				mat[i][j]=msg[k];
				k++;
			}
			else
				mat[i][j] = 'x';
		}
	}
	rows_used=i;
	for(i=0;i<COLS;i++)
	{
		k = arr_key[i];
		for(j=0;j<rows_used;j++)
		{
			encrypted[temp]=mat[j][k-1];
			temp++;
		}
	}
	printf("\nEncrypted Message ->");
	for(i=0;i<(rows_used*COLS);i++)
		printf("%c",encrypted[i]);
}
int check(long int k)
{
	int no = k,count=0,rem,i = COLS-1,key = k,j;
	while(no!=0)
	{
		rem = no % 10;
		if(rem<=0 || rem>COLS)
			return 0;
		count++;
		no = no / 10;
	}	
	if(count==COLS)
	{
		while(key!=0)
		{
			rem = key % 10;
			arr_key[i] = rem;
			key = key/10;
			i--;
		}
		for(i=0;i<COLS;i++)
		{
			no = arr_key[i];
			for(j=i+1;j<COLS;j++)
			{
				if(no==arr_key[j])
					return 0;
			}
		}
	}
	else return 0;
	return 1;	
}
int invalidKey()
{
	int in;
	printf("\n\nInvalid Key!!\n");
	printf("\nThe key must satisfy the following conditions:-");
	printf("\n1.It must contain all numbers from 1-%d.",COLS);
	printf("\n2.The numbers must not be repeated.");
	printf("\n3.Length should be %d.",COLS);
	printf("\n\nWhat do you wanna do?\n");
	printf("\n1.Try Entering the key again for the same message.");
	printf("\n2.Start Over again.\n\t->");
	scanf("%d",&in);
	return (in);
}
void decryptColumnar()
{
	int rows_used,i,j,k,temp=0;
	if(strlen(encrypted) % COLS == 0)
		rows_used = strlen(encrypted) / COLS;
	else
		rows_used = (strlen(encrypted) / COLS)+1;
	for(i=0;i<COLS;i++)
	{
		k = arr_key[i];
		for(j=0;j<rows_used && temp<strlen(encrypted);j++)
		{
			mat[j][k-1] = encrypted[temp];
			temp++;
		}
	}
	temp=0;
	for(i=0;i<rows_used;i++)
	{
		for(j=0;j<COLS;j++)
		{
			msg[temp] = mat[i][j];
			temp++;
		}
	}
	printf("Decrypted Message : ");
	for(i=0;i<strlen(encrypted);i++)
		printf("%c",msg[i]);
}
