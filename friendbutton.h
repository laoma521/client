#ifndef FRIENDBUTTON_H_
#define FRIENDBUTTON_H_

#include "constant.h"
#include "links.h"
#include "chatRoom.h"
#include "addFriend.h"
#include "showUserInf.h"
#include "changeInf.h"
#include "remark.h"
#include "changePwd.h"

class FriendButton : public QToolButton
{
	Q_OBJECT
private:
	QString myAccount;
	QString myName;
	QString strStatus;
	FriendInformation friInf;
	bool isOpen;

	Links *link;
	Chatroom *room;
	QMenu *menu;

	void getStatusFromInt(int n, QString &str) const;
	void creatMenu();

public:
	FriendButton(Links *tLink, const FriendInformation &theFriend, 
		const QString &acc, const QString &name, QWidget *parent=0);
	~FriendButton();
	void openChatRoom();
	void setButtonStatus();
	void closeChatRoom();

	bool isRoomOpen() const
	{	return isOpen;	}
	Chatroom *getRoomPoint() const
	{	return room;	}
	FriendInformation &getInformation()
	{	return friInf;	}
	FriendInformation getInformation() const
	{	return friInf;	}

signals:
	void deleteFriendSignal(const QString &peerAccount);

	public slots:
		void clickedFriendButton();
		void clickedRightButton(const QPoint &);
		void clickedShowInformation();
		void clickedChangeRemark();
		void clickedRemoveFriend();
		void chatRoomQuit();
		void changeRemark(const QString &newRemark);
		void changeStatus(int status);
};

#endif
