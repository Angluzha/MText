#include "FriendList.h"

FriendList::FriendList()
{
	canSee_ = false;
}

void FriendList::setCanSee()
{
	if (canSee_)
		canSee_ = false;
	else
		canSee_ = true;
}

void FriendList::setFriendClass(string _friendClass)
{
	friendClass_ = _friendClass;
}
void FriendList::setTalkTable(string _talkTable)
{
	talkTable_ = _talkTable;
}
string FriendList::getFriendClass()
{
	return friendClass_;
}
string FriendList::getTalkTable()
{
	return talkTable_;
}