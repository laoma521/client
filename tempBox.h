#ifndef TEMPBOX_H_
#define TEMPBOX_H_

#include "constant.h"

#include "constant.h"
#include "links.h"

class tempBox : public QWidget
{
	Q_OBJECT
private:
	int n;
	QLabel *firstLabel;
	QLabel *secondLabel;
	QLabel *thirdLabel;
	QLineEdit *firstLineEdit;
	QLineEdit *secondLineEdit;
	QLineEdit *thirdLineEdit;
	QPushButton *OKPushButton;
	QPushButton *closePushButton;

public:
	tempBox(int temp, QWidget *parent);
	virtual ~tempBox() = 0;

	void setLabelName(const QString &one="",
		const QString &two="",
		const QString &three="");
	TempStrings getInformation() const;
	void setPasswordStyle();
	void setAllEnabled(bool enable);

	public slots:
		virtual void clickedOKButton() = 0;
		void clickedCloseButton();
};

#endif
