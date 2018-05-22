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
    mtmFlix->series = setCreate();
    mtmFlix->users = setCreate();
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
    User series_tmp=seriesCreate();
    SET_FOREACH(Series, series_tmp, mtmflix->series){
        if(getSeriesName(series_tmp)==name){
            setRemove(mtmflix->series, series_tmp);
        }
    }
}
