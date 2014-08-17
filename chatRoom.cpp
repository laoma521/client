#include "chatRoom.h"

Chatroom::Chatroom(Links *tLink, 
				   const FriendInformation &theFriend, 
				   const QString &acc, 
				   const QString &name,
				   QWidget *parent/* =0 */)
: QWidget(parent), link(tLink), peer(theFriend),
	myAccount(acc), myName(name)
{
	ui.setupUi(this);

	QPalette pal;
	QPixmap pixmap( QDir::toNativeSeparators
		("pictures/chatRoom.jpg") );
	pal.setBrush(QPalette::Window,QBrush(pixmap));
	setPalette(pal);

	if(peer.remark.isEmpty())
		peerRemark = peer.name;
	else
		peerRemark = peer.remark;

	QString title = QString("%1 (%2)").arg(peerRemark)
		.arg(theFriend.account);
	setWindowTitle(title);

	ui.aboutTextEdit->append(tr("account: ") + theFriend.account);
	ui.aboutTextEdit->append(tr("nickname: ") + peerRemark);
	ui.aboutTextEdit->append(tr("Personal Description: ") + theFriend.about);
	ui.aboutTextEdit->setReadOnly(true);

	ui.outputTextEdit->setReadOnly(true);

	ui.avatarFrame->setObjectName("avatar");
	QString str = QString("QFrame#avatar{border-image:url(pictures/%1.bmp)}")
		.arg(QString::number(peer.avatarNumber));
	ui.avatarFrame->setStyleSheet(str);

	readFontColor();

	connect(ui.sendPushButton, SIGNAL(clicked()), 
		this, SLOT(clickedSendButton()));
	connect(ui.closePushButton, SIGNAL(clicked()),
		this, SLOT(close()));
	connect(ui.colorPushButton, SIGNAL(clicked()),
		this, SLOT(clickedColorButton()));
	connect(ui.FontsPushButton, SIGNAL(clicked()),
		this, SLOT(clickedFontsButton()));
	connect(ui.recordPushButton, SIGNAL(clicked()),
		this, SLOT(clickedRecordButton()));

	connect(ui.inputTextEdit, SIGNAL(textChanged()),
		this, SLOT(inputTextChanged()));
	connect(ui.inputTextEdit, SIGNAL(sendSignal()),
		this, SLOT(clickedSendButton()));
}

Chatroom::~Chatroom()
{

}


void Chatroom::clickedSendButton()
{
	if(ui.inputTextEdit->toPlainText().isEmpty())
		return;
	sendString = ui.inputTextEdit->toHtml();
	ui.inputTextEdit->clear();
	QString dateTime = getCurrentDateTime();
	QString temp = QString("<font size=\"4\" color=green>%1    %2: </font>%3")
		.arg(myName).arg(dateTime).arg(sendString);
	ui.outputTextEdit->append(temp);

	Message message;
	message.kind = TALK_MESSAGE;
	message.sender = myAccount;
	message.receiver = peer.account;
	message.text = sendString;
	link->messageRequest(message);
}

void Chatroom::setOutputLine(const Message &mes)
{
	QString dateTime = getCurrentDateTime();
	QString temp = QString("<font size=\"4\" color=blue>%1    %2: </font>%3")
		.arg(peerRemark).arg(dateTime).arg(mes.text);
	ui.outputTextEdit->append(temp);
}

void Chatroom::closeEvent(QCloseEvent *event)
{
	emit roomQuitSignal();
	saveTalkHistory();

	disconnect(link, SIGNAL(newReplySignal(qint32)), this, SLOT(result(qint32)));
	event->accept();
}

void Chatroom::clickedColorButton()
{
	QColorDialog *colorDialog = new QColorDialog(this);
	colorDialog->setCurrentColor(ui.inputTextEdit->textColor());

	if(QDialog::Accepted == colorDialog->exec())
	{
		saveFile.color = colorDialog->currentColor();
		ui.inputTextEdit->setTextColor(saveFile.color);
		saveFontColor();
	}
}

