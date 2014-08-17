#include "register.h"

RegisterBox::RegisterBox(Links *tlink, QWidget *parent)
: InformationBox(parent), link(tlink)
{
	setWindowTitle( tr("New user registration") );
	connect(link, SIGNAL(newReplySignal(qint32)), this, SLOT(result(qint32)));
}

RegisterBox::~RegisterBox()
{
	
}

void RegisterBox::result(qint32 replyKind)
{
	if(REGISTER_EXIST == replyKind)
		QMessageBox::critical(this, tr("Error"), tr("This user name has been registered"));
	else if(REGISTER_SUCCESS == replyKind)
	{
		QMessageBox::information(this, tr("Congratulations"), tr("registration successful"));
		close();
	}
	setAllReadOnly(false);
}

void RegisterBox::clickedOKButton()
{
	if(!informationIsAllow() || !passwordIsAllow())
		return;
	userInf = getUserInformation();
	userInf.status = OFFLINE;
	link->registerRequest(userInf);
	setAllReadOnly(true);
}

void RegisterBox::closeEvent(QCloseEvent *event)
{
	disconnect(link, SIGNAL(newReplySignal(qint32)), this, SLOT(result(qint32)));
}
