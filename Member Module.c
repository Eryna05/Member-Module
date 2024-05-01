#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#pragma warning (disable:4996)
#pragma warning (disable:6031)

typedef struct {
    char name[30];
    char gender;
    char id[10];
    char bookId[10];
    char password[10];
    char contactNum[12];
    int schedule;
} Member;

Member members[100];
int memberCount = 0;

void choiceMenu();
void addMember();
void searchMember();
void modifyMember();
void displayMember();
void deleteMember();
void saveFileMember();
void loadFileMember();
void changePasswordMember(Member* member);

//entering password before proceed to the choiceMenu()
void main() {
    int correctPass = 1234;
    int inputPass;
    int attempts = 3;

    do {
        printf("Enter Password: ");
        scanf("%d", &inputPass);
        printf("\n");

        if (inputPass == correctPass) {
            choiceMenu();
        }
        
        //if user enter password wrong 3 times
        else {
            attempts--;
            printf("Incorrect Password! You have %d attempts left\n", attempts);
            if (attempts <= 0) {
                
                //to let user to decide whether to change the password
                printf("Do you want to change password?\n");
                printf("If yes enter [1], if no enter [2]: ");
                
                int choice;
                scanf("%d", &choice);
                if (choice == 1) {
                    changePasswordMember(&members[0]);
                }
                else {
                    return;
                }
            }
        }
    } while (attempts > 0);


    int choice;
    do {
        choiceMenu();
    } while (1);

}

//to choose the function 
void choiceMenu() {
    int choice;

    printf("=============================\n");
    printf("||       MEMBER MODULE     ||\n");
    printf("=============================\n");
    printf("1. Add Member\n");
    printf("2. Search for Member\n");
    printf("3. Modify Member\n");
    printf("4. Display Member\n");
    printf("5. Delete Member\n");
    printf("6. Exit\n");

    printf("Please enter your choice [1-6]: ");
    scanf(" %d", &choice);
    printf("\n");

    switch (choice) {
    case 1:
        addMember();
        break;

    case 2:
        searchMember();
        break;

    case 3:
        modifyMember();
        break;

    case 4:
        displayMember();
        break;

    case 5:
        deleteMember();
        break;

    case 6:
        exit(0);

    default:
        printf("Please enter a valid choice!\n");
    }
}

//to add memeber
void addMember() {
    Member add;
    int i = 0, addMore;
    FILE* fptr;
    fptr = fopen("member.bin", "ab");
    if (fptr == NULL) {
        printf("Error Opening File\n");
        exit(0);
    }


    printf("\n");
    printf("===========================\n");
    printf("||       ADD MEMBER      ||\n");
    printf("===========================\n");
    do {
        if (i >= 100) {
            printf("The number of members has reached the maximum number.\n");
            fclose(fptr);
            return;
        }
        i++;
        printf("Enter Full Name: ");
        scanf(" %[^\n]", add.name);

        printf("Enter Gender [M/F]: ");
        scanf(" %c", &add.gender);

        //validation when user dont enter M or F
        while (add.gender != 'M' && add.gender != 'F') {
            printf("Please enter a valid gender [M/F]: ");
            scanf(" %c", &add.gender);
        }

        printf("Enter MemberID: ");
        scanf(" %s", add.id);

        printf("Enter Member BookingID: ");
        scanf(" %s", add.bookId);

        printf("Enter Contact Number: ");
        scanf(" %s", add.contactNum);

        printf("Enter Member password: ");
        scanf(" %s", add.password);


        printf("\n");


        fwrite(&add, sizeof(Member), 1, fptr);
        printf("Member added successfully:)\n");

        //to let the user decide to add more member
        printf("Do you want to add another member? \n");
        printf("If yes enter [1], if no enter [2]: ");
        scanf("%d", &addMore);
        printf("\n");

        while (addMore != 1 && addMore != 2) {
            printf("Please enter a valid number (1 or 2): ");
            scanf("%d", &addMore);
            printf("\n");
        }

    } while (addMore == 1);
    fclose(fptr);

}

//for changing the password if user forget password
void changePasswordMember(Member* member) {
    char changePass[10];
    printf("Enter new password: ");
    scanf(" %s", &changePass);
    strcpy(member->password, changePass);

    printf("Password successfully changed:)\n");
    printf("Enter your password again: ");
    scanf(" %s", &changePass);
    strcpy(member->password, changePass);
}

