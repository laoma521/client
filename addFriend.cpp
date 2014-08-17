#include "addFriend.h"

AddFriendBox::AddFriendBox(Links *tLink,
						   const QString &myAccount,
						   QWidget *parent/* =0 */)
						   : tempBox(2, parent), link(tLink)
{
	setWindowTitle( tr("add Friend") );
	setFixedSize(200, 150);

	message.kind = REQUEST_FRIEND;
	message.sender = myAccount;
	
	setLabelName(tr("other's account"), tr("Authentication information"));
	connect(link, SIGNAL(newReplySignal(qint32)), this, SLOT(result(qint32)));
}

AddFriendBox::~AddFriendBox()
{
	
}

void AddFriendBox::clickedOKButton()
{
	TempStrings temp;
	temp = getInformation();

	if(temp.one.isEmpty())
	{
		QMessageBox::critical(this, tr("Error"),
			tr("The other's account can not be empty"));
		return;
	}

	message.receiver = temp.one;
	message.text = temp.two;
	if(message.sender == message.receiver)
	{
		QMessageBox::critical(this, tr("Error"),
			tr("Your friends can't be your own"));
		return;
	}
	link->addFriendRequest(message);
	setAllEnabled(false);
}

void AddFriendBox::result(qint32 replyKind)
{
	if(FRIEDN_NO_ACCOUNT == replyKind)
		QMessageBox::critical(this, tr("Error"), 
			tr("No this user, please try again"));
	
	else if(ALREAD_FRIENDS == replyKind)
		QMessageBox::critical(this, tr("Error"), 
			tr("They are already good friends or have sended the friend request"));
	else if(FRIEND_REQUESTED == replyKind)
	{
		QMessageBox::information(this, tr("Congratulations"),
			tr("The friend's requestion have been sended, is waiting for reply"));
		close();
	}
	setAllEnabled(true);
}

void AddFriendBox::closeEvent(QCloseEvent *event)
{
	disconnect(link, SIGNAL(newReplySignal(qint32)), this, SLOT(result(qint32)));
}
