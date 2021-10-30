struct user{
  int userId;
  char userName[30];
  char password[30];
  int status; // 1 for active , 0 for inactive
  int type; // 0 for Normal User, 1 for Agent
};