//to search for a specific member
void searchMember() {
    FILE* fptr;
    char search[10];
    int i = 0;
    bool found = false;

    fptr = fopen("member.bin", "rb");
    if (fptr == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    printf("==============================\n");
    printf("||       SEARCH MEMBER      ||\n");
    printf("==============================\n");

    printf("Enter the ID of the member you want to find: ");
    scanf("%s", search);

    while (fread(&members[i], sizeof(Member), 1, fptr) != 0) {
        if (strcmp(&members[i].id, search) == 0) {
            printf("\n");
            printf("MEMBER PROFILE\n");
            printf("==============\n");
            printf("Name: %s\n", members[i].name);
            printf("Gender: %c\n", members[i].gender);
            printf("MemberID: %s\n", members[i].id);
            printf("BookingID: %s\n", members[i].bookId);
            printf("Contact Number: %s\n", members[i].contactNum);
            printf("Member Password: %s\n", members[i].password);
            printf("\n");
            found = true;
            i++;
            break;
        }
    }

    if (!found) {
        printf("Member not found:(\n");
    }

    fclose(fptr);
}

//to save the file
void saveFileMember() {
    FILE* fptr;
    fptr = fopen("member.bin", "wb");

    if (fptr == NULL) {
        printf("Error Opening File");
        exit(0);
    }

    fwrite(members, sizeof(Member), memberCount, fptr);
    fclose(fptr);
}

//to load the file
void loadFileMember() {
    FILE* fptr;
    fptr = fopen("member.bin", "rb");

    if (fptr == NULL) {
        printf("Member Not Found");
        exit(0);
    }
    fread(members, sizeof(Member), memberCount, fptr);
    fclose(fptr);

    memberCount = 0;
    for (int i = 0; i < 100; i++) {
        if (members[i].name[0] == '\0') {
            break;
        }
        memberCount++;
    }
}

//to modify a member
void modifyMember() {
    char modify[10];

    printf("\n");
    printf("=============================\n");
    printf("||      MODIFY MEMBER      ||\n");
    printf("=============================\n");

        printf("Enter the memberID you want to modify: ");
        scanf("%9s", modify);

        FILE* fptr;
        fptr = fopen("member.bin", "rb+");
        if (fptr == NULL) {
            printf("Error opening file\n");
            exit(-1);
        }

        int found = 0;
        while (fread(&members[memberCount], sizeof(Member), 1, fptr) != 0) {
            if (strcmp(members[memberCount].id, modify) == 0) {
                found = 1;
                break;
            }
            memberCount++;
        }

        if (found) {
            printf("Enter new Full Name: ");
            scanf(" %[^\n]", members[memberCount].name);

            printf("Enter new Gender: ");
            scanf(" %c", &members[memberCount].gender);

            //validation when user dont enter M or F
            while (members[memberCount].gender != 'M' && members[memberCount].gender != 'F') {
                printf("Please enter a valid gender [M/F]: ");
                scanf(" %c", &members[memberCount].gender);
            }

            printf("Enter new BookingID: ");
            scanf(" %s", members[memberCount].bookId);

            printf("Enter new Contact Number: ");
            scanf(" %s", members[memberCount].contactNum);

            fseek(fptr, memberCount * sizeof(Member), SEEK_SET);
            fwrite(&members[memberCount], sizeof(Member), 1, fptr);

            printf("Member modified successfully:)\n");
        }
        else {
            printf("Member Not Found...:(\n");
        }

        fclose(fptr);

}

//to display all the members
void displayMember() {
    int i = 0;
    FILE* fptr;
    fptr = fopen("member.bin", "rb");
    if (fptr == NULL) {
        printf("Error Opening File\n");
        exit(-1);
    }

    printf("\n");

    printf("==============================\n");
    printf("||      DISPLAY MEMBER      ||\n");
    printf("==============================\n");
    while (fread(&members[i], sizeof(Member), 1, fptr) != 0) {
        printf("Name                Gender            MemberID     MemberBookID    Contact Number   Member Password\n");
        printf("===================================================================================================\n");
        printf("%s\t\t%c\t\t%s\t\t%s\t\t%s\t%s\n", members[i].name, members[i].gender, members[i].id, members[i].bookId, members[i].contactNum, members[i].password);
        printf("===================================================================================================\n");
        printf("\n");
        i++;
    }

    fclose(fptr);
}

//to delete a member
void deleteMember() {
    char delete[10];
    int i = 0;
    bool found = false;

    printf("\n");
    printf("=============================\n");
    printf("||      DELETE MEMBER      ||\n");
    printf("=============================\n");

    printf("Enter the MemberID you want to delete: ");
    scanf("%s", delete);
    printf("\n");

    FILE* fptr;
    fptr = fopen("member.bin", "rb+");
    if (fptr == NULL) {
        printf("Error opening file\n");
        exit(-1);
    }

    while (fread(&members[i], sizeof(Member), 1, fptr) != 0) {
        if (strcmp(members[i].id, delete) == 0) {
            found = true;
        }
        else {
            i++;
        }
    }

    fclose(fptr);

    fptr = fopen("member.bin", "wb");
    if (fptr == NULL) {
        printf("Error opening file\n");
        exit(-1);
    }

    for (int j = 0; j < i; j++) {
        fwrite(&members[j], sizeof(Member), 1, fptr);
    }

    fclose(fptr);

    if (found) {
        printf("Member deleted successfully:)\n");
    }
    else {
        printf("Member Not Found...:(\n");
    }
}

 


