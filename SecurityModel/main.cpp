//Teodor Hedberg tehe20@student.bth.se, Kim Budichewski kibu20@student.bth.se
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <dirent.h>
#include <stdlib.h>
#include <algorithm>

void tofile(const std::vector<std::string>& virussig, const std::vector<std::string>& file, std::string filepath) //Skriver ut resultatet i en fil
{
    std::ofstream outfile;
    outfile.open("dv1620.log");
    outfile << "Virus:              File:\n";
    for(int i = 0; i < virussig.size(); i++){
        outfile << virussig[i].substr(0,virussig[i].find_first_of("=")) << "  -->  " << file[i] << std::endl;
    }
    outfile.close();
    std::vector <std::string> filevector;
    for(auto f:file)
        if(std::find(filevector.begin(),filevector.end(),f)==filevector.end())
            filevector.push_back(f);
    std::string answer;
    std::cout << "Do you want to remove infected files? (Y/n)" << std::endl;
    std::cin >> answer;
    if(answer != "no" && answer != "No" && answer != "n" && answer != "N" && answer!= "nej" && answer != "Nej")
    {
        for(auto f:filevector)
        {
            std::string temp = "rm -f " + f;
            const char* filepath = temp.c_str();
            system(filepath);
        }
    }
}

void compare(const std::vector<std::string>& signvec, const std::vector<std::string>& files, std::string realpath) //jämnför signaturerna med filerna 
{
    std::string signature = "0x";
    std::vector<std::string>asciisig;
    std::vector<std::string>virusname;
    std::vector<std::string>virusoutput; //Sparas de virus namn som ska skrivas på filen
    std::vector<std::string>fileoutput; //Sparas de filepath namn som ska skrivas på filen
    std::string fullvalue;
    int largestsize =0;

    for (auto& s : signvec) //Spara alla signatures som virus namn och ascii i vectorer
    {
        for (int i = 1; i < s.size() - s.find_first_of("="); i += 2)
        {
            double k = std::stoi(s.substr(s.find_first_of('=') + i, 2), nullptr, 16);
            std::string ascii(1, char(k));
            fullvalue += ascii;
        }
       /* if(largestsize < fullvalue.size())
            largestsize = fullvalue.size();*/
        asciisig.push_back(fullvalue);
        virusname.push_back(s.substr(0, s.find_first_of("=") + 1));
        fullvalue = "";
    }

    for (auto& f : files) //Går in i alla filer för att kolla om de har virus
    {
        std::fstream fs;
        fs.open(f, std::fstream::in);
        std::string filecontains;
        std::string row;
        while (getline(fs, row))
        {
            filecontains += row;
            filecontains += "\n";
        }
        for (int i = 0; i < asciisig.size(); i++) //jämför alla virussignaturer med filerna
        {
            std::string temp = filecontains;
            while(temp.size() > asciisig[i].size())
            {
                int pos = temp.find_first_of(asciisig[i][0]);
                if(pos == -1)
                    break;
                else if(pos+asciisig[i].size() > temp.size())
                    break;

                if (asciisig[i] == temp.substr(pos, asciisig[i].size()))
                {
                    virusoutput.push_back(virusname[i]);
                    fileoutput.push_back(f);
                    break;
                }
                else
                    temp = temp.substr(pos+1);
            }
        }
    }
    if(virusoutput.size() > 0)
        tofile(virusoutput, fileoutput, realpath);

}

void directorytraverse(std::vector<std::string>&files, std::string directorypath)//traverserar filträdet för att hitta alla filer och skriver in dom i en vektor
{
    const char* pointer = directorypath.c_str();
    DIR *dr = NULL;
    struct dirent *isdirectory = NULL;
    dr = opendir(pointer); //måste vara const char*
    
    if(!dr){
        std::cout << "input not a folder" << std::endl;
        exit(0);
    }

    std::string comparison = ".";
    std::string comparison2 = "..";
    while((isdirectory = readdir(dr)) != NULL)
    {        
        if (isdirectory->d_name != comparison && isdirectory->d_name != comparison2)
        {        
            std::string nextdir(pointer);
            nextdir += "/";
            nextdir += isdirectory->d_name;
            if(isdirectory->d_type == DT_DIR)
                directorytraverse(files, nextdir);
            else
            {
                files.push_back(nextdir);
            }
        }

    }
    closedir(dr);
}

