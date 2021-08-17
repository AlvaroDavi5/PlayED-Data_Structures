#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "friendship.h"


struct friend_list
{
	int size;
	Friend *first;
	Friend *last;
};

struct friend
{
	int index;
	User *friend;
	Friend *next;
};

struct usr
{
	int index;
	char *name;
	FriendList *friends;
	PlaylistList *playlists;
	User *next;
};


/* -------------- Friend Manipulation -------------- */
Friend * makeFriend(User *usr)
{
	Friend *friend = (Friend *) malloc(sizeof(Friend));

	friend->index = -1;
	friend->friend = usr;
	friend->next = NULL;

	return friend;
}

void showFriend(Friend *friend)
{
	printf("%s \n", (friend->friend)->name);
}


/* -------------- FriendList Manipulation -------------- */
FriendList * initFriendList()
{
	FriendList *list = (FriendList *) malloc(sizeof(FriendList));

	list->size = 0;
	list->first = NULL;
	list->last = NULL;

	return list;
}

void addFriendToHead(FriendList *list, Friend *fnd)
{
	if (list->first == NULL)
	{
		list->last = fnd;
		fnd->next = NULL;
	}
	else
	{
		fnd->next = list->first;
	}

	list->first = fnd;
	list->size += 1;

	Friend *current = list->first;
	for (int i = 0; i < list->size; i++)
	{
		(current)->index = i;
		current = (current)->next;
	}
}

void addFriendToTail(FriendList *list, Friend *fnd)
{
	fnd->next = NULL;

	if (list->first == NULL)
	{
		list->first = fnd;
	}
	else
	{
		list->last->next = fnd;
	}

	fnd->index = list->size;
	list->last = fnd;
	list->size += 1;
}

Friend * getFriendByPosition(FriendList *list, fptrCompare compareFunction, int position)
{
	Friend *current = list->first;

	while (current != NULL)
	{
		if (compareFunction((current)->index, position) == 0)
		{
			return current;
		}

		current = (current)->next;
	}

	return NULL;
}

Friend * getFriendByName(FriendList *list, char *name)
{
	Friend *current = list->first;

	while (current != NULL)
	{
		if (strcmp(((current)->friend)->name, name) == 0)
		{
			return current;
		}

		current = (current)->next;
	}

	return NULL;
}

void deleteFriend(FriendList *list, Friend *fnd)
{
	Friend *current = list->first;

	if (fnd == list->first)
	{
		if (list->first->next == NULL)
		{
			list->first = list->last;
		}
		else
		{
			list->first = list->first->next;
		}
	}
	else
	{
		while (current != NULL && (current)->next != fnd)
		{
			current = (current)->next;
		}
		if (current != NULL && (current)->next == fnd)
		{
			(current)->next = fnd->next;
			((current)->next)->index = fnd->index;
		}
	}

	free(fnd);
	list->size -= 1;

	Friend *indexedFriend = list->first;
	for (int i = 0; i < list->size; i++)
	{
		if (indexedFriend != NULL)
		{
			indexedFriend->index = i;
			indexedFriend = indexedFriend->next;
		}
	}
}

void destroyFriendList(FriendList *list)
{
	Friend *current = list->first;
	Friend *next = NULL;

	while (current != NULL)
	{
		next = (current)->next;

		deleteFriend(list, current);
		current = next;
	}

	free(list);
}

void displayFriendList(FriendList *list)
{
	Friend *current = list->first;

	while (current != NULL)
	{
		printf("Friend %d: \n", (current)->index);
		showFriend(current);
		current = (current)->next;
	}
}
