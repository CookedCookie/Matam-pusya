#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include "set.h"

struct user{
    const char* name;
    int age;
    Set friends;
    Set movies;
};

User userCreate(){
    User user = malloc(sizeof(*user));
    user->friends = setCreate();
    user->movies = setCreate();
    user->age = -1;
    user->name = "";
}

void setUserName(User user, const char* name){
    strcpy(user->name, name);
}

void setUserAge(User user, int age){
    user->age=age;
}

const char* getUserName(User user){
    return user->name;
}
