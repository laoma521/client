#ifndef CHANGEINF_H_
#define CHANGEINF_H_

#include "constant.h"
#include "informationBox.h"

class ChangeInf : public InformationBox
{
	Q_OBJECT
private:
	Links *link;
	UserInformation userInf;				//个人详细信息
	FriendInformation friInf;
	QString tPassward;						//存储验证密码

protected:
	void closeEvent(QCloseEvent *event);

public:
	ChangeInf(Links *tLink,
		const QString &acc, QWidget *parent=0);
	~ChangeInf();

signals:
	void changeInformationSignal(int, QString, QString);

	public slots:
		void clickedOKButton();
		void result(qint32 replyKind);
};

#endif
