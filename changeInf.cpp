#include "changeInf.h"

ChangeInf::ChangeInf(Links *tLink,
					 const QString &acc,
					 QWidget *parent/* =0 */)
: InformationBox(parent), link(tLink)
{
	setWindowTitle( tr("Modify Personal Information") );
	
	link->getUserRequest(acc);
	setSomeReadOnly(true);
	connect(link, SIGNAL(newReplySignal(qint32)), 
		this, SLOT(result(qint32)));
}

ChangeInf::~ChangeInf()
{
	
}

void ChangeInf::clickedOKButton()
{
	if(!informationIsAllow())
		return;
	userInf = getUserInformation();
	userInf.password = tPassward;
	link->changeInformationRequest(userInf);
	setAllReadOnly(true);
}

void ChangeInf::result(qint32 replyKind)
{
	if(GET_USER_INF_SUCCESS == replyKind)
	{
		UserInformation userInf;
		userInf = link->getUserInformation();
		setUserInformation(userInf);
		tPassward = userInf.password;
	}
	else if(CHANGE_INFORMATION_SUCCESS == replyKind)
	{
		QMessageBox::information(this, tr("Congratulations"), 
			tr("Modify Personal Information successfully"));
		emit changeInformationSignal(userInf.avatarNumber, 
			userInf.nickName, userInf.aboutMyself);
		close();
	}
	setMostReadOnly(false);
}

void ChangeInf::closeEvent(QCloseEvent *event)
{
	disconnect(link, SIGNAL(newReplySignal(qint32)), this, SLOT(result(qint32)));
}
