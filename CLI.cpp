#include "CLI.h"
vector<Command*> buildAllCommand(vector<Command*> vecRet, DefaultIO* dio){
    //vecRet.push_back(new CommandOneUploadFile(dio));
    //vecRet.push_back(new CommandTwoAlgorithmSettings(dio));
    //vecRet.push_back(new CommandThreeDetectAnomalies(dio));
    //vecRet.push_back(new CommandFourDisplayResults(dio));
    //vecRet.push_back(new CommandFiveUploadAnomalies(dio));
    //vecRet.push_back(new CommandSixExit(dio));
    return vecRet;
}
CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
    commandsData * data = new commandsData();
    data->setAnomalyDetector(this->hybridDetector);
    //buildAllCommand
    this->vecCommands.push_back(new CommandOneUploadFile(dio,data));
    this->vecCommands.push_back(new CommandTwoAlgorithmSettings(dio,data));
    this->vecCommands.push_back(new CommandThreeDetectAnomalies(dio,data));
    this->vecCommands.push_back(new CommandFourDisplayResults(dio,data));
    this->vecCommands.push_back(new CommandFiveUploadAnomalies(dio,data));
    this->vecCommands.push_back(new CommandSixExit(dio,data));
}

void CLI::start(){
    int chooseCommand = 0;
    string commandISteing;
    while (chooseCommand!=6)
    {
        this->dio->write("Welcome to the Anomaly Detection Server.\r\n");
        this->dio->write("Please choose an option:\r\n");
        for (int i = 0; i < this->vecCommands.size(); i++)
        {
            commandISteing = this->vecCommands[i]->getDescription();
            this->dio->write(commandISteing);
        }
        float x;
        string inputNumber = this->dio->read();
        chooseCommand = stoi(inputNumber);
        if (chooseCommand >= 6 || chooseCommand<=0)
        {
            break;
        }
        this->vecCommands[chooseCommand-1]->execute();
    }
    
    

    
}


CLI::~CLI() {
}

