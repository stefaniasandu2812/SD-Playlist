// Copyright 2020 <Sandu Stefania-Cristina>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TEMA1_H_
#define TEMA1_H_

struct Song{
	char TAG[3];
	char Title[30];
	char Artist[30];
	char Album[30];
	char Year[4];
};

struct Node{
	struct Song *track;
	struct Node *next, *prev;
};

struct Playlist{
	int size;
	struct Node *head, *tail, *cursor;
};

// functiile folosite sunt implementate in tema1.c

void init_playlist(struct Playlist *playlist);

void ADD_FIRST(struct Playlist *playlist, char *new_song, FILE *fout);

void ADD_LAST(struct Playlist *playlist, char *new_song, FILE *fout);

void ADD_AFTER(struct Playlist *playlist, char *new_song, FILE *fout);

void DEL_FIRST(struct Playlist *playlist, FILE *fout);

void DEL_LAST(struct Playlist *playlist, FILE *fout);

void DEL_CURR(struct Playlist *playlist, FILE *fout);

void DEL_SONG(struct Playlist *playlist, char *song_to_del, FILE *fout);

void MOVE_NEXT(struct Playlist *playlist, FILE *fout);

void MOVE_PREV(struct Playlist *playlist, FILE *fout);

void SHOW_FIRST(struct Playlist *playlist, FILE *fout);

void SHOW_LAST(struct Playlist *playlist, FILE *fout);

void SHOW_CURR(struct Playlist *playlist, FILE *fout);

void SHOW_PLAYLIST(struct Playlist *playlist, FILE *fout);

void read_file_mp3(struct Song *song, FILE *f);

void free_playlist(struct Playlist **pp_playlist);

#endif  // TEMA1_H_ //
