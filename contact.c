#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
//#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
   // saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

int validateName(char *name)
{
   for(int i = 0; name[i] != '\0'; i++)
   {
        if(isdigit(name[i]))
        {
            printf("Please enter alphabets only.\n");
            return 0;
        }
   }
   return 1;
}

int validatePhone(char *phone)
{
    int len = strlen(phone);
    if(len != 10)
    {
       printf("Please enter 10 digits.\n");
       return 0;
    }
    for(int i = 0; phone[i] != '\0'; i++)
    {
        if(!isdigit(phone[i]))
        {
            printf("Please enter digits only.\n");
            return 0;
        }
    }
    return 1;
}

int validateMail(char *email)
{
    char *temp1 = strchr(email,'@');
    char *temp2 = strstr(email,".com");
    if(temp2 - temp1 < 2)
    {
        printf("Invalid email format! Please check and enter the correct one.\n");
        return 0;
    }
    return 1;
}

int isPhoneUnique(AddressBook *addressBook, char *phone) 
{
    for(int i = 0; i < addressBook->contactCount; i++) 
    {
        if(strcmp(addressBook->contacts[i].phone, phone) == 0) 
        {
            printf("Phone number already exists! Please enter a unique phone number.\n");
            return 0;
        }
    }
    return 1;
}

int isEmailUnique(AddressBook *addressBook, char *email) 
{
    for(int i = 0; i < addressBook->contactCount; i++) 
    {
        if(strcmp(addressBook->contacts[i].email, email) == 0) 
        {
            printf("Email already exists! Please enter a unique email.\n");
            return 0;
        }
    }
    return 1;
}

void createContact(AddressBook *addressBook)
{
    if(addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("You already saved 100 contacts. No space left!");
        return;
    }

	Contact newcon;
    getchar();

    printf("Enter the name: ");
    scanf("%[^\n]", newcon.name);
    if(!validateName(newcon.name))
    {
        return;
    }
    
    do 
    {
        printf("Enter the phone number: ");
        scanf("%s", newcon.phone);
    } while(!validatePhone(newcon.phone) || !isPhoneUnique(addressBook, newcon.phone));
    
    do 
    {
        printf("Enter the email id: ");
        scanf("%s", newcon.email);
    } while(!validateMail(newcon.email) || !isEmailUnique(addressBook, newcon.email));
    
    addressBook->contacts[addressBook->contactCount] = newcon;
    addressBook->contactCount++;

    printf("Your contact saved successfully.\n");
}

void searchContact(AddressBook *addressBook) 
{
    int opt, flag = 0;
    printf("Please choose one option to search by:\n");
    printf("1. Name\n2. Phone Number\n3. Email id:\n");
    printf("Enter your choice: ");
    scanf("%d", &opt);
    
    switch(opt)
    {
        case 1: 
        {
            char searchName[50];
            getchar();
            printf("Enter the name to search: ");
            scanf("%[^\n]", searchName);
            if(!validateName(searchName)) 
            {
                return;
            }
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].name, searchName) == 0)
                {
                    printf("%s\t", addressBook->contacts[i].name);
                    printf("%s\t", addressBook->contacts[i].phone);
                    printf("%s\t", addressBook->contacts[i].email);
                    flag = 1;
                    break;
                }
            }
            break;
        }
        case 2: 
        {   
            char searchPhone[15];
            getchar();
            printf("Enter the phone number to search: ");
            scanf("%s", searchPhone);
            if(!validatePhone(searchPhone))
            {
                return;
            }

            for(int i = 0; i < addressBook->contactCount; i++) 
            {
                if(strcmp(addressBook->contacts[i].phone, searchPhone) == 0)
                {
                    printf("%s\t", addressBook->contacts[i].name);
                    printf("%s\t", addressBook->contacts[i].phone);
                    printf("%s\t", addressBook->contacts[i].email);
                    flag = 1;
                    break;
                }
            }
            break;
        }
        case 3: 
        {   
            char searchMail[50];
            getchar();
            printf("Enter the email id to search: ");
            scanf("%s", searchMail);
            if(!validateMail(searchMail))
            {
                return;
            }

            for(int i = 0; i < addressBook->contactCount; i++) 
            {
                if(strcmp(addressBook->contacts[i].email, searchMail) == 0)
                {
                    printf("%s\t", addressBook->contacts[i].name);
                    printf("%s\t", addressBook->contacts[i].phone);
                    printf("%s\t", addressBook->contacts[i].email);
                    flag = 1;
                    break;
                }
            }
            break;
        }
        default: 
            printf("Invalid choice. Please select from the options above.\n");
            break;
    }
    if(flag == 0)
    {
        printf("The contact you are searching for is not available.\n");
    }
}

