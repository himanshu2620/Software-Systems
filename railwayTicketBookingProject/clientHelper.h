#include "user.h"

void handleAdminClient(int sfd){
  printf("Enter 1 to add/modify/delete User Details \n");
  printf("Enter 2 to add/modify/delete Train Details \n");
  char ch[1];
  scanf("%s", ch);
  write(sfd, ch, sizeof(ch)); //
  if(ch[0]=='1'){
    printf("Enter 1 to add a User account\n");
    printf("Enter 2 to delete a User account\n");
    printf("Enter 3 to modify a User account\n");
    printf("Enter 4 to search for a User account\n");
    char choice[1];
    scanf("%s", choice);
    write(sfd, choice, sizeof(choice));
    struct user currUser;

    if(choice[0] == '1'){ // Add a User Account
        printf("----------------Add User Account Menu--------------\n");
        printf("Enter a user id:\n");
        scanf("%s", currUser.userId);
        printf("Enter your user name\n");
        scanf("%s", currUser.userName);
        printf("Enter your password\n");
        scanf("%s", currUser.password);
        for(int i=0;i<100;i++){
           currUser.bookings[i] = 0; // Initialize the bookings array
        }
        currUser.count = 0;
        write(sfd, &currUser,sizeof(struct user));
    }
    else if(choice[0] == '2'){

    }
    else if(choice[0] == '3'){

    }
    else if(choice[0] == '4'){

    }
  }
  else if(ch[0]=='2'){

  }
  else{
    printf("Enter Correct Input\n");
  }
}
