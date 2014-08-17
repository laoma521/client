#ifndef INPUTTEXTEDIT_H_
#define INPUTTEXTEDIT_H_

#include "constant.h"

class InputTextEdit : public QTextEdit
{
	Q_OBJECT
protected:
	void keyPressEvent(QKeyEvent *event);

public:
	InputTextEdit(QWidget *parent=0);
	~InputTextEdit();

signals:
	void sendSignal();

};

#endif
