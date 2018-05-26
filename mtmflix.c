#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mtmflix.h"
#include "series.h"
#include "user.h"
#include "set.h"

struct mtmFlix_t {
    Set series;
    Set users;
};

MtmFlix mtmFlixCreate() {
    MtmFlix mtmFlix = malloc(sizeof(*mtmFlix));
    copySetElements* tmp_copySetElements = malloc(sizeof(*tmp_copySetElements));
    freeSetElements* tmp_freeSetElements = malloc(sizeof(*tmp_freeSetElements));
    compareSetElements* tmp_compareSetElements = malloc(sizeof(*tmp_compareSetElements));
    mtmFlix->series = setCreate(*tmp_copySetElements, *tmp_freeSetElements, *tmp_compareSetElements);
    mtmFlix->users = setCreate(*tmp_copySetElements, *tmp_freeSetElements, *tmp_compareSetElements);
    return mtmFlix;
}

void mtmFlixDestroy(MtmFlix mtmflix){
    free(mtmflix);
}

MtmFlixResult mtmFlixAddUser(MtmFlix mtmflix, const char* username, int age){
    int counter=0;
    if(username==NULL){
        return MTMFLIX_NULL_ARGUMENT;
    }
    if(age<MTM_MIN_AGE || age>MTM_MAX_AGE){
        return MTMFLIX_ILLEGAL_AGE;
    }
    for(int i=0; i<(int)strlen(username); i++){
        if((username[i]<=90 && username[i]>=65)||(username[i]>=97 &&username[i]<=122)){
                counter++;
                continue;
        }
        if(username[i]>=48 && username[i]<=57){
            continue;
        }
        return MTMFLIX_ILLEGAL_USERNAME;
    }
    if(counter==0) return MTMFLIX_ILLEGAL_USERNAME;
    User user_tmp=userCreate();
    setUserName(user_tmp, username);
    setUserAge(user_tmp, age);
    if(setIsIn(mtmflix->users, user_tmp)){
        return MTMFLIX_USERNAME_ALREADY_USED;
    }
    setAdd(mtmflix->users, user_tmp);
    return MTMFLIX_SUCCESS;
}

MtmFlixResult mtmFlixRemoveUser(MtmFlix mtmflix, const char* username){
    User user_tmp=userCreate();
    SET_FOREACH(User, user_tmp, mtmflix->users){
        if(getUserName(user_tmp)==username){
            setRemove(mtmflix->users, user_tmp);
        }
    }
    return MTMFLIX_SUCCESS;
}

MtmFlixResult mtmFlixAddSeries(MtmFlix mtmflix, const char* name, int episodesNum, Genre genre, int* ages, int episodeDuration){
    if(name == NULL || mtmflix == NULL){
        return MTMFLIX_NULL_ARGUMENT;
    }
    if(episodesNum<=0) return MTMFLIX_ILLEGAL_EPISODES_NUM;
    if(episodeDuration<=0) return MTMFLIX_ILLEGAL_EPISODES_DURATION;
    int counter = 0;
    for(int i=0; i<(int)strlen(name); i++){
        if((name[i]<=90 && name[i]>=65)||(name[i]>=97 && name[i]<=122)){
                counter++;
                continue;
        }
        if(name[i]>=48 && name[i]<=57){
            continue;
        }
        return MTMFLIX_ILLEGAL_SERIES_NAME;
    }
    if(counter==0) return MTMFLIX_ILLEGAL_SERIES_NAME;
    Series series_tmp = seriesCreate();
    setSeriesAges(series_tmp, ages);
    setSeriesEpisodeDuration(series_tmp, episodeDuration);
    setSeriesEpisodesNum(series_tmp, episodesNum);
    setSeriesGenre(series_tmp, genre);
    setSeriesName(series_tmp, name);
    if(setIsIn(mtmflix->series, series_tmp)){
        return MTMFLIX_SERIES_ALREADY_EXISTS;
    }
    setAdd(mtmflix->series, series_tmp);
    return MTMFLIX_SUCCESS;
}

MtmFlixResult mtmFlixRemoveSeries(MtmFlix mtmflix, const char* name){
    Series series_tmp=seriesCreate();
    SET_FOREACH(Series, series_tmp, mtmflix->series){
        if(getSeriesName(series_tmp)==name){
            setRemove(mtmflix->series, series_tmp);
        }
    }
    return MTMFLIX_SUCCESS;
}

MtmFlixResult mtmFlixReportSeries(MtmFlix mtmflix, int seriesNum, FILE* outputStream) {
    Set tmp_set = setCopy(mtmflix->series);
    Series* tmp_series = malloc(sizeof(*tmp_series));
    Series* tmp_series2 = malloc(sizeof(*tmp_series2));
    Genre* cur_genre = malloc(sizeof(*cur_genre));
    cur_genre = COMEDY;
    bool flag = false;
    SET_FOREACH(Series, tmp_series, tmp_set){
        if(getSeriesGenre(tmp_series) != COMEDY){
            setRemove(tmp_set, tmp_series);
        }
    }
    SET_FOREACH(Series, tmp_series, tmp_set) {
        SET_FOREACH(Series, tmp_series2, tmp_set) {
            if(tmp_series == tmp_series2)
                flag = true;
            if(strcmp(getSeriesName(tmp_series), getSeriesName(tmp_series2)) > 0 && ) {
                tmp_series = tmp_series2;
            }
        }
    }
}

