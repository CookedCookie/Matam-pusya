#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include "set.h"

struct user{
    const char* name;
    int age;
    Set friends;
    Set favorite_movies;
};

User userCreate(){
    User user = malloc(sizeof(*user));
    user->friends = setCreate();
    user->favorite_movies = setCreate();
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

void addFavoriteMovie(User user, Series series) {
    setAdd(user->favorite_movies, series);
}

Set getFavoriteMovies(User user) {
    return user->favorite_movies;
}

int getAge(User user) {
    return user->age;
}

Set getFriends(User user) {
    return user->friends;
}
