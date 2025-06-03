#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QScreen>
#include <QDebug>
#include <QString>
#include <ctime>
#include <iostream>
#include <data/question.h>
using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    srand(time(nullptr));

    // Main window
    QWidget window;
    window.setWindowTitle("Question");
    window.resize(300, 150);

    // Place de window on the center of the screen
    QScreen *screen = app.primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = screenGeometry.x() + (screenGeometry.width() - window.width()) / 2;
    int y = screenGeometry.y() + (screenGeometry.height() - window.height()) / 2;
    window.move(x, y);

    // Create widgets
    auto [capital, answer] = getInfo();
    
    QLabel *label = new QLabel("What is the capital of " + capital);
    QLineEdit *input = new QLineEdit();
    QPushButton *submit = new QPushButton("Submit");
    QLabel *errorLabel = new QLabel(); // Print error
    submit->setStyleSheet("background-color: green;");
    errorLabel->setStyleSheet("color: red;"); // red texte
    
    // Layout vertical
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(label);
    layout->addWidget(input);
    layout->addWidget(submit);
    layout->addWidget(errorLabel);
    window.setLayout(layout);

    // Connexion to the button
    auto checkAnswer = [&]() {
        QString userAnswer = input->text();
	if(userAnswer.size() >= 30){
	  errorLabel->setText("Your answer is waaaayyy to long !");
	}else{	 
	  if(userAnswer.toLower() == answer.toLower()){
	    errorLabel->setText("");
	    window.close();
	  } else if(userAnswer == "doNNe"){
	    input->setText(answer);
	  } else {
	    input->setText("");
	    errorLabel->setText(QString("Bad answer! '%1' is not the capital of %2").arg(userAnswer).arg(capital));
	  }
	}
    };
    // validate if button presse or enter
    QObject::connect(submit, &QPushButton::clicked, checkAnswer);
    QObject::connect(input, &QLineEdit::returnPressed, checkAnswer);
    window.show();
    return app.exec();
}
