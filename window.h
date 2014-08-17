#ifndef WINDOW_H_
#define WINDOW_H_

#include "constant.h"
#include "friendbutton.h"
#include "ui_window.h"

class Window : public QWidget
{
	Q_OBJECT
private:
	Ui::windowForm ui;
	Links *link;
	ServerNode serverNode;
	FriendInformation myself;
	QVBoxLayout *layout;
	QGroupBox *groupBox;
	UserInformation userInf;
	QMap<QString, FriendButton*> friButtonMap;

	bool continueToClose();

	void createFolder() const;

	void createTrayIcon();

	void setMyInformation();

	void addFriendButton(const FriendInformation &friInf);

	void changeFriendStatus(const QString &acc, qint32 status);

	void deleteFromTable(const QString &acc);

	void setStatusFromInt(int n, QString &str) const;

	void setButtonStatus(const FriendInformation &friInf, QToolButton *button);

	void processingMessage(const Message &mes);
	void receivedTalkMessage(const Message &mes);
	void replyAddFriend(const Message &tMessage);

	QSystemTrayIcon *trayIcon;
	QAction *onlineAction;
	QAction *talkAction;
	QAction *busyAction;
	QAction *leaveAction;
	QAction *disturbAction;
	QAction *stealthAction;
	QAction *quitAction;
	QMenu *trayIconMenu;
	QSignalMapper *trayMap;
	
protected:
	void closeEvent(QCloseEvent *event);

public:
	Window(const ServerNode &node, 
		const QVector<FriendInformation> &friendsVec,
		QWidget *parent=0);
	~Window();

	public slots:
		void result(qint32 replyKind);
		void clickedAddFriendButton();
		void clickedChangeInfButton();
		void clickedChangePwdButton();
		void clickedAboutButton();
		void sendRoomsMessage(const Message &mes);
		void changeState(int n);
		void changeInformation(int avaNum, 
			QString name, QString about);
		void removeFriend(const QString &peerAccount);

		void iconActivated(QSystemTrayIcon::ActivationReason reason);
		void linkDisconnected();
};

#endif
