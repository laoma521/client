#include "remark.h"

ChangeRemark::ChangeRemark(Links *tLink,
						   const Message &mes,
						   QWidget *parent)
						   : tempBox(1, parent), link(tLink),
						   message(mes)
{
	setWindowTitle( tr("Change remark") );
	resize(200, 100);

	setLabelName( tr("Please enter the new remark") );
	connect(link, SIGNAL(newReplySignal(qint32)), this, SLOT(result(qint32)));
}

ChangeRemark::~ChangeRemark()
{
	
}

void ChangeRemark::clickedOKButton()
{
	TempStrings temp = getInformation();
	message.text = temp.one;
	link->changeRemarkRequest(message);
	setAllEnabled(false);
}

void ChangeRemark::result(qint32 replyKind)
{
	if(CHANGE_REMARK_SUCCESS == replyKind)
	{
		QMessageBox::information(this, tr("Congratulation"),
			tr("Successfully change the remark"));
		emit changeRemarkSignal(message.text);
		close();
	}
	setAllEnabled(true);
}

void ChangeRemark::closeEvent(QCloseEvent *event)
{
	disconnect(link, SIGNAL(newReplySignal(qint32)), this, SLOT(result(qint32)));
}
