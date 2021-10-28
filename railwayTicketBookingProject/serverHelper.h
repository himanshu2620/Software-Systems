#include "user.h"
#include "train.h"
#include "booking.h"

char welcomeMenu[] = "Login as:\n1.Normal Account User\n2.Agent Account User\n3.Administrator\n4.Exit\nPlease enter your choice:";
char normalUserPrompt[] = "Press:\n1 for Booking a Ticket\n2 for Viewing Previous Bookings\n3 for Updating a Booking\n4 to cancel a booking\n0 to exit";
char trainIdInputMsg[] = "Enter the trainId of the train to book the seat";
char seatsInputMsg[] = "Enter the number of seats to be booked";




void handleNormalUser(int nsd){
  write(nsd, normalUserPrompt, sizeof(normalUserPrompt)); // show the prompt
  char ch[1];
  read(nsd,ch,sizeof(ch));
  if(ch[0]=='1'){
    // book  a ticket

    // take input for trainId
    write(nsd,trainIdInputMsg,sizeof(trainIdInputMsg));
    char inputTrainId[10];
    read(nsd,inputTrainId,sizeof(inputTrainId));

    // take input for number of seats to be booked
    write(nsd,seatsInputMsg,sizeof(seatsInputMsg));
    char buff[10];
    read(nsd,buff,sizeof(buff));
    int seatsToBeBooked = atoi(buff);

    // trainId , userId, seatsBooked
    // find train and decrement seatsAvailable
    // create a booking and enter these 3 details
  }
}
void addUserAccount(int nsd){
  struct user currUser;
  read(nsd,&currUser,sizeof(struct user));

  char *path = malloc(strlen("database/users/")  + 1);
  strcpy(path,"database/users/");
  //strcat(path,currUser.userId);
  //strcat(path,currUser.userId);
  int fd = open(path, O_CREAT | O_RDWR , 0744);
  if(fd==-1){
    write(nsd,"Couldn't create user account",sizeof("Couldn't create user account"));
  }
  else{
    int rb = write(fd,&currUser,sizeof(struct user));
    if(rb==-1){
      write(nsd,"Couldn't create user account",sizeof("Couldn't create user account"));
    }
    else{
      write(nsd,"User Account created Successfully",sizeof("User Account created Successfully"));
    }
  }
  close(fd);
  free(path);
}

void deleteUserAccount(int nsd){
    struct user currUser;
    read(nsd,&currUser,sizeof(struct user));
    char *path = malloc(strlen("database/users/")  + 1);
    strcpy(path,"database/users/");
    //strcat(path,currUser.userId);
    int fd = unlink(path);
    if(fd==-1){
      write(nsd,"Error in deleting as account with supplied user id not found",sizeof("Error in deleting as account with supplied user id not found"));
    }
    else{
      write(nsd,"User Account Deleted Successfully",sizeof("User Account Deleted Successfully"));
    }
    close(fd);
    free(path);
}

void addTrain(int nsd){
  int status = 1;
  struct train currTrain;
  read(nsd, &currTrain, sizeof(struct train));
  currTrain.status = 1; // train is up and running
  int fd = open("database/trains.dat", O_CREAT | O_APPEND | O_RDWR , 0666);
  write(fd, (char* )&currTrain, sizeof(struct train));
  write(nsd, &status, sizeof(status));
  //handleAdminUser(nsd);
}

void deleteTrain(int nsd){
    struct train currTrain;
    read(nsd,&currTrain,sizeof(struct train));
    char *path = malloc(strlen("database/trains/") + strlen(currTrain.trainName) + 1);
    strcpy(path,"database/trains/");
    strcat(path,currTrain.trainName);
    int fd = unlink(path);
    if(fd==-1){
      write(nsd,"Error in deleting Train details",sizeof("Error in deleting Train details"));
    }
    else{
      write(nsd,"Train details Deleted Successfully",sizeof("Train details Deleted Successfully"));
    }
    close(fd);
    free(path);
}

void handleAdminUser(int nsd){
    char ch[1];
    read(nsd,ch,sizeof(ch));
    if(ch[0]=='1'){ // for modifying User accounts
        char choice[1];
        read(nsd,choice,sizeof(choice));
        if(choice[0]=='1'){ // Add account
            addUserAccount(nsd);
        }
        else if(choice[0]=='2'){ // delete account
            deleteUserAccount(nsd);
        }
        else if(choice[0]=='3'){ // update account

        }
        else if(choice[0]=='4'){ // search for an account

        }
    }
    else if(ch[0]=='2'){ // for modifying Train info
        char choice[1];
        read(nsd,choice,sizeof(choice));
        if(choice[0]=='1'){ // Add a train account
            addTrain(nsd);
        }
        else if(choice[0]=='2'){ // delete a train
            deleteTrain(nsd);
        }
        else if(choice[0]=='3'){ // update train details

        }
        else if(choice[0]=='4'){ // search for a train

        }
    }
}

int checkUserExists(int nsd, char userName[]){
  struct user currUser;
  int flag = 0;
  int fd = open("database/users.dat", O_CREAT | O_APPEND | O_RDWR , 0666);
  while(read(fd, (char* )&currUser, sizeof(struct user))){
    if(strcmp(userName, currUser.userName)==0){
      flag = 1;
      break;
    }
  }
  close(fd);
  return flag;
}

void handleMainMenu(int nsd){
  char ch[5];
  read(nsd,ch,sizeof(ch));
  if(ch[0]=='1'){
    printf("normal \n");
    handleNormalUser(nsd);
  }
  else if(ch[0]=='2'){
    printf("agent \n");
  }
  else if(ch[0]=='3'){
    printf("admin \n");
    handleAdminUser(nsd);
  }
  else{
    printf("exiting the system now...\n");
  }
}

void signUp(int nsd){
  struct user currUser;
  read(nsd, &currUser, sizeof(struct user));
  int status = 1;
  if(!checkUserExists(nsd, currUser.userName)){
      int fd = open("database/users.dat", O_CREAT | O_APPEND | O_RDWR , 0666);
      currUser.status = 0;
      currUser.userId = ((rand()%3097)*2) + 1000;
      write(fd, (char* )&currUser, sizeof(struct user));
  }
  else{
    status = -1;
  }
  write(nsd, &status, sizeof(status));
  handleMainMenu(nsd);
}



void handleInitialLogin(int nsd){
    //write(nsd, welcomeMenu, sizeof(welcomeMenu));
    sleep(0.01);
    char choice[1];
    read(nsd, choice, sizeof(choice));
    if(choice[0]=='1'){
      signUp(nsd);
    }
    else if(choice[0]=='2'){
      handleMainMenu(nsd);
    }
}
