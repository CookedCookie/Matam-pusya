#include <stdio.h>
#include <stdlib.h>
#include "series.h"
#include <string.h>

struct series {
    const char* name;
    int episodesNum;
    Genre genre;
    int* ages;
    int episodeDuration;
};

Series seriesCreate(){
    Series series = malloc(sizeof(*series));
    series->ages=[-1, -1];
    series->episodeDuration=-1;
    series->name = "";
    series->episodesNum=0;
}

void setSeriesName(Series series, const char* name){
    strcpy(series->name, name);
}

void setSeriesEpisodesNum(Series series, int episodesNum){
    series->episodesNum = episodesNum;
}

void setSeriesGenre(Series series, Genre genre){
    series->genre = genre;
}

void setSeriesAges(Series series, int* ages){
    if(ages == NULL){
        series->ages[0]=MTM_MIN_AGE;
        return;
    }
    if(ages[0]<MTM_MIN_AGE){
        series->ages[0]=MTM_MIN_AGE;
    }
    else{
        series->ages[0]=ages[0];
    }
    if(ages[1]>MTM_MAX_AGE){
        series->ages[1]=MTM_MAX_AGE;
    }
    else{
        series->ages[1]=ages[1];
    }
}

void setSeriesEpisodeDuration(Series series, int episodeDuration){
    series->episodeDuration = episodeDuration;
}