MtmFlixResult mtmFlixSeriesJoin(MtmFlix mtmflix, const char* username, const char* seriesName) {
    if(username == NULL || seriesName == NULL || mtmflix == NULL) {
        return MTMFLIX_NULL_ARGUMENT;
    }
    bool flag = false;
    Series* tmp_series = malloc(sizeof(*tmp_series));
    SET_FOREACH(Series, tmp_series, mtmflix->series) {
        if(strcmp(getSeriesName(tmp_series), seriesName) == 0) {
            flag = true;
            break;
        }
    }
    if(!flag) {
        return MTMFLIX_SERIES_DOES_NOT_EXIST;
    }
    flag = false;
    User* tmp_user = malloc(sizeof(*tmp_user));
    SET_FOREACH(User, tmp_users, mtmflix->users) {
        if(strcmp(getUserName(tmp_user), username) == 0) {
            flag = true;
            break;
        }
    }
    if(!flag) {
        return MTMFLIX_USER_DOES_NOT_EXIST;
    }
    if(getAge(tmp_user) < getMinimalAge(tmp_user) || getAge(tmp_user) > getMaximalAge(tmp_user)) {
        return MTMFLIX_USER_NOT_IN_THE_RIGHT_AGE;
    }
    addFavoriteMovie(tmp_user, tmp_series);
    return MTMFLIX_SUCCESS;
}

MtmFlixResult mtmFlixSeriesLeave(MtmFlix mtmflix, const char* username, const char* seriesName) {
    if(username == NULL || seriesName == NULL || mtmflix == NULL) {
        return MTMFLIX_NULL_ARGUMENT;
    }
    bool flag = false;
    User* tmp_user = malloc(sizeof(*tmp_user));
    SET_FOREACH(User, tmp_users, mtmflix->users) {
        if(strcmp(getUserName(tmp_user), username) == 0) {
            flag = true;
            break;
        }
    }
    if(!flag) {
        return MTMFLIX_USER_DOES_NOT_EXIST;
    }
    flag = false;
    Series* tmp_series = malloc(sizeof(*tmp_series));
    SET_FOREACH(Series, tmp_series, mtmflix->series) {
        if(strcmp(getSeriesName(tmp_series), seriesName) == 0) {
            setRemove(getFavoriteMovies(tmp_user), tmp_series);
            flag = true;
            break;
        }
    }
    if(!flag) {
        return MTMFLIX_SERIES_DOES_NOT_EXIST;
    }
    return MTMFLIX_SUCCESS;
}

MtmFlixResult mtmFlixAddFriend(MtmFlix mtmflix, const char* username1, const char* username2) {
    if(mtmflix == NULL || username1 == NULL || username2 == NULL) {
        return MTMFLIX_NULL_ARGUMENT;
    }
    bool flag = false;
    User* tmp_user1 = malloc(sizeof(*tmp_user));
    SET_FOREACH(User, tmp_users, mtmflix->users) {
        if(strcmp(getUserName(tmp_user), username1) == 0) {
            flag = true;
            break;
        }
    }
    if(!flag) {
        return MTMFLIX_USER_DOES_NOT_EXIST;
    }
    flag = false;
    User* tmp_user2 = malloc(sizeof(*tmp_user));
    SET_FOREACH(User, tmp_users, mtmflix->users) {
        if(strcmp(getUserName(tmp_user), username2) == 0) {
            flag = true;
            break;
        }
    }
    if(!flag) {
        return MTMFLIX_USER_DOES_NOT_EXIST;
    }
    setAdd(getFriends(tmp_user1), tmp_user2);
    return MTMFLIX_SUCCESS;
}

MtmFlixResult mtmFlixRemoveFriend(MtmFlix mtmflix, const char* username1, const char* username2) {
    if(mtmflix == NULL || username1 == NULL || username2 == NULL) {
        return MTMFLIX_NULL_ARGUMENT;
    }
    bool flag = false;
    User* tmp_user1 = malloc(sizeof(*tmp_user));
    SET_FOREACH(User, tmp_users, mtmflix->users) {
        if(strcmp(getUserName(tmp_user), username1) == 0) {
            flag = true;
            break;
        }
    }
    if(!flag) {
        return MTMFLIX_USER_DOES_NOT_EXIST;
    }
    flag = false;
    User* tmp_user2 = malloc(sizeof(*tmp_user));
    SET_FOREACH(User, tmp_users, mtmflix->users) {
        if(strcmp(getUserName(tmp_user), username2) == 0) {
            flag = true;
            break;
        }
    }
    if(!flag) {
        return MTMFLIX_USER_DOES_NOT_EXIST;
    }
    setRemove(getFriends(tmp_user1), tmp_user2);
    return MTMFLIX_SUCCESS;
}
