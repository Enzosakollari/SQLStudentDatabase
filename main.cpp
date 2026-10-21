#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student
{
    int id;
    int age;
    string name;
    string degree;
    char group;
    int year;
};

void printStudent(Student student)
{
    cout << student.name << " " << student.age << " "
         << student.id << " " << student.degree << " "
         << student.year << " " << student.group << "\n";
}


//so first if given a command for example INSERT 1 Enzo CompSci will have to be devided so we can distinguish the command
vector<string> parseInput(string input)
{
    vector<char> v(input.begin(), input.end());
    vector<string> args;
    string word;

    for (const char& c : v)
    {
        if (c == ' ')
        {
            if (!word.empty())
            {
                args.push_back(word);
                word.clear();
            }
        }
        else
        {
            word += c;
        }
    }

    if (!word.empty())
    {
        args.push_back(word);
    }

    return args;
}

//the function about parsing the values to get each on individually so i can onvert the ones i need into int
vector<string> parseValues(string input)
{
    vector<string> values;
    string value;

    if (input.substr(0, 7) != "VALUES(" || input.back() != ')')
    {
        return {};
    }

    for (size_t i = 7; i < input.size() - 1; i++)
    {
        if (input[i] == ',')
        {
            values.push_back(value);
            value.clear();
        }
        else
        {
            value += input[i];
        }
    }

    values.push_back(value);
    return values;
}
//just to have a functon dont want to make it very crowded into the insert so i just get a student and pass it here as an argment
//might say that  i am doing too many functions but well i think this is better than having super long funcions i think

#include <fstream>

void writestudentintofile(Student student)
{
    ofstream file("students.csv", ios::app);

    if (!file)
    {
        cout << "Could not open students.csv\n";
        return;
    }

    file << student.id << ","
         << student.age << ","
         << student.name << ","
         << student.degree << ","
         << student.group << ","
         << student.year << "\n";

    file.close();

    if (!file)
    {
        cout << "Failed to save student\n";
        return;
    }

    cout << "Student saved\n";
}

void insertStudent(vector<string> v)

{
    //now to insert records i am getting them from the input and then storing them in csv files

    //first i think i will need to have some logic about parsing this
    /* so first the arg will be something like
     Insert Into Students(here either pass in a strict order or to resemble sql i will need to parse this)
     i am doiing the strict approach since i think is more user friendly and simple for me to do */

     if (v.size() != 4)
{
    cout << "Invalid INSERT syntax\n";
    return;
}

//here i ave to take into account that values are a part of a string array so i need to parse them and validate them 

if (v[1] != "INTO" ||
    v[2] != "Students(id,age,name,degree,group,year)")
{
    cout << "Expected: INSERT INTO Students(id,age,name,degree,group,year) VALUES (...)\n";
    return;
}
vector<string> values= parseValues(v[v.size()-1]);

Student student;
//propably need some vaidations for this to be honest since user can just enter an age of 123333 for example.
student.id = stoi(values[0]);
student.age = stoi(values[1]);
student.name = values[2];
student.degree = values[3];
student.group = values[4][0];
student.year = stoi(values[5]);

writestudentintofile(student);



}

void selectStudents(){
ifstream file("students.csv");

if(!file){
    cout<<"Couldnt open file";
    return;
}
string row;

    while(getline(file,row)){
        for(char& c : row){
            if(c==','){
                c=' ';
            }

        }
        cout<< row << "\n";
    }




}

//this function will have to do te WHERE clause filtering in the sql statement for example select students where id=1 /not adding aggregations anytime soon tbh just filtering and every
//statement will be select * not a single column im going to be reading file rows

int main()
{
    

    while(true){
        string input;
        if (!getline(cin, input))
            break;
            vector<string> arguments= parseInput(input);

        if(arguments[0] == "Exit" || arguments[0] == "exit" || arguments[0] == "EXIT"){
            break;
        }
        
        for (int i = 0; i < arguments.size(); i++)
        {
            cout<<arguments[i] << endl;
        }
        if(arguments[0]=="INSERT"){
            insertStudent(arguments);
        }
        else if(arguments[0] == "SELECT" && arguments[1]=="Students"){
            selectStudents();
        }
         

    }

        
    return 0;
}