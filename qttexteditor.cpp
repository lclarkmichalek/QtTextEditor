#include "qttexteditor.h"

#include <QtGui>

QTTextEditor::QTTextEditor(QMainWindow *parent)
    : QMainWindow(parent)
{
	setWindowTitle(tr("[*] - QtTextEditor"));

	editor = new QTextEdit(this);
	setCentralWidget(editor);

	CurrentFile = new QString("");

	createActions();
	createMenus();

	connect(editor, SIGNAL(textChanged ()), this, SLOT(Modified()));
}

void QTTextEditor::Modified(bool in)
{
	editor->document()->setModified(in);
	setWindowModified(in);

	editor->setPlainText(QString("Modified"));
}

void QTTextEditor::setTitle(QString Title)
{
	editor->setDocumentTitle(Title);
	setWindowTitle(editor->documentTitle().append("[*] - QTTextEditor"));
}

bool QTTextEditor::closeFile()
{
	if (editor->document()->isModified()) {
		 QMessageBox msgBox;
		 msgBox.setText("The document has been modified.");
		 msgBox.setInformativeText("Do you want to save your changes?");
		 msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard
													 | QMessageBox::Cancel);
		 msgBox.setDefaultButton(QMessageBox::Save);
		 int ret = msgBox.exec();
		 switch (ret) {
		 case QMessageBox::Save:
			 saveFile();
			 break;
		 case QMessageBox::Discard:
			 _unloadFile();
			 return true;
		 case QMessageBox::Cancel:
			 return false;
		 }
	}
	_unloadFile();
	return true;
}

void QTTextEditor::openFile()
{
	if ( not closeFile()) return;
	QString FileName = QFileDialog::getOpenFileName(this);
	_loadFile(FileName);
}

void QTTextEditor::saveFile()
{
	if (*CurrentFile == QString(""))  {
		QString FileName = QFileDialog::getSaveFileName(this);
		if (FileName == QString("")) return;
		*CurrentFile = FileName;
	}
	_saveFile();
}

void QTTextEditor::newFile()
{
	closeFile();
	_newFile();
}

void QTTextEditor::_loadFile(QString FileName)
{
	*CurrentFile = FileName;
	QFile File(FileName);
	QTextStream Content(&File);
	Content.setCodec("UTF-8");
	editor->setPlainText(Content.readAll());

	setTitle(FileName);
	Modified(false);

}

void QTTextEditor::_unloadFile()
{
	*CurrentFile = QString("");
	editor->setText(QString(""));
	Modified(false);
	setTitle(QString(""));
}

void QTTextEditor::_saveFile()
{
	QFile File(*CurrentFile);
	QTextStream Content(&File);
	Content << editor->document()->toPlainText();
	Modified(false);
}

void QTTextEditor::_newFile()
{
	_unloadFile();
}

void QTTextEditor::createActions()
{
	Close = new QAction(tr("&Close"), this);
	connect(Close, SIGNAL(triggered()), this, SLOT(closeFile()));
	Open = new QAction(tr("&Open"), this);
	connect(Open, SIGNAL(triggered()), this, SLOT(openFile()));
	New = new QAction(tr("&New"), this);
	connect(New, SIGNAL(triggered()), this, SLOT(newFile()));
	Save = new QAction(tr("&Save"), this);
	connect(Save, SIGNAL(triggered()), this, SLOT(saveFile()));
}

void QTTextEditor::createMenus()
{
	File = menuBar()->addMenu(tr("&File"));
	File->addAction(Close);
	File->addAction(Open);
	File->addAction(Save);
	File->addAction(New);
	Edit = menuBar()->addMenu(tr("&Edit"));
	Help = menuBar()->addMenu(tr("&Help"));
}