void realPath(std::string& thisfilepath){ //ger absolutvägen till programmet
    char resolved_path[PATH_MAX];
    std::string thisDir = realpath(".",resolved_path);//Färdig funktion som ger vägen till denna folder från /home
    int neededcheck = thisfilepath.find("..");
    int singlecheck = thisfilepath.find(".");

    std::string fileStartPath;
    if(thisfilepath.find("/") == 0)
        fileStartPath = thisfilepath.substr(0, thisfilepath.substr(1).find_first_of("/")+1);
    else
        fileStartPath = thisfilepath.substr(0, thisfilepath.find("/"));

    if(fileStartPath == "/home")
        thisfilepath = thisfilepath;
    else if(fileStartPath == "home")
        thisfilepath = "/" + thisfilepath;
    else if(neededcheck == 0){
        int numOfDotDot = 0;
        while(neededcheck > 0 || neededcheck < thisfilepath.size()){
            numOfDotDot++;
            thisfilepath = thisfilepath.substr(thisfilepath.find_first_of("..")+2);
            neededcheck = thisfilepath.find("..");
        }
        while(numOfDotDot != 0){
            thisDir = thisDir.substr(0,thisDir.find_last_of("/"));
            numOfDotDot--;
        }
        thisfilepath = thisDir + thisfilepath;
    }
    else if(singlecheck == 0){
        thisfilepath = thisDir + thisfilepath.substr(thisfilepath.find_first_of(".")+1);
    }
    else{
        thisfilepath = thisDir + "/" + thisfilepath;
    }
}

int main(int argi, char* argc[])
{
    if(argi == 0 || argi >4){
        std::cout << "Wrong number of arguments!" << std::endl;
    }
    else
    {
        std::string filepath;
        if(argi != 1)
        {
            if(std::string(argc[1]) != "-d")
                filepath = argc[1];
            else
                filepath = argc[3];
        }
        realPath(filepath);

        std::vector<std::string> signatures;
        std::vector<std::string> files;
        std::string row;
        std::string signaturepath;
        std::ifstream fs;

        if(argi != 1)
            directorytraverse(files, filepath);

        if(argi == 1)//Avrekommenderas från att användas då det tar för lång tid
        {
            fs.open("./signatures.db");
            if(fs.is_open())
                signaturepath = "./signatures.db";
            fs.close();
            filepath = "/home";
            directorytraverse(files, filepath);
        }
        else if(argi == 2)
        {
            for(auto& f:files)
            {
                int pos = f.find_last_of("/");
                std::string findsign = f.substr(pos);
                if (findsign == "/signatures.db")
                    signaturepath = f;
            }
            fs.open("./signatures.db");
            if(fs.is_open())
                signaturepath = "./signatures.db";
            fs.close();
        }
        else if (argi == 3) //ifall argument 3 är signatures.db
        {
            if(std::string(argc[2]) == "signatures.db")
                signaturepath = "./signatures.db";
        }
        else if(argi == 4)
        {
            if(std::string(argc[1]) == "-d")
            {
                signaturepath = argc[2];
            }
            else if(std::string(argc[2]) == "-d")
            {
                std::string temp = argc[3];
                signaturepath = "./" + temp;
            }
            else
            {
                std::cout << "Something is wrong with your arguments!" << std:: endl;
                return 0;
            }

            std::string findsign;
            if(signaturepath != "./signatures.db"){
                findsign = "." + signaturepath.substr(signaturepath.find_last_of("/"));
            }
            else
                findsign = "./signatures.db";

            if(findsign != "./signatures.db")   
            {
                std::cout << "Can't find signatures" << std::endl;
                exit(0);
            }
        }

        fs.open(signaturepath);
        if(fs.is_open()){
            while (getline(fs, row))
                signatures.push_back(row);
            compare(signatures, files, filepath);
            fs.close();
        }
        else
        {
            std::cout << "Can't open or find signatures." << std::endl;
        }
    }
   return 0;
}