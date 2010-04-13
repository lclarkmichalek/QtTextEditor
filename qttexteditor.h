#include <QMainWindow>
#include <QTextEdit>
#include <QMenu>
#include <QAction>
#include <QTextBrowser>

#ifndef QTTEXTEDITOR_H
#define QTTEXTEDITOR_H

class QTTextEditor : public QMainWindow
{
	Q_OBJECT
public:
	QTTextEditor(QMainWindow *parent = 0);
public slots:
	void Modified(bool in = true);

	bool closeFile(); //done
	void openFile(); //done
	void newFile(); //done
	void saveFile(); //done
private:
	//vars
	QTextEdit *editor;
	QString *CurrentFile; //QString("") if unsaved

	//Actions
	QAction *Close;
	QAction *Open;
	QAction *New;
	QAction *Save;

	//Menus
	QMenu *File;
	QMenu *Edit;
	QMenu *Help;

	//Init Functions
	void createActions();
	void createMenus();

	//Functions
	void _loadFile(QString FileName); //done
	void _unloadFile(); //done
	void _saveFile(); //done
	void _newFile(); //done
	void setTitle(QString Title);

};

#endif // QTTEXTEDITOR_H
