#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
	int i;
	if(addressBook -> contactCount == 0)
	{
		printf("No contact to display.\n");
		return ;
	}
	printf("Sl	Name		Phone No		Email\n");
	for(i = 0;i < addressBook -> contactCount; i++)
	{
		printf("%d\t",i + 1);
		printf("%s \t",addressBook -> contacts[i].name);
		printf("%s\t",addressBook -> contacts[i].phone);
		printf("%s\n",addressBook -> contacts[i].email);
	}
}

void initialize(AddressBook *addressBook) {
	addressBook->contactCount = 0;
	populateAddressBook(addressBook);

	// Load contacts from file during initialization (After files)
	loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
	saveContactsToFile(addressBook); // Save contacts to file
	exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
lable1:
	printf("Enter the name : ");
	scanf(" %[^\n]",addressBook -> contacts [addressBook -> contactCount].name);

	int i = 0;
	while(addressBook ->contacts[addressBook->contactCount].name[i] != '\0')
	{
		char name = addressBook->contacts[addressBook->contactCount].name[i];

		if(name >= 'a' && name <= 'z'|| name >= 'A' && name <= 'Z' || name == ' ')
		{
			i++;
		}
		else
		{
			printf("Invalid !.. Try Again");
			goto lable1; 
		}
	}

lable2:
	printf("Enter Phone number (10 digits) : ");
	scanf("%s",addressBook -> contacts [addressBook -> contactCount].phone);

	if((strlen (addressBook -> contacts [addressBook -> contactCount].phone)) != 10)
	{
		printf("Invaild !.. Enter 10 digits only");
		goto lable2;
	}
	else
	{
		for(i = 0; i < addressBook->contactCount;i++)
		{
			if(strcmp(addressBook->contacts[addressBook->contactCount].phone, addressBook->contacts[i].phone)==0)
			{
				printf("Mobile Number allready Found ....Enter again");
				goto lable2;
			}
		}
		while(addressBook -> contacts->phone[i] != '\0')
		{
			char Mobile = addressBook -> contacts [addressBook -> contactCount].phone[i];
			if(Mobile >= '0' && Mobile <= '9')
			{
				i++;
			}
			else
			{
				printf("Error !.. ");
				goto lable2;
			}			
		}
	}

lable3:
	printf("Enter Mail id : ");
	scanf("%s",addressBook -> contacts [addressBook -> contactCount].email);

	for(i = 0;addressBook -> contacts [addressBook -> contactCount].email[i] != '\0';i++)
	{

		char mail=addressBook->contacts[addressBook->contactCount].email[i];
		if(mail == '@')
		{
			if(strstr(addressBook ->contacts[addressBook->contactCount].email,".com") != NULL)
			{
				if(addressBook ->contacts[addressBook->contactCount].email[i + 1] != '.' )
				{
					printf("Contact Stored sucessfully");
					addressBook->contactCount++;
					return;
				}
				else
				{
					printf("Error !.. ");
					goto lable3;
				}
			}
			else
			{
				printf("Error !.. ");
				goto lable3;
			}

		}
	}
	printf("Error !.. ");
	goto lable3;
}

