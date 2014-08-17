#include "inputTextEdit.h"

InputTextEdit::InputTextEdit(QWidget *parent/* =0 */)
: QTextEdit(parent)
{

}

InputTextEdit::~InputTextEdit()
{

}

void InputTextEdit::keyPressEvent(QKeyEvent *event)
{
	bool isSend = (Qt::Key_Return==event->key() || Qt::Key_Enter==event->key())
		&& (event->modifiers() & Qt::ControlModifier);

	if(isSend)
		emit sendSignal();
	else
		QTextEdit::keyPressEvent(event);
}
