/*
    r4iD-ftw's Substitution Crypter(Encrypter/Decryptor) v1.1	
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
/*
    The current version contains support for lowercase alphabets, further 
    support for other characters will be added soon.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define CHAR_LEN 26
char msg[50],encrypted[50];
int key=0,i,j,temp,msg_ind[50][50];
char charset[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
void encrypt();
void decrypt();
int checkKey(int);
void main()
{
	int ch;
	do
	{
		printf("\nr4iD-ftw's Substitution Crypter(Encrypter/Decryptor) v1.1\n");
		printf("Copyright 2014\n");
		printf("All Rights Reserved\n\n");
		printf("---------------------------------------------------------\n");
		printf("\nMenu :\n\n1.Encrypt\n\n2.Decrypt\n\n3.Exit\n\t->");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				printf("Enter string to encrypt: ");
				scanf("%s",&msg);
				printf("Enter key: ");
				scanf("%d",&key);
				if(checkKey(key))
					encrypt();
				break;
			case 2:
				decrypt();
				break;
			case 3:
				exit(1);
				break;
			default:
				printf("\nInvalid Selection!!\nTry Again...\n");
		}
	}while(1);
}
void encrypt()
{
	for(i=0;i<strlen(msg);i++)
	{
		for(j=0;j<CHAR_LEN;j++)
			if(msg[i]==charset[j])
			{
				temp = (j + key) % CHAR_LEN;
				encrypted[i] = charset[temp];
			}
	}
	printf("Encrypted Message : ");
	for(i=0;i<strlen(msg);i++)
		printf("%c",encrypted[i]);
	printf("\n");
}
void decrypt()
{
	printf("Enter string to decrypt: ");
	scanf("%s",&encrypted);
	for(i=0;i<strlen(encrypted);i++)
	{
		for(j=0;j<CHAR_LEN;j++)
		{
			if(encrypted[i]==charset[j])
			{
				msg_ind[0][i] = j;
			}
		}
	}
	printf("Possible Decrypted Values:-\n");
	for(i=1;i<CHAR_LEN;i++)
	{
		printf("Key = %d \t",i);
		for(j=0;j<strlen(encrypted);j++)
		{
			temp = (msg_ind[0][j]-i) % CHAR_LEN;
			if(temp<0)
				temp = CHAR_LEN+temp;
			msg[j] = charset[temp];
			printf("%c ",msg[j]);
		}
		printf("\n");
	}
}
int checkKey(int k)
{
	if(k>0 && k<CHAR_LEN)
		return 1;
	else
	{	printf("\n\nInvalid Key!!\n");
		printf("Your key must be from 1 - %d",CHAR_LEN);
		return 0;
	}
}