void searchContact(AddressBook *addressBook) 
{
label1:
	int option;
	char src1[100], src2[20], src3[100];
	int sub = -1, i;
	printf("1. By Name \n");
	printf("2. By Mobile No \n");
	printf("3. By Mail id \n");
	printf("Enter Your Option : ");
	scanf("%d", &option);

	switch(option)
	{
		case 1:
			printf("Enter the name :");
			scanf(" %[^\n]", src1);

			for(i = 0; i < addressBook->contactCount;i++)
			{
				sub = strcmp(src1, addressBook->contacts[i].name);		
				if(sub == 0)
				{
					printf("%s\t%s\t%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
					break;
				}
			}
			if(sub != 0)
			{
				printf("Invaild....\n");
				goto label1;
			}
			break;

		case 2:
			printf("Enter the phone number :");
			scanf(" %[^\n]", src2);

			for(i = 0;i < addressBook->contactCount;i++)
			{
				sub = strcmp(src2, addressBook->contacts[i].phone);		
				if(sub == 0)
				{
					printf("%s\t%s\t%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
					break;
				}
			}
			if(sub != 0)
			{
				printf("Invaild....\n");
				goto label1;
			}
			break;

		case 3:
			printf("Enter the mail id :");
			scanf(" %[^\n]", src3);

			for(i = 0;i != addressBook->contactCount;i++)
			{
				sub = strcmp(src3, addressBook->contacts[i].email);		
				if(sub == 0)
				{
					printf("%s\t%s\t%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
					break;
				}
			}
			if(sub != 0)
			{
				printf("Invaild....\n");
				goto label1;
			}
			break;

		default:
			printf("Invalid Option!... Try Again");
			goto label1;
	}
}

void editContact(AddressBook *addressBook)
{
	void searchContact(AddressBook *addressBook);
	printf("1.edit by name.\n");
	printf("2.edit by mobile number.\n");
	printf("3.edit by email ID.\n");
	int option;
	printf("Enter the option : ");
	scanf("%d", &option);
	switch(option)
	{
		case 1:
			char edit_name[50];
			int flag1 = 0;
			int count_name = 0; 
			printf("Enter the contact name : ");
			scanf(" %[^\n]",edit_name);
			for(int i = 0;i < addressBook -> contactCount;i++)
			{
				if(strcmp(addressBook -> contacts[i].name,edit_name) == 0)
				{
					count_name++;
				}
			}
			if(count_name == 0)
			{
				printf("No contact found with this name \n");
				return;
			}
			else
			{
				if(count_name == 1)
				{
					for(int i = 0;i < addressBook -> contactCount;i++)
					{
						if(strcmp(addressBook -> contacts[i].name,edit_name) == 0)
						{
							if(count_name == 1)
							{
								printf("Contact Found\n");
								printf("%s ", addressBook -> contacts[i].name);
								printf("%s ", addressBook -> contacts[i].phone);
								printf("%s\n", addressBook -> contacts[i].email);

								printf("Enter a new name : ");
								char edit_name1[50];
								scanf(" %[^\n]", edit_name1);		    
								int valid_name = 1;
								for(int j = 0;edit_name1[j] != '\0';j++)
								{
									if(!((edit_name1[j] >= 'a' && edit_name1[j] <= 'z') || (edit_name1[j] >= 'A' && edit_name1[j] <= 'Z')))
									{
										valid_name = 0;
										break;
									}
								}
								if (valid_name) 
								{
									strcpy(addressBook->contacts[i].name, edit_name1);
									printf("Name changed successfully!\n");
									printf("After edit:\nName: %s\nPhone: %s\nEmail: %s\n",
											addressBook->contacts[i].name,
											addressBook->contacts[i].phone,
											addressBook->contacts[i].email);
								} else 
								{
									printf("Invalid name. Name should only contain letters.\n");
								}

							}
						}
					}
				}

				else {

					printf("More than one contact found with that name.\n");
					printf("Enter the mobile number to search : ");
					char phone_search[50];
					scanf(" %[^\n]", phone_search);

					for (int j = 0; j < addressBook->contactCount; j++) 
					{
						if (strcmp(addressBook->contacts[j].phone, phone_search) == 0) 
						{
							printf("Contact found:\n");
							printf("Name: %s\nPhone: %s\nEmail: %s\n",
									addressBook->contacts[j].name,
									addressBook->contacts[j].phone,
									addressBook->contacts[j].email);

							printf("Enter a new name: ");
							char new_name[50];
							scanf(" %[^\n]", new_name);


							int valid_name = 1;
							for (int k = 0; k < 10; k++) 
							{
								if ((new_name[k] >= 'a' && new_name[k] <= 'z') || (new_name[k] >= 'A' && new_name[k] <= 'Z') || (new_name[k] == ' ')) 
								{
									valid_name = 0;
									break;
								}
							}

							if (valid_name == 0) 
							{
								strcpy(addressBook->contacts[j].name, new_name);
								printf("Name changed successfully...\n");
								printf("After edit:\nName: %s\nPhone: %s\nEmail: %s\n",
										addressBook->contacts[j].name,
										addressBook->contacts[j].phone,
										addressBook->contacts[j].email);
							} else 
							{
								printf("Invalid name. Name must be Alphabets only.\n");
							}

							break;
						}
					}
				}
				break;

				case 2:
				char edit_phone[50];
				int flag2 = 0;
				printf("Enter the contact mobile number : ");
				scanf(" %[^\n]", edit_phone);
				for(int i = 0;i < addressBook -> contactCount;i++)
				{
					if(strcmp(addressBook -> contacts[i].phone,edit_phone) == 0)
					{
						printf("Contact Found\n");
						flag2 = 1;
						printf("%s ", addressBook -> contacts[i].name);
						printf("%s ", addressBook -> contacts[i].phone);
						printf("%s\n", addressBook -> contacts[i].email);

						printf("Enter the new mobile number : ");
						char edit_phone1[50];
						scanf(" %[^\n]",edit_phone1);
M2:		    int j = 0;
			if(strlen(edit_phone1) != 10)
			{
				printf("Enter a valid mobile number...");
				goto M2;
			}
			else
			{
				int valid = 1;
				for(j = 0;j < 10;j++)
				{
					if(edit_phone1[j] >= '0'&& edit_phone1[j] <= '9')
					{
						valid = 0;
						break;
					}
				}
				if(valid == 0)
				{
					strcpy(addressBook -> contacts[i].phone,edit_phone1);
					printf("After edit : \n");

					printf("%s ", addressBook -> contacts[i].name);
					printf("%s ", addressBook -> contacts[i].phone);
					printf("%s\n", addressBook -> contacts[i].email);
					printf("Phone number changed sucessfully...");
				}
				else
				{
					printf("Invalid phone number \n");
				}
			}
			break;
					}
				}
				if(flag2 == 0)
				{
					printf("Mobile number is not found\n");
				}
				break;
				case 3:
				char edit_email[50];
				int flag3 = 0;
				printf("Enter the email ID : ");
				scanf(" %[^\n]", edit_email);
				for(int i = 0;i < addressBook -> contactCount;i++)
				{
					if(strcmp(addressBook -> contacts[i].email,edit_email) == 0)
					{
						printf("Contact Found\n");
						flag3 = 1;
						printf("%s ", addressBook -> contacts[i].name);
						printf("%s ", addressBook -> contacts[i].phone);
						printf("%s\n", addressBook -> contacts[i].email);

						printf("Enter the email ID to be editted : ");
						char edit_email1[50];
						scanf(" %[^\n]", edit_email1);
						int valid = 1;
						char* at_position = strchr(edit_email1,'@');
						char* dot_position = strchr(edit_email1,'.');
						if(at_position == NULL || dot_position == NULL || at_position > dot_position)
						{
							valid =0 ;
						}
						if(edit_email1[0] == '@' || at_position[1] == '.')
						{
							valid = 0;
						}
						if(valid == 1)
						{
							strcpy(addressBook -> contacts[i].email,edit_email1);
							printf("After edit : \n");
							printf("%s ", addressBook -> contacts[i].name);
							printf("%s ", addressBook -> contacts[i].phone);
							printf("%s\n", addressBook -> contacts[i].email);
						}
						else
						{
							printf("Invalid email address.\n");
						}
						if(flag3 == 0)
						{
							printf("Email ID not found");
						}
						break;
					}
				}
			}
	}
}
void deleteContact(AddressBook *addressBook)
{
	int flag = 0;
    int option, val;
    char searchName[50], searchPhone[15], searchEmail[50];
  
    printf("1.Name\n2.Phone_no\n3.Email\nEnter the choice to search the contact: ");
    scanf("%d", &option);

labelA:
    switch(option)
	{
			case 1:
					printf("Enter the name of the contact to edit: ");
					scanf(" %[^\n]", searchName);

    				for (int i = 0; i < addressBook->contactCount; i++)
    				{
    						if (strcmp(addressBook->contacts[i].name, searchName) == 0)
        					{
        							val = i;
            						flag = 1;
            						deleteby(addressBook, val);
							}
							else
							{
								printf("Contact Not Found");
								goto labelA;
							}
					}
					break;
			case 2:

					printf("Enter the phone_no of the contact to edit: ");
					scanf(" %[^\n]", searchPhone);

    				for (int i = 0; i < addressBook->contactCount; i++)
    				{
    						if (strcmp(addressBook->contacts[i].phone, searchPhone) == 0)
        					{
        							val = i;
            						flag = 1;
            						deleteby(addressBook, val);
							}
							else
							{
								printf("Contact Not Found");
								goto labelA;
							}
					}
					break;
			case 3:
					printf("Enter the email of the contact to edit: ");
					scanf(" %[^\n]", searchEmail);

    				for (int i = 0; i < addressBook->contactCount; i++)
    				{
    						if (strcmp(addressBook->contacts[i].email, searchEmail) == 0)
        					{
        							val = i;
            						flag = 1;
            						deleteby(addressBook, val);
							}
							else
							{
								printf("Contact Not Found");
								goto labelA;
							}
					}
					break;
	}
	if(flag == 0)
	{
			printf("Contact not found\n");
	}
	else
	{
		printf("Contact Not Found");
		goto labelA;
	}
}
void deleteby(AddressBook *addressBook, int val)
{
		//int i = 0;
		for(int j = val;j < addressBook->contactCount;j++)
		{
				strcpy(addressBook->contacts[val].name, addressBook->contacts[val + 1].name);
				strcpy(addressBook->contacts[val].phone, addressBook->contacts[val + 1].phone);
				strcpy(addressBook->contacts[val].email, addressBook->contacts[val + 1].email);
				val++;
		}
		printf("Contact deleted successfully\n");
		printf("\n\n--------------------------------------------------------------------------------------------------------\n");
}