void validate_editcontact(Contact *contact)
{
    printf("Enter the new name to save: ");
    getchar(); 
    scanf("%[^\n]", contact->name);

    if (!validateName(contact->name))
    {
        return;
    }

    do {
        printf("Enter the new mobile number to save: ");
        scanf("%s", contact->phone);
    } while (!validatePhone(contact->phone));

    do {
        printf("Enter the new email id to save: ");
        scanf("%s", contact->email);
    } while (!validateMail(contact->email));

    printf("Successfully modified contact details.\n");
}

void editContact(AddressBook *addressBook)
{
	int opt, flag = 0;
    printf("Please select any one option to edit contact:\n");
    printf("1. Name\n2. Phone Number\n3. Email Id:\n");
    printf("Enter your choice: ");
    scanf("%d", &opt);
    
    switch(opt)
    {
        case 1: 
        {   
            char searchName[50];
            getchar();
            printf("Enter the name of the contact you want to edit: ");
            scanf("%[^\n]", searchName);
            if(!validateName(searchName))
            {
                return;
            }
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].name, searchName) == 0)
                {
                    validate_editcontact(&addressBook->contacts[i]);
                    flag = 1; 
                }
            }
            if(!flag)
            {
                printf("Contact not found.\n");
            }
            break;
        }
        case 2: 
        {   
            char searchPhone[15];
            getchar();
            do {
                printf("Enter the phone number of the contact you want to edit: ");
                scanf("%s", searchPhone);
            } while(!validatePhone(searchPhone));
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].phone, searchPhone) == 0)
                {
                    validate_editcontact(&addressBook->contacts[i]);
                    flag = 1; 
                }
            }
            if(!flag)
            {
                printf("Contact not found.\n");
            }
            break;
        }
        case 3: 
        {   
            char searchMail[50];
            getchar();
            do{
                printf("Enter the mail id of the contact you want to edit: ");
                scanf("%s", searchMail);
            } while(!validateMail(searchMail));
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].email, searchMail) == 0)
                {
                    validate_editcontact(&addressBook->contacts[i]);
                    flag = 1; 
                }
            }
            if(!flag)
            {
                printf("Contact not found.\n");
            }
            break;
        }
        default: 
            printf("Invalid option, please select from the options above.");        
    }       
} 
void deleteContact(AddressBook *addressBook)
{
    int opt, flag = 0;
    printf("Please select an option to delete contact by:\n");
    printf("1. Name\n2. Phone Number\n3. Email Id:\n");
    printf("Enter your choice: ");
    scanf("%d", &opt);

    switch(opt)
    {
        case 1: 
        {
            char searchName[50];
            getchar();
            printf("Enter the name of the contact you want to delete: ");
            scanf("%[^\n]", searchName);
            if(!validateName(searchName))
            {
                return;
            }
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].name, searchName) == 0)
                {
                    // Shift contacts to the left to overwrite the deleted contact
                    for(int j = i; j < addressBook->contactCount - 1; j++)
                    {
                        addressBook->contacts[j] = addressBook->contacts[j + 1];
                    }
                    addressBook->contactCount--;
                    flag = 1;
                    printf("Contact deleted successfully.\n");
                    break;
                }
            }
            break;
        }
        case 2: 
        {   
            char searchPhone[15];
            getchar();
            do {
                printf("Enter the phone number of the contact you want to delete: ");
                scanf("%s", searchPhone);
            } while(!validatePhone(searchPhone));

            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].phone, searchPhone) == 0)
                {
                    // Shift contacts to the left to overwrite the deleted contact
                    for(int j = i; j < addressBook->contactCount - 1; j++)
                    {
                        addressBook->contacts[j] = addressBook->contacts[j + 1];
                    }
                    addressBook->contactCount--;
                    flag = 1;
                    printf("Contact deleted successfully.\n");
                    break;
                }
            }
            break;
        }
        case 3: 
        {   
            char searchMail[50];
            getchar();
            do{
                printf("Enter the email id of the contact you want to delete: ");
                scanf("%s", searchMail);
            } while(!validateMail(searchMail));

            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].email, searchMail) == 0)
                {
                    // Shift contacts to the left to overwrite the deleted contact
                    for(int j = i; j < addressBook->contactCount - 1; j++)
                    {
                        addressBook->contacts[j] = addressBook->contacts[j + 1];
                    }
                    addressBook->contactCount--;
                    flag = 1;
                    printf("Contact deleted successfully.\n");
                    break;
                }
            }
            break;
        }
        default: 
            printf("Invalid choice. Please select from the options above.\n");
            return;
    }

    if(flag == 0)
    {
        printf("Contact not found.\n");
    }
}

