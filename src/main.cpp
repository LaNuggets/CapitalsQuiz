#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QScreen>
#include <QDebug>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPixmap>
#include <ctime>
#include <iostream>
#include <data/question.h>
using namespace std;

int main(int argc, char *argv[]) {
  
    QApplication app(argc, argv);
    srand(time(nullptr));
    // Main window
    QWidget window;
    window.setWindowTitle("Capital Quiz");
    window.resize(300, 200);

    // Place de window on the center of the screen
    QScreen *screen = app.primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = screenGeometry.x() + (screenGeometry.width() - window.width()) / 2;
    int y = screenGeometry.y() + (screenGeometry.height() - window.height()) / 2;
    window.move(x, y);

    // Get country information: Name, capital, and flag url
    auto [country, answer, flag] = getInfo();
    
    // Create widgets
    QLabel *flagLabel = new QLabel();
    flagLabel->setFixedSize(200, 150);
    flagLabel->setAlignment(Qt::AlignCenter);
    QLabel *label = new QLabel("What is the capital of this country ?");
    QPushButton *countryButton = new QPushButton("Reveal Country Name"); // Button for hide country name
    QLineEdit *input = new QLineEdit(); // Form
    input->setFocus(); // Automatic focus on lunch
    QPushButton *submit = new QPushButton("Submit"); // Submit button
    QLabel *errorLabel = new QLabel(); // Print error
    // Some CSS
    submit->setStyleSheet("background-color: green;"); // Green button
    errorLabel->setStyleSheet("color: red;"); // Red error Msg
    countryButton->setStyleSheet("color: black;"); // Black text for country reveal button
    
    // Layout
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(flagLabel); // Flag
    layout->addWidget(countryButton); // Reveal button
    layout->addWidget(label); // Question
    layout->addWidget(input); // Form
    layout->addWidget(submit); // Submit button
    layout->addWidget(errorLabel); // Error Msg
    window.setLayout(layout);

    // Flag download
    QNetworkAccessManager* manager = new QNetworkAccessManager(&window);
    QNetworkRequest request{QUrl(flag)};
    QNetworkReply* reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, [reply, flagLabel]() {
      /// Check error during flag loading
        if (reply->error() == QNetworkReply::NoError) { 
            QByteArray data = reply->readAll();
            QPixmap pix;
            pix.loadFromData(data);
            flagLabel->setPixmap(pix.scaled(flagLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            flagLabel->setText("Failed to load flag");
        }
        reply->deleteLater();
    });

    // Reveal button
    QObject::connect(countryButton, &QPushButton::clicked, [=]() {
      countryButton->setText(country);
      countryButton->setEnabled(false); // Enable button after clicked
    });

    // Connexion to the button
    auto checkAnswer = [&]() {
        QString userAnswer = input->text();
	if(userAnswer.size() >= 30){
	  errorLabel->setText("Your answer is waaaayyy to long !");
	}else{	 
	  if(userAnswer.toLower() == answer.toLower()){
	    errorLabel->setText("");
	    window.close(); // Close app on Win
	  } else if(userAnswer == "doNNe"){ // Cheat code to get the answer
	    input->setText(answer);
	  } else {
	    input->setText("");
	    errorLabel->setText(QString("Bad answer! '%1' is not the capital of %2").arg(userAnswer).arg(country));
	  }
	}
    };
    
    // validate if button presse or enter presse
    QObject::connect(submit, &QPushButton::clicked, checkAnswer);
    QObject::connect(input, &QLineEdit::returnPressed, checkAnswer);
    window.show();
    return app.exec();
}
