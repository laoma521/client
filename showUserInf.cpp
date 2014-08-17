#include "showUserInf.h"

ShowUserInf::ShowUserInf(Links *tLink,
						 const QString &acc,
						 QWidget *parent)
: InformationBox(parent), link(tLink)
{
	setWindowTitle( tr("friend's information") );
	setAllReadOnly(true);

	link->getUserRequest(acc);

	connect(link, SIGNAL(newReplySignal(qint32)), 
		this, SLOT(result(qint32)));
}

ShowUserInf::~ShowUserInf()
{
	
}

void ShowUserInf::clickedOKButton()
{
	close();
}

void ShowUserInf::result(qint32 replyKind)
{
	if(GET_USER_INF_SUCCESS == replyKind)
	{
		UserInformation userInf;
		userInf = link->getUserInformation();
		setUserInformation(userInf);
	}
}

void ShowUserInf::closeEvent(QCloseEvent *event)
{
	disconnect(link, SIGNAL(newReplySignal(qint32)), this, SLOT(result(qint32)));
}
