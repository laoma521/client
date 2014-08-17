#ifndef LOGINBOX_H_
#define LOGINBOX_H_

#include "constant.h"
#include "links.h"
#include "register.h"
#include "window.h"
#include "ui_loginBox.h"

class LoginBox : public QWidget
{
	Q_OBJECT
private:
	Ui::loginBoxForm ui;
	ServerNode serverNode;
	LoginInformation logInf;		//储存登录信息
	Links *link;
	bool getString(QString &str, QLineEdit *edit, const QString &message);

public:
	LoginBox(QWidget *parent = 0);
	~LoginBox();

	public slots:
		void result(qint32 replyKind);
		void checkConnectionButton();
		void clickedRegisterButton();
		void clickedLoginButton();	

		void setStatus(const QString &statusStr);
		void ServerDisconnected();
		void initStatus();
		void connectedStatus();
};

#endif
