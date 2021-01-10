#include "CLI.h"
vector<Command*> buildAllCommand(vector<Command*> vecRet, DefaultIO* dio){
    vecRet.push_back(new CommandOneUploadFile(dio));
    vecRet.push_back(new CommandTwoAlgorithmSettings(dio));
    vecRet.push_back(new CommandThreeDetectAnomalies(dio));
    vecRet.push_back(new CommandFourDisplayResults(dio));
    vecRet.push_back(new CommandFiveUploadAnomalies(dio));
    vecRet.push_back(new CommandSixExit(dio));
    return vecRet;
}
CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
    //buildAllCommand
    this->vecCommands.push_back(new CommandOneUploadFile(dio));
    this->vecCommands.push_back(new CommandTwoAlgorithmSettings(dio));
    this->vecCommands.push_back(new CommandThreeDetectAnomalies(dio));
    this->vecCommands.push_back(new CommandFourDisplayResults(dio));
    this->vecCommands.push_back(new CommandFiveUploadAnomalies(dio));
    this->vecCommands.push_back(new CommandSixExit(dio));
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
        //string inputNumber = this->dio->read();
        //chooseCommand = stoi(inputNumber);
        if (chooseCommand == 6)
        {
            break;
        }
        //this->vecCommands[chooseCommand-1]->execute();
        break;
        
    }
    
    

    
}


CLI::~CLI() {
}

