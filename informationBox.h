#ifndef INFORMATIONBOX_H_
#define INFORMATIONBOX_H_

#include "constant.h"
#include "links.h"
#include "ui_informationBox.h"

class InformationBox : public QWidget
{
	Q_OBJECT
private:
	Ui::informationBoxForm ui;
	QString confirmPwd;					//验证的密码
	int num;
	static const int all = 134;			//总头像数

public:
	InformationBox(QWidget *parent);
	virtual ~InformationBox() = 0;

	UserInformation getUserInformation();
	void setAllReadOnly(bool enable);

	void setMostReadOnly(bool enable);

	void setSomeReadOnly(bool enable);

	void setUserInformation(const UserInformation &userInf);

	bool informationIsAllow();

	bool passwordIsAllow();

	public slots:
		void clickedQuitButton();
		virtual void clickedOKButton() = 0;
		void clickedPastButton();
		void clickedNextButton();
		void clickedHelpButton();
};

#endif
