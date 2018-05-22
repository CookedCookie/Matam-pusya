#include <stdio.h>
#include <stdlib.h>

#include "mtm_ex3.h"

typedef struct series * Series;

Series seriesCreate();
void setSeriesName(Series series, const char* name);
void setSeriesEpisodesNum(Series series, int episodesNum);
void setSeriesGenre(Series series, Genre genre);
void setSeriesAges(Series series, int* ages);
void setSeriesEpisodeDuration(Series series, int episodeDuration);
const char* getSeriesName(Series series);
