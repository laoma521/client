#include "changePwd.h"

ChangePassword::ChangePassword(Links *tLink, 
							   const QString &acc,
							   QWidget *parent/* =0 */)
: tempBox(3, parent), account(acc), link(tLink)
{
	setWindowTitle( tr("Change password") );
	resize(200, 100);

	setLabelName(tr("Please enter the old password"),
		tr("Please enter the new password"),
		tr("Please enter the new password again"));
	setPasswordStyle();
	connect(link, SIGNAL(newReplySignal(qint32)), this, SLOT(result(qint32)));
}

ChangePassword::~ChangePassword()
{
	
}

void ChangePassword::clickedOKButton()
{
	TempStrings temp = getInformation();

	QRegExp regExp;
	regExp.setPattern("^[A-Za-z0-9]{6,20}$");
	if(!regExp.exactMatch(temp.two))
	{
		QMessageBox::critical(this, tr("Error"), 
			tr("new password's Format is wrong. Please try again"));
		return;
	}
	if(temp.two != temp.three)
	{
		QMessageBox::critical(this, tr("Error"), tr("The two new passwords are different"));
		return;
	}

	temp.three = account;

	link->changePasswordRequest(temp);
	setAllEnabled(false);
}

void ChangePassword::result(qint32 replyKind)
{
	if(OLD_PWD_IS_WRONG == replyKind)
		QMessageBox::critical(this, tr("Error"),
			tr("The old password is wrong, please try again"));
	else if(CHANGE_PWD_SUCCESS)
	{
		QMessageBox::information(this, tr("Congratulation"), 
			tr("Change password success"));
		close();
	}
}

void ChangePassword::closeEvent(QCloseEvent *event)
{
	disconnect(link, SIGNAL(newReplySignal(qint32)), this, SLOT(result(qint32)));
}
