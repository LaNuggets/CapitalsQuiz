#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <QString>
#include <QCoreApplication>
#include <QDir>
#include <nlohmann/json.hpp>
using namespace std;

using json = nlohmann::json;


pair<QString, QString> getInfo(){

  QString appDir = QCoreApplication::applicationDirPath();
  QString jsonPath = appDir + "/data/capitals.json";

  std::ifstream f(jsonPath.toStdString());
  if(!f.is_open()){
    std::cerr << "Erreur : impossible d'ouvrir le fichier JSON !" << std::endl;
    return {"error", "error"};
  }
  
  json data;
  f >> data;

  int rndIndex = rand() % data.size();

  string country = data[rndIndex]["country"];
  string capital = data[rndIndex]["city"];

  QString question = QString::fromStdString(country);
  QString answer = QString::fromStdString(capital);
    
  return {question, answer};
}
