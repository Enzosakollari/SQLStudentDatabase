#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
vector<string> parseRow(string row);
void writeRowsIntoFile(vector<string> rows);

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

void deleteStudent(vector<string> v)
{
    if (v.size() != 6 ||
        v[1] != "Students" ||
        v[2] != "WHERE" ||
        v[3] != "id" ||
        v[4] != "=")
    {
        cout << "Expected: DELETE Students WHERE id = 1\n";
        return;
    }

    ifstream file("students.csv");

    if (!file)
    {
        cout << "Could not open students.csv\n";
        return;
    }

    vector<string> rows;
    string row;
    bool found = false;

    while (getline(file, row))
    {
        vector<string> values = parseRow(row);

        if (values[0] == v[5])
        {
            found = true;
        }
        else
        {
            rows.push_back(row);
        }
    }

    bool readFailed = file.bad();
    file.close();

    if (readFailed)
    {
        cout << "Failed to read students.csv\n";
        return;
    }

    if (!found)
    {
        cout << "Student not found\n";
        return;
    }

    writeRowsIntoFile(rows);
}

void updateStudent(vector<string> v)
{
    if (v.size() != 10 ||
        v[1] != "Students" ||
        v[2] != "SET" ||
        v[4] != "=" ||
        v[6] != "WHERE" ||
        v[7] != "id" ||
        v[8] != "=")
    {
        cout << "Expected: UPDATE Students SET age = 23 WHERE id = 1\n";
        return;
    }

    int column = -1;

    if (v[3] == "id")
        column = 0;
    else if (v[3] == "age")
        column = 1;
    else if (v[3] == "name")
        column = 2;
    else if (v[3] == "degree")
        column = 3;
    else if (v[3] == "group")
        column = 4;
    else if (v[3] == "year")
        column = 5;

    if (column == -1)
    {
        cout << "Unknown column\n";
        return;
    }

    // A comma would create an extra CSV field.
    if (v[5].find(',') != string::npos)
    {
        cout << "Value cannot contain commas\n";
        return;
    }

    ifstream file("students.csv");

    if (!file)
    {
        cout << "Could not open students.csv\n";
        return;
    }

    vector<string> rows;
    string row;
    bool found = false;

    while (getline(file, row))
    {
        vector<string> values = parseRow(row);

        if (values.size() == 6 && values[0] == v[9])
        {
            values[column] = v[5];
            found = true;
            row.clear();

            for (size_t i = 0; i < values.size(); i++)
            {
                if (i > 0)
                {
                    row += ',';
                }

                row += values[i];
            }
        }

        rows.push_back(row);
    }

    bool readFailed = file.bad();
    file.close();

    if (readFailed)
    {
        cout << "Failed to read students.csv\n";
        return;
    }

    if (!found)
    {
        cout << "Student not found\n";
        return;
    }

    writeRowsIntoFile(rows);
}

vector<string> parseRow(string row)
{
    vector<string> values;
    string value;

    for (char c : row)
    {
        if (c == ',')
        {
            values.push_back(value);
            value.clear();
        }
        else
        {
            value += c;
        }
    }

    values.push_back(value);
    return values;
}

void writeRowsIntoFile(vector<string> rows)
{
    ofstream file("students.csv");

    if (!file)
    {
        cout << "Could not open students.csv for writing\n";
        return;
    }

    for (const string& row : rows)
    {
        file << row << "\n";
    }

    file.close();

    if (!file)
    {
        cout << "Failed to save changes\n";
        return;
    }

    cout << "Changes saved\n";
}

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
        else if (arguments[0] == "DELETE")
        {
            deleteStudent(arguments);
        }
        else if (arguments[0] == "UPDATE")
        {
            updateStudent(arguments);
        }
         

    }

        
    return 0;
}