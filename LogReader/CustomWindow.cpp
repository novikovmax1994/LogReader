#include "CustomWindow.h"

CustomWindow::CustomWindow(QWidget* parent) : QMainWindow(parent) {
	log_reader_ = new Reader();

	QWidget* global_widget = new QWidget();
	QWidget* up_widget = new QWidget();

	QVBoxLayout* global_lay = new QVBoxLayout();
	QHBoxLayout* up_lay = new QHBoxLayout();

	file_path_lab_.setText("Not selected");
	file_path_lab_.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

	browse_button_.setText("...");
	browse_button_.setMaximumSize(60, 25);

	read_button_.setText("Read log");
	read_button_.setMaximumSize(60, 25);

	result_.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
	result_.setColumnCount(2);
	result_.resizeColumnsToContents();
	QStringList header{ "Device address","Command code" };
	result_.setHorizontalHeaderLabels(header);
	result_.horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	up_lay->setContentsMargins(3, 0, 0, 0);
	up_lay->addWidget(&file_path_lab_);
	up_lay->addWidget(&browse_button_);
	up_lay->addWidget(&read_button_);

	up_widget->setLayout(up_lay);
	up_widget->setMaximumHeight(50);
	up_widget->setMinimumHeight(30);

	global_lay->setContentsMargins(0, 0, 0, 0);
	global_lay->addWidget(up_widget);
	global_lay->addWidget(&result_);

	global_widget->setLayout(global_lay);
	
	this->setCentralWidget(global_widget);
}

CustomWindow::~CustomWindow() {
	delete log_reader_;
}

void CustomWindow::Init() {
	QObject::connect(&browse_button_, SIGNAL(clicked()), this, SLOT(browse_button_clicked()));
	QObject::connect(&read_button_, SIGNAL(clicked()), this, SLOT(read_button_clicked()));
}

QString CustomWindow::FileDialog() {
	QUrl start;
	QUrl file_path = QFileDialog::getOpenFileUrl(this, "Browse file", start, "(*.log) ;; (*.txt)");
	return file_path.toLocalFile();
}

void CustomWindow::DisplayResult() {
	ResultMap data = log_reader_->ReadLogFile();
	int num_row = 0;
	QTableWidgetItem* temp_1;
	QTableWidgetItem* temp_2;
	if (data.size()) {
		result_.setRowCount(data.size());
	}
	else {
		result_.setRowCount(1);
		temp_1 = new QTableWidgetItem;
		temp_1->setText("Addresses not found");
		result_.setItem(num_row, 0, temp_1);
		temp_2 = new QTableWidgetItem;
		temp_2->setText("Command codes not found");
		result_.setItem(num_row, 1, temp_2);
	}
	for (auto m_it : data) {
		QString column1_text = QString::fromStdString(m_it.first);
		temp_1 = new QTableWidgetItem;
		temp_1->setText(column1_text);
		result_.setItem(num_row, 0, temp_1);
		QString column2_text = QString::fromStdString(m_it.second);
		temp_2 = new QTableWidgetItem;
		temp_2->setText(column2_text);
		result_.setItem(num_row, 1, temp_2);
		++num_row;
	}
}

void CustomWindow::browse_button_clicked() {
	QString file_path = FileDialog();
	if (file_path != '\0') {
		log_reader_->setPath(file_path.toStdString());
		file_path_lab_.setText(file_path);
		result_.clear();
		QStringList header{ "Device address","Command code" };
		result_.setHorizontalHeaderLabels(header);
	}
}

void CustomWindow::read_button_clicked() {
	if (file_path_lab_.text() != "Not selected") {
		result_.clear();
		QStringList header{ "Device address","Command code" };
		result_.setHorizontalHeaderLabels(header);
		DisplayResult();
	}
}