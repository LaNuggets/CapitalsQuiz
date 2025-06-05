#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <QString>
#include <QCoreApplication>
#include <QDir>
#include <nlohmann/json.hpp>
using namespace std;

using json = nlohmann::json;

tuple<QString, QString, QString> getInfo(){

  // Loading json file
  QString appDir = QCoreApplication::applicationDirPath();
  QString jsonPath = appDir + "/data/data.json";

  // Handle error
  std::ifstream f(jsonPath.toStdString());
  if(!f.is_open()){
    std::cerr << "Erreur : impossible d'ouvrir le fichier JSON !" << std::endl;
    return {"error", "error", "error"};
  }
  
  json data; // Create empty json object
  f >> data; // filled data var with the content of "f"

  // Get a random country
  int rndIndex = rand() % data.size();

  string country = data[rndIndex]["country"];
  string capital = data[rndIndex]["city"];
  string flag = data[rndIndex]["flag"];

  QString question = QString::fromStdString(country);
  QString answer = QString::fromStdString(capital);
  QString CFlag = QString::fromStdString(flag);
    
  return {question, answer, CFlag};
}
