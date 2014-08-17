#ifndef ADDFRIEND_H_
#define ADDFRIEND_H_

#include "constant.h"
#include "tempBox.h"
#include "links.h"

class AddFriendBox : public tempBox
{
	Q_OBJECT
private:
	Message message;
	Links *link;

protected:
	void closeEvent(QCloseEvent *event);

public:
	AddFriendBox(Links *tLink,
		const QString &myAccount, QWidget *parent=0);
	~AddFriendBox();

	public slots:
		void clickedOKButton();
		void result(qint32 replyKind);					
};

#endif