void Chatroom::clickedFontsButton()
{
	QFontDialog *fontDialog = new QFontDialog(this);
	fontDialog->setCurrentFont(ui.inputTextEdit->font());
	fontDialog->setModal(true);
	if(QDialog::Accepted == fontDialog->exec())
	{
		saveFile.font = fontDialog->currentFont();
		ui.inputTextEdit->setCurrentFont(saveFile.font);
		saveFontColor();
	}
}

void Chatroom::readFontColor()
{
	QString filename = QString("./save/%1/colorFont.cf").arg(myAccount);
	filename = QDir::toNativeSeparators(filename);
	QFile file(filename);

	if( !file.open(QIODevice::ReadOnly) )
		return;

	QDataStream in(&file);
	in.setVersion(QDataStream::Qt_4_0);
	in >> saveFile;
	ui.inputTextEdit->setCurrentFont(saveFile.font);
	ui.inputTextEdit->setTextColor(saveFile.color);
	file.close();
}

void Chatroom::saveFontColor() const
{

	QString filename = QString("./save/%1/colorFont.cf").arg(myAccount);
	filename = QDir::toNativeSeparators(filename);
	QFile file(filename);
	if( !file.open(QIODevice::WriteOnly) )
		return;
	QDataStream out(&file);
	out.setVersion(QDataStream::Qt_4_0);
	out << saveFile;
	file.close();
}

void Chatroom::clickedRecordButton()
{
	QString record = readTalkHistory();
	QTextEdit *textEdit = new QTextEdit(record, this);
	textEdit->resize(300, 500);
	Qt::WindowFlags flag = Qt::Window
		| Qt::WindowCloseButtonHint 
		| Qt::WindowMinimizeButtonHint;
	textEdit->setWindowFlags(flag);
	textEdit->setReadOnly(true);
	textEdit->show();
}

void Chatroom::inputTextChanged()
{
	if(ui.inputTextEdit->toPlainText().isEmpty())
	{
		ui.inputTextEdit->setTextColor(saveFile.color);
		ui.inputTextEdit->setCurrentFont(saveFile.font);
	}
}

void Chatroom::saveTalkHistory() const
{
	QString fileLoad = QString("./save/%1/%2.re")
		.arg(myAccount).arg(peer.account);
	fileLoad = QDir::toNativeSeparators(fileLoad);
	QFile file(fileLoad);
	bool isOpen = file.open(QIODevice::WriteOnly | QIODevice::Append);
	if(!isOpen)
		return;

	QDataStream out(&file);
	out.setVersion(QDataStream::Qt_4_0);

	if(ui.outputTextEdit->toPlainText().isEmpty())
		return;

	QString talkRecord = ui.outputTextEdit->toHtml();
	out << talkRecord;
	file.close();
}

QString Chatroom::readTalkHistory()
{
	QString allRecord;
	QString fileLoad = QString("./save/%1/%2.re")
		.arg(myAccount).arg(peer.account);
	fileLoad = QDir::toNativeSeparators(fileLoad);
	QFile file(fileLoad);
	bool isOpen = file.open(QIODevice::ReadOnly);

	if(!isOpen)
		return ui.outputTextEdit->toHtml();

	QDataStream in(&file);
	in.setVersion(QDataStream::Qt_4_0);

	QString tempString;
	while( !file.atEnd() )
	{
		in >> tempString;
		allRecord += tempString;
	}
	file.close();
	allRecord += ui.outputTextEdit->toHtml();
	return allRecord;
}

QString Chatroom::getCurrentDateTime()
{
	QTime time = QTime::currentTime();
	QDate date = QDate::currentDate();

	return QString("%1  %2").arg(date.toString(Qt::ISODate))
		.arg(time.toString(Qt::ISODate));
}
