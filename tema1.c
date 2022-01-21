// Copyright 2020 <Sandu Stefania-Cristina>
#include "./tema1.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// functie pentru initializarea playlist-ului
void init_playlist(struct Playlist *playlist){
	playlist->head = NULL;
	playlist->tail = NULL;
	playlist->cursor = NULL;
	playlist->size = 0;
}
void ADD_FIRST(struct Playlist *playlist, char *new_song, FILE *fout){
	struct Node *new, *curr;
	new = malloc(sizeof(struct Node));
	struct Song *song;
	song = malloc(sizeof(struct Song));
	new->track = malloc(sizeof(struct Song));
	char song_file[100];
	int n = snprintf(song_file, sizeof(song_file), "%s", "./songs/");
	snprintf(song_file + n, sizeof(song_file) + n, "%s", new_song);
	FILE *f;
	f = fopen(song_file, "rb");
	if(f == NULL){
		fprintf(fout, "Error opening file\n");
		return;
	}
	read_file_mp3(song, f);
	if(playlist->head == NULL){  // cazul in care playlist-ul e gol
		memcpy(new->track->Title, song->Title, 30*sizeof(char));
		memcpy(new->track->Artist, song->Artist, 30*sizeof(char));
		memcpy(new->track->Album, song->Album, 30*sizeof(char));
		memcpy(new->track->Year, song->Year, 4*sizeof(char));
		new->next = NULL;
		new->prev = NULL;
		playlist->head = new;
		playlist->tail = new;
		playlist->size++;
		playlist->cursor = playlist->head;
		free(song);
		return;
	}
	curr = playlist->head;
	// verific daca exista deja in playlist cantecul respectiv
	while(curr != NULL && strcmp(curr->track->Title, song->Title) != 0){
		curr = curr->next;
	}
	if(curr != NULL){
		DEL_SONG(playlist, new_song, fout);
	}
	memcpy(new->track->Title, song->Title, 30*sizeof(char));
	memcpy(new->track->Artist, song->Artist, 30*sizeof(char));
	memcpy(new->track->Album, song->Album, 30*sizeof(char));
	memcpy(new->track->Year, song->Year, 4*sizeof(char));
	new->next = playlist->head;
	new->prev = NULL;
	playlist->head->prev = new;
	playlist->head = new;
	playlist->size++;
	free(song);
}
void ADD_LAST(struct Playlist *playlist, char *new_song, FILE *fout){
	struct Node *new, *curr;
	new = malloc(sizeof(struct Node));
	struct Song *song;
	song = malloc(sizeof(struct Song));
	new->track = malloc(sizeof(struct Song));
	char song_file[100];
	int n = snprintf(song_file, sizeof(song_file), "%s", "./songs/");
	snprintf(song_file + n, sizeof(song_file) + n, "%s", new_song);
	FILE *f;
	f = fopen(song_file, "rb");
	if(f == NULL){
		fprintf(fout, "Error opening file\n");
		return;
	}
	read_file_mp3(song, f);
	if(playlist->head == NULL){  // cazul in care playlist-ul e gol
		memcpy(new->track->Title, song->Title, 30*sizeof(char));
		memcpy(new->track->Artist, song->Artist, 30*sizeof(char));
		memcpy(new->track->Album, song->Album, 30*sizeof(char));
		memcpy(new->track->Year, song->Year, 4*sizeof(char));
		new->next = NULL;
		new->prev = NULL;
		playlist->head = new;
		playlist->tail = new;
		playlist->size++;
		playlist->cursor = playlist->head;
		free(song);
		return;
	}
	curr = playlist->head;
	// verific daca exista deja in playlist cantecul respectiv
	while(curr != NULL && strcmp(curr->track->Title, song->Title) != 0){
		curr = curr->next;
	}
	if(curr != NULL){
		DEL_SONG(playlist, new_song, fout);
	}
	memcpy(new->track->Title, song->Title, 30*sizeof(char));
	memcpy(new->track->Artist, song->Artist, 30*sizeof(char));
	memcpy(new->track->Album, song->Album, 30*sizeof(char));
	memcpy(new->track->Year, song->Year, 4*sizeof(char));
	new->next = NULL;
	new->prev = playlist->tail;
	playlist->tail->next = new;
	playlist->tail = new;
	playlist->size++;
	free(song);
}
void ADD_AFTER(struct Playlist *playlist, char *new_song, FILE *fout){
	if(playlist == NULL){
		return;
	}
	if(playlist->cursor == NULL){
		return;
	}
	if(playlist->head == NULL){
		return;
	}
	struct Node *new, *curr;
	struct Song *song;
	char song_file[100];
	int n = snprintf(song_file, sizeof(song_file), "%s", "./songs/");
	snprintf(song_file + n, sizeof(song_file) + n, "%s", new_song);
	FILE *f;
	f = fopen(song_file, "rb");
	if(f == NULL){
		fprintf(fout, "Error opening file\n");
		return;
	}
	song = malloc(sizeof(struct Song));
	read_file_mp3(song, f);
	if(strcmp(playlist->cursor->track->Title, song->Title) == 0){
		free(song);
		return;
	}
	if(playlist->cursor->next == NULL){
		ADD_LAST(playlist, new_song, fout);
		free(song);
		return;
	}
	new = malloc(sizeof(struct Node));
	new->track = malloc(sizeof(struct Song));
	curr = playlist->head;
	// verific daca exista deja in playlist cantecul respectiv
	while(curr != NULL && strcmp(curr->track->Title, song->Title) != 0){
		curr = curr->next;
	}
	if(curr != NULL){
		DEL_SONG(playlist, new_song, fout);
	}
	memcpy(new->track->Title, song->Title, 30*sizeof(char));
	memcpy(new->track->Artist, song->Artist, 30*sizeof(char));
	memcpy(new->track->Album, song->Album, 30*sizeof(char));
	memcpy(new->track->Year, song->Year, 4*sizeof(char));
	new->next = playlist->cursor->next;
	playlist->cursor->next->prev = new;
	playlist->cursor->next = new;
	new->prev = playlist->cursor;
	playlist->size++;
	free(song);
}
void DEL_FIRST(struct Playlist *playlist, FILE *fout){
	struct Node *first;
	if(playlist->head == NULL){  // cazul in care playlist-ul e gol
		fprintf(fout, "Error: delete from empty playlist\n");
		return;
	}
	// mut cursorul daca acesta este capul listei
	if(playlist->cursor == playlist->head){
		if(playlist->head->next != NULL){
			playlist->cursor = playlist->head->next;
		} else{
			playlist->cursor = NULL;
		}
	}
	first = playlist->head;
	if(playlist->head->next == NULL){
		playlist->head = NULL;
		playlist->tail = NULL;
		free(first->track);
		free(first);
		playlist->size--;
		return;
	} else{
		playlist->head = first->next;
		playlist->head->prev = NULL;
		free(first->track);
		free(first);
		playlist->size--;
		return;
	}
}
void DEL_LAST(struct Playlist *playlist, FILE *fout){
	struct 	Node *last;
	if(playlist->head == NULL){  // cazul in care playlist-ul e gol
		fprintf(fout, "Error: delete from empty playlist\n");
		return;
	}
	// mut cursorul daca acesta este coada listei
	if(playlist->cursor == playlist->tail){
		if(playlist->tail->prev != NULL){
			playlist->cursor = playlist->tail->prev;
		} else{
			playlist->cursor = NULL;
		}
	}
	last = playlist->tail;
	if(playlist->tail->prev == NULL){
		playlist->tail = playlist->head = NULL;
		free(last->track);
		free(last);
		playlist->size--;
		return;
	} else{
		last->prev->next = NULL;
		playlist->tail = last->prev;
		free(last->track);
		free(last);
		playlist->size--;
		return;
	}
}
void DEL_CURR(struct Playlist *playlist, FILE *fout){
	struct Node *curr;
	if(playlist->cursor == NULL){
		fprintf(fout, "Error: no track playing\n");
		return;
	}
	curr = playlist->cursor;
	if(playlist->head->next == NULL){
		playlist->cursor = NULL;
		playlist->head = NULL;
		playlist->tail = NULL;
		free(curr->track);
		free(curr);
		playlist->size--;
		return;
	}
	if(curr->next != NULL){
		playlist->cursor = curr->next;
	} else{
		playlist->cursor = curr->prev;
	}
	if(curr == playlist->head){
		DEL_FIRST(playlist, fout);
		return;
	}
	if(curr == playlist->tail){
		DEL_LAST(playlist, fout);
		return;
	}
	curr->prev->next = curr->next;
	curr->next->prev = curr->prev;
	free(curr->track);
	free(curr);
	playlist->size--;
}
void DEL_SONG(struct Playlist *playlist, char *song_to_del, FILE *fout){
	struct Node *curr;
	struct Song *song;
	song = malloc(sizeof(struct Song));
	char song_file[100];
	int n = snprintf(song_file, sizeof(song_file), "%s", "./songs/");
	snprintf(song_file + n, sizeof(song_file) + n, "%s", song_to_del);
	FILE *f;
	f = fopen(song_file
		, "rb");
	if(f == NULL){
		fprintf(fout, "Eroare fisier\n");
	}
	if(playlist->head == NULL){  // cazul in care playlist-ul e gol
		fprintf(fout, "Error: no song found to delete\n");
		free(song);
		return;
	}
	read_file_mp3(song, f);
	if(strcmp(playlist->cursor->track->Title, song->Title) == 0){
		DEL_CURR(playlist, fout);
		free(song);
		return;
	}
	curr = playlist->head;
	while(curr != NULL && strcmp(curr->track->Title, song->Title) != 0){
		curr = curr->next;
	}
	if(curr == NULL){
		fprintf(fout, "Error: no song found to delete\n");
		free(song);
		return;
	}
	if(curr == playlist->head){
		DEL_FIRST(playlist, fout);
		free(song);
		return;
	}
	if(curr == playlist->tail){
		DEL_LAST(playlist, fout);
		free(song);
		return;
	}
	curr->prev->next = curr->next;
	curr->next->prev = curr->prev;
	free(curr->track);
	free(curr);
	playlist->size--;
	free(song);
}
void MOVE_NEXT(struct Playlist *playlist, FILE *fout){
	struct Node *curr;
	if(playlist->cursor == NULL){
		fprintf(fout, "Error: no track playing\n");
		return;
	}
	if(playlist->cursor->next == NULL){
		return;
	}
	curr = playlist->cursor;
	playlist->cursor = curr->next;
}
void MOVE_PREV(struct Playlist *playlist, FILE *fout){
	struct Node *curr;
	if(playlist->cursor == NULL){  // cazul in care nu exista cursorul
		fprintf(fout, "Error: no track playing\n");
		return;
	}
	if(playlist->cursor->prev == NULL){
		return;
	}
	curr = playlist->cursor;
	playlist->cursor = curr->prev;
}
void SHOW_FIRST(struct Playlist *playlist, FILE *fout){
	struct Node *first;
	if(playlist->head == NULL){  // cazul in care playlist-ul e gol
		fprintf(fout, "Error: show empty playlist\n");
		return;
	}
	first = playlist->head;
	fprintf(fout, "Title: %.30s\n", first->track->Title);
	fprintf(fout, "Artist: %.30s\n", first->track->Artist);
	fprintf(fout, "Album: %.30s\n", first->track->Album);
	fprintf(fout, "Year: %.4s\n", first->track->Year);
}
void SHOW_LAST(struct Playlist *playlist, FILE *fout){
	struct Node *last;
	if(playlist->head == NULL){  // cazul in care playlist-ul e gol
		fprintf(fout, "Error: show empty playlist\n");
		return;
	}
	last = playlist->tail;
	fprintf(fout, "Title: %.30s\n", last->track->Title);
	fprintf(fout, "Artist: %.30s\n", last->track->Artist);
	fprintf(fout, "Album: %.30s\n", last->track->Album);
	fprintf(fout, "Year: %.4s\n", last->track->Year);
}
void SHOW_CURR(struct Playlist *playlist, FILE *fout){
	struct Node *curr;
	if(playlist->head == NULL){  // cazul in care playlist-ul e gol
		fprintf(fout, "Error: show empty playlist\n");
		return;
	}
	curr = playlist->cursor;
	fprintf(fout, "Title: %.30s\n", curr->track->Title);
	fprintf(fout, "Artist: %.30s\n", curr->track->Artist);
	fprintf(fout, "Album: %.30s\n", curr->track->Album);
	fprintf(fout, "Year: %.4s\n", curr->track->Year);
}
void SHOW_PLAYLIST(struct Playlist *playlist, FILE *fout){
	struct Node *curr;
	if(playlist->head == NULL){  // cazul in care playlist-ul e gol
		fprintf(fout, "[]\n");
		return;
	}
	// daca playlist-ul are un singur element
	if(playlist->head->next == NULL){
		fprintf(fout, "[%.30s]", playlist->head->track->Title);
		fprintf(fout, "\n");
		return;
	}
	curr = playlist->head;
	fprintf(fout, "[");
	while(curr != NULL){
		fprintf(fout, "%.30s", curr->track->Title);
		if(curr->next != NULL){
			fprintf(fout, "; ");
		}
		curr = curr->next;
	}
	fprintf(fout, "]\n");
}
// functie pentru citirea din fisierele binare
void read_file_mp3(struct Song *song, FILE *f){
	// ma pozitionez in fisier cu -94 fata de sfarsit pentru a evita TAG-ul
	fseek(f, -94, SEEK_END);
	fread(song->Title, 30*sizeof(char), 1, f);
	fread(song->Artist, 30*sizeof(char), 1, f);
	fread(song->Album, 30*sizeof(char), 1, f);
	fread(song->Year, 4*sizeof(char), 1, f);
	fclose(f);
}
// functie pentru dezalocarea memoriei
void free_playlist(struct Playlist **pp_playlist){
	struct Node *curr, *next;
	curr = (*pp_playlist)->head;
	while(curr != NULL){
		next = curr->next;
		free(curr->track);
		free(curr);
		curr = next;
	}
	free(*pp_playlist);
	*pp_playlist = NULL;
}
int main(int argc, char *argv[]){
	// validarea numarului de parametri
	if(argc < 2){
		printf("Error input\n");
		return -1;
	}
	struct Playlist *playlist;
	playlist = malloc(sizeof(struct Playlist));
	init_playlist(playlist);
	char c;
	char *command;
	command = malloc(100*sizeof(char));
	char *command1;
	int i, q;
	FILE *fin, *fout;
	fin = fopen(argv[1], "rt");
	fout = fopen(argv[2], "w");
	// deschiderea fisierelor de intrare si de iesire
	if(fin == NULL){
		printf("Error opening file \n");
	}
	if(fout == NULL){
		printf("Error opening file \n");
	}
	fscanf(fin, "%d", &q);
	fscanf(fin, "%c", &c);
	for(i = 0; i < q; i++){
		command1 = NULL;
		fgets(command, 100, fin);
		char *rest_for_command;
		rest_for_command = command;
		command1 = __strtok_r(command, " \n", &rest_for_command);
	if(strcmp(command1, "ADD_FIRST") == 0){
		command1 = __strtok_r(NULL, "\n", &rest_for_command);
		ADD_FIRST(playlist, command1, fout);
	}
	if(strcmp(command1, "ADD_LAST") == 0){
		command1 = __strtok_r(NULL, "\n", &rest_for_command);
		ADD_LAST(playlist, command1, fout);
	}
	if(strcmp(command1, "ADD_AFTER") == 0){
		command1 = __strtok_r(NULL, "\n", &rest_for_command);
		ADD_AFTER(playlist, command1, fout);
	}
	if(strcmp(command1, "DEL_FIRST") == 0){
		DEL_FIRST(playlist, fout);
	}
	if(strcmp(command1, "DEL_LAST") == 0){
		DEL_LAST(playlist, fout);
	}
	if(strcmp(command1, "DEL_CURR") == 0){
		DEL_CURR(playlist, fout);
	}
	if(strcmp(command1, "DEL_SONG") == 0){
		command1 = __strtok_r(NULL, "\n", &rest_for_command);
		DEL_SONG(playlist, command1, fout);
	}
	if(strcmp(command1, "MOVE_PREV") == 0){
		MOVE_PREV(playlist, fout);
	}
	if(strcmp(command1, "MOVE_NEXT") == 0){
		MOVE_NEXT(playlist, fout);
	}
	if(strcmp(command1, "SHOW_FIRST") == 0){
		SHOW_FIRST(playlist, fout);
	}
	if(strcmp(command1, "SHOW_LAST") == 0){
		SHOW_LAST(playlist, fout);
	}
	if(strcmp(command1, "SHOW_CURR") == 0){
		SHOW_CURR(playlist, fout);
	}
	if(strcmp(command1, "SHOW_PLAYLIST") == 0){
		SHOW_PLAYLIST(playlist, fout);
	}
}
free(command);
	free_playlist(&playlist);
	fclose(fin);
	fclose(fout);
}
