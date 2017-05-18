#pragma once
#include "qmainwindow.h"
#include "qpushbutton.h"
#include "qtablewidget.h"
#include "qlabel.h"
#include "qlayout.h"
#include "qheaderview.h"
#include "qfiledialog.h"
#include "Reader.h"


class CustomWindow : public QMainWindow{
Q_OBJECT

public:
	CustomWindow(QWidget *parent = Q_NULLPTR);
	virtual ~CustomWindow();
	void Init();

private:
	QString FileDialog();
	void DisplayResult();

private slots:
	void browse_button_clicked();
	void read_button_clicked();

private:
	Reader* log_reader_;

	QTableWidget result_;

	QPushButton browse_button_;
	QPushButton read_button_;

	QLabel file_path_lab_;
};