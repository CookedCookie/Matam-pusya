#include <stdio.h>
#include <stdlib.h>
typedef struct user * User;

User userCreate();
void setUserName(User user, const char* name);
void setUserAge(User user, int age);
const char* getUserName(User user);
